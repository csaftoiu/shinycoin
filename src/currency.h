// Copyright (c) 2014 Claudiu Saftoiu

// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
#ifndef SHINYCOIN_CURRENCY_H
#define SHINYCOIN_CURRENCY_H

#include "serialize.h"

#include <vector>


class CScript;
class CTransaction;


typedef std::vector<uint8_t> CurrencyId;
extern CurrencyId cidShinys;


class CCurrency {
public:
    CurrencyId cid;
    std::string strName;
    int64 nTotalUnits;
    int64 nDivisibility;
    CScript scriptPubKey;
    
    IMPLEMENT_SERIALIZE
    (
        READWRITE(cid);
        READWRITE(strName);
        READWRITE(nTotalUnits);
        READWRITE(nDivisibility);
        READWRITE(scriptPubKey);
    )
    
    bool VerifySignature(const CScript &scriptSig, const CTransaction &tx) const;
};

#endif // SHINYCOIN_CURRENCY_H