#include "transactionrecord.h"

#include "wallet.h"
#include "main.h"

/* Return positive answer if transaction should be shown in list.
 */
bool TransactionRecord::showTransaction(const CWalletTx &wtx)
{
    if (wtx.IsCoinBase() || wtx.IsCoinStake())
    {
        // Don't show generated coin until confirmed by at least one block after it
        // so we don't get the user's hopes up until it looks like it's probably accepted.
        //
        // It is not an error when generated blocks are not accepted.  By design,
        // some percentage of blocks, like 10% or more, will end up not accepted.
        // This is the normal mechanism by which the network copes with latency.
        //
        // We display regular transactions right away before any confirmation
        // because they can always get into some block eventually.  Generated coins
        // are special because if their block is not accepted, they are not valid.
        //
        if (wtx.GetDepthInMainChain() < 2)
        {
            return false;
        }
    }
    return true;
}

/*
 * Decompose CWallet transaction to model transaction records.
 */
QList<TransactionRecord> TransactionRecord::decomposeTransaction(const CWallet *wallet, const CWalletTx &wtx)
{
    QList<TransactionRecord> parts;
    int64 nTime = wtx.GetTxTime();
    int64 nCredit = wtx.GetCredit(true);
    int64 nDebit = wtx.GetDebit();
    int64 nNet = nCredit - nDebit;
    uint256 hash = wtx.GetHash();
    std::map<std::string, std::string> mapValue = wtx.mapValue;

    if (showTransaction(wtx))
    {
        if (wtx.IsCoinStake()) // ppcoin: coinstake transaction
        {
            int64 showCredit = wtx.GetValueOut(cidShinys);
            
            BOOST_FOREACH(const PAIRTYPE(const uint256, CWalletTx)& hash_tx, wallet->mapWallet)
            {
                const CWalletTx &otherTx = hash_tx.second;
                if (otherTx.hashBlock == wtx.hashBlock && otherTx.IsCoinBase())
                {
                    showCredit += otherTx.GetValueOut(cidShinys);
                    break;
                }
            }
            
            parts.append(TransactionRecord(hash, nTime, TransactionRecord::StakeMint, "", -nDebit, showCredit));
        }
        else if (nNet > 0 || wtx.IsCoinBase())
        {
            bool fShow = true;
            if (wtx.IsCoinBase())
            {
                BOOST_FOREACH(const PAIRTYPE(const uint256, CWalletTx)& hash_tx, wallet->mapWallet)
                {
                    const CWalletTx &otherTx = hash_tx.second;
                    if (otherTx.hashBlock == wtx.hashBlock && otherTx.IsCoinStake())
                    {
                        fShow = false;
                        break;
                    }
                }
            }
            
            if (fShow) {
                //
                // Credit
                //
                BOOST_FOREACH(const CTxOut& txout, wtx.vout)
                {
                    if(wallet->IsMine(txout))
                    {
                        TransactionRecord sub(hash, nTime);
                        CBitcoinAddress address;
                        sub.idx = parts.size(); // sequence number
                        sub.credit = txout.nValue;
                        if (wtx.IsCoinBase())
                        {
                            // Generated
                            sub.type = TransactionRecord::Generated;
                        }
                        else if (ExtractAddress(txout.scriptPubKey, address) && wallet->HaveKey(address))
                        {
                            // Received by Bitcoin Address
                            sub.type = TransactionRecord::RecvWithAddress;
                            sub.address = address.ToString();
                        }
                        else
                        {
                            // Received by IP connection (deprecated features), or a multisignature or other non-simple transaction
                            sub.type = TransactionRecord::RecvFromOther;
                            sub.address = mapValue["from"];
                        }

                        parts.append(sub);
                    }
                }
            }
        }
        else
        {
            bool fAllFromMe = true;
            BOOST_FOREACH(const CTxIn& txin, wtx.vin)
                fAllFromMe = fAllFromMe && wallet->IsMine(txin);

            bool fAllToMe = true;
            BOOST_FOREACH(const CTxOut& txout, wtx.vout)
                fAllToMe = fAllToMe && wallet->IsMine(txout);

            if (fAllFromMe && fAllToMe)
            {
                // Payment to self
                int64 nChange = wtx.GetChange();

                parts.append(TransactionRecord(hash, nTime, TransactionRecord::SendToSelf, "",
                                -(nDebit - nChange), nCredit - nChange));
            }
            else if (fAllFromMe)
            {
                //
                // Debit
                //
                int64 nTxFee = nDebit - wtx.GetValueOut(cidShinys);

                for (int nOut = 0; nOut < wtx.vout.size(); nOut++)
                {
                    const CTxOut& txout = wtx.vout[nOut];
                    TransactionRecord sub(hash, nTime);
                    sub.idx = parts.size();

                    if(wallet->IsMine(txout))
                    {
                        // Ignore parts sent to self, as this is usually the change
                        // from a transaction sent back to our own address.
                        continue;
                    }

                    CBitcoinAddress address;
                    if (ExtractAddress(txout.scriptPubKey, address))
                    {
                        // Sent to Bitcoin Address
                        sub.type = TransactionRecord::SendToAddress;
                        sub.address = address.ToString();
                    }
                    else
                    {
                        // Sent to IP, or other non-address transaction like OP_EVAL
                        sub.type = TransactionRecord::SendToOther;
                        sub.address = mapValue["to"];
                    }

                    int64 nValue = txout.nValue;
                    /* Add fee to first output */
                    if (nTxFee > 0)
                    {
                        nValue += nTxFee;
                        nTxFee = 0;
                    }
                    sub.debit = -nValue;

                    parts.append(sub);
                }
            }
            else
            {
                //
                // Mixed debit transaction, can't break down payees
                //
                parts.append(TransactionRecord(hash, nTime, TransactionRecord::Other, "", nNet, 0));
            }
        }
        
        BOOST_FOREACH(const CTxIn &txin, wtx.vin)
        {
            std::string addrStr = "?";
            if (wallet->mapWallet.count(txin.prevout.hash) > 0)
            {
                const CWalletTx &prevTx = wallet->mapWallet.find(txin.prevout.hash)->second;
                const CTxOut &prevout = prevTx.vout[txin.prevout.n];
                CBitcoinAddress forAddr;
                if (ExtractAddress(prevout.scriptPubKey, forAddr))
                {
                    addrStr = forAddr.ToString();
                }
            }
            
            BOOST_FOREACH(const CTxInfo &info, txin.infos)
            {
                int64 debit=0, credit=0;
                if (parts.size() == 1 && parts[0].type == TransactionRecord::SendToSelf)
                {
                    debit = parts[0].debit;
                    credit = parts[0].credit;
                    parts.pop_back();
                }
                TransactionRecord trec(hash, nTime, TransactionRecord::Info, addrStr, debit, credit);
                trec.info = info;
                parts.append(trec);
            }
        }
    }

    return parts;
}

void TransactionRecord::updateStatus(const CWalletTx &wtx)
{
    // Determine transaction status

    // Find the block the tx is in
    CBlockIndex* pindex = NULL;
    std::map<uint256, CBlockIndex*>::iterator mi = mapBlockIndex.find(wtx.hashBlock);
    if (mi != mapBlockIndex.end())
        pindex = (*mi).second;

    // Sort order, unrecorded transactions sort to the top
    status.sortKey = strprintf("%010d-%01d-%010u-%03d",
        (pindex ? pindex->nHeight : std::numeric_limits<int>::max()),
        (wtx.IsCoinBase() ? 1 : 0),
        wtx.nTimeReceived,
        idx);
    status.confirmed = wtx.IsConfirmed();
    status.depth = wtx.GetDepthInMainChain();
    status.cur_num_blocks = nBestHeight;

    if (!wtx.IsFinal())
    {
        if (wtx.nLockTime < LOCKTIME_THRESHOLD)
        {
            status.status = TransactionStatus::OpenUntilBlock;
            status.open_for = nBestHeight - wtx.nLockTime;
        }
        else
        {
            status.status = TransactionStatus::OpenUntilDate;
            status.open_for = wtx.nLockTime;
        }
    }
    else
    {
        if (GetAdjustedTime() - wtx.nTimeReceived > 2 * 60 && wtx.GetRequestCount() == 0)
        {
            status.status = TransactionStatus::Offline;
        }
        else if (status.depth < NumConfirmations)
        {
            status.status = TransactionStatus::Unconfirmed;
        }
        else
        {
            status.status = TransactionStatus::HaveConfirmations;
        }
    }

    // For generated transactions, determine maturity
    if(type == TransactionRecord::Generated || type == TransactionRecord::StakeMint)
    {
        int64 nCredit = wtx.GetCredit(true);
        if (nCredit == 0)
        {
            status.maturity = TransactionStatus::Immature;

            if (wtx.IsInMainChain())
            {
                status.matures_in = wtx.GetBlocksToMaturity();

                // Check if the block was requested by anyone
                if (GetAdjustedTime() - wtx.nTimeReceived > 2 * 60 && wtx.GetRequestCount() == 0)
                    status.maturity = TransactionStatus::MaturesWarning;
            }
            else
            {
                status.maturity = TransactionStatus::NotAccepted;
            }
        }
        else
        {
            status.maturity = TransactionStatus::Mature;
        }
    }
}

bool TransactionRecord::statusUpdateNeeded()
{
    return status.cur_num_blocks != nBestHeight;
}

std::string TransactionRecord::getTxID()
{
    return hash.ToString() + strprintf("-%03d", idx);
}

