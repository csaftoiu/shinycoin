#include <boost/test/unit_test.hpp>

#include "main.h"
#include "wallet.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(transaction_tests)

BOOST_AUTO_TEST_CASE(basic_transaction_tests)
{
    // Random real transaction (183fdaa4f69c9824f21679f4f33be650c80bebe4891a8d39cc5b68b8617ece00)
    unsigned char ch[] = {0x01, 0x00, 0x00, 0x00, 0x12, 0x17, 0xb3, 0x53, 0x03, 0x3b, 0xbc, 0xd2, 0xe9, 0x73, 0xe5, 0x3f, 0xd6, 0x75, 0x16, 0x34, 0xfc, 0xb5, 0x47, 0x2c, 0x1a, 0x51, 0xbd, 0xcb, 0xd2, 0x53, 0xda, 0x6e, 0xa1, 0x40, 0x8f, 0xc9, 0x9c, 0x60, 0xfc, 0x20, 0x18, 0x00, 0x00, 0x00, 0x00, 0x49, 0x48, 0x30, 0x45, 0x02, 0x20, 0x41, 0x44, 0x49, 0x7d, 0xf1, 0x7b, 0x9a, 0xcb, 0x4c, 0xe4, 0xa2, 0x43, 0xf1, 0xbe, 0xb7, 0x93, 0x5e, 0xdb, 0xd4, 0x9a, 0xab, 0xc5, 0x2e, 0x56, 0x9f, 0xbf, 0x4d, 0x25, 0xd4, 0x06, 0xbe, 0x83, 0x02, 0x21, 0x00, 0xc1, 0x2c, 0x0c, 0x43, 0x2e, 0x8a, 0xe1, 0x1d, 0x99, 0x84, 0x31, 0xa8, 0x60, 0x9d, 0x6c, 0x15, 0xf1, 0x99, 0xc7, 0x2e, 0x31, 0x8d, 0x13, 0xfb, 0x4e, 0x7a, 0x9b, 0x01, 0xc3, 0x8f, 0x23, 0xf7, 0x01, 0xff, 0xff, 0xff, 0xff, 0x00, 0x53, 0x7d, 0x16, 0x31, 0x6e, 0xaf, 0xda, 0xdc, 0xf8, 0xa9, 0x26, 0x83, 0x46, 0x0d, 0x0b, 0xab, 0xbc, 0x20, 0xe3, 0x3d, 0x1a, 0x5b, 0x09, 0x25, 0x7e, 0x2a, 0xc9, 0xca, 0x1a, 0x23, 0xdc, 0xca, 0x00, 0x00, 0x00, 0x00, 0x4a, 0x49, 0x30, 0x46, 0x02, 0x21, 0x00, 0xf5, 0x77, 0xaa, 0x78, 0xa8, 0x7e, 0x23, 0x4c, 0x10, 0x6a, 0xd4, 0xca, 0xca, 0xfe, 0x3b, 0xd7, 0x7c, 0x0f, 0x0b, 0xe0, 0xb0, 0x99, 0xa2, 0x45, 0x35, 0xc1, 0xe7, 0x37, 0x4a, 0x91, 0xd3, 0xfc, 0x02, 0x21, 0x00, 0x88, 0x51, 0x01, 0x40, 0x7a, 0x31, 0x2f, 0x79, 0xfc, 0x09, 0x2c, 0x84, 0xc3, 0xdb, 0x4e, 0x16, 0xda, 0x5d, 0xe7, 0x5c, 0xe5, 0xa9, 0xdc, 0x06, 0x71, 0xae, 0x96, 0x1c, 0x1f, 0x89, 0x2b, 0x9a, 0x01, 0xff, 0xff, 0xff, 0xff, 0x00, 0xd2, 0xf3, 0x3b, 0x07, 0x2d, 0xe7, 0x4b, 0xdd, 0xf1, 0xde, 0x9e, 0x54, 0x1c, 0xc4, 0x03, 0x6e, 0x07, 0xd5, 0xed, 0x78, 0x6a, 0xdc, 0x5b, 0x87, 0x42, 0x9b, 0xe7, 0x09, 0xb8, 0xc8, 0x27, 0x86, 0x0d, 0x00, 0x00, 0x00, 0x6b, 0x48, 0x30, 0x45, 0x02, 0x20, 0x12, 0x57, 0xa3, 0x9d, 0xb4, 0xf7, 0x7b, 0x78, 0x0a, 0x8f, 0x6b, 0x4b, 0x8c, 0xfc, 0xfd, 0xb0, 0xd5, 0x20, 0xa8, 0x45, 0x8c, 0x1a, 0x12, 0x0d, 0xe8, 0x9f, 0xee, 0xeb, 0xad, 0xb4, 0x61, 0x7e, 0x02, 0x21, 0x00, 0xe1, 0xb2, 0x38, 0xaf, 0x52, 0xfe, 0x81, 0xae, 0x27, 0x94, 0xd8, 0xbb, 0x80, 0xd2, 0xd2, 0x46, 0xfd, 0x0f, 0x52, 0x77, 0xfc, 0x61, 0x14, 0xbf, 0x67, 0x5a, 0xe5, 0x82, 0x62, 0xd9, 0x43, 0x42, 0x01, 0x21, 0x03, 0x17, 0x97, 0x98, 0x66, 0x46, 0x8f, 0xe7, 0x32, 0x57, 0xbd, 0x87, 0xa7, 0x8a, 0x2d, 0xff, 0x61, 0x51, 0x0a, 0x29, 0x02, 0x86, 0xcd, 0x88, 0x17, 0x2a, 0x1a, 0xa7, 0xb9, 0xe2, 0xee, 0x34, 0x52, 0xff, 0xff, 0xff, 0xff, 0x00, 0x19, 0x00, 0xf4, 0x54, 0x54, 0x03, 0x00, 0x00, 0x00, 0x00, 0x19, 0x76, 0xa9, 0x14, 0x3a, 0xe0, 0x3b, 0x3f, 0x54, 0x68, 0x95, 0xd9, 0x4d, 0x78, 0xfd, 0x6d, 0x74, 0x5f, 0x16, 0x94, 0x50, 0xce, 0x79, 0x94, 0x88, 0xac, 0x00, 0x6e, 0xf4, 0x11, 0x01, 0x00, 0x00, 0x00, 0x00, 0x19, 0x76, 0xa9, 0x14, 0xfc, 0x1b, 0x9c, 0x8f, 0xc9, 0xea, 0x9a, 0x35, 0xcb, 0x8f, 0x10, 0x17, 0x2e, 0xbd, 0xc3, 0x8f, 0x94, 0x5b, 0x45, 0xf4, 0x88, 0xac, 0x00, 0xcc, 0xdd, 0x65, 0x01, 0x00, 0x00, 0x00, 0x00, 0x19, 0x76, 0xa9, 0x14, 0x68, 0x3b, 0x3c, 0x00, 0xbd, 0x1e, 0x1e, 0xf9, 0x68, 0xb5, 0xa0, 0xcf, 0xcc, 0x47, 0xb4, 0x8e, 0xe4, 0xc1, 0x4b, 0xb4, 0x88, 0xac, 0x00, 0x25, 0xd6, 0xd8, 0x01, 0x00, 0x00, 0x00, 0x00, 0x19, 0x76, 0xa9, 0x14, 0xb6, 0x51, 0xcb, 0x47, 0xbd, 0xde, 0x6b, 0x66, 0x5c, 0x07, 0x17, 0xb3, 0xca, 0x88, 0x45, 0xb3, 0x75, 0x16, 0x61, 0xe6, 0x88, 0xac, 0x00, 0x8b, 0x1f, 0xed, 0x04, 0x00, 0x00, 0x00, 0x00, 0x19, 0x76, 0xa9, 0x14, 0x9b, 0x2d, 0x1b, 0xb9, 0xf6, 0x06, 0xf8, 0x0a, 0x9e, 0x8f, 0xbe, 0x95, 0x60, 0x8a, 0x10, 0x6b, 0x30, 0x80, 0x05, 0x48, 0x88, 0xac, 0x00, 0x4a, 0x48, 0x5d, 0x01, 0x00, 0x00, 0x00, 0x00, 0x19, 0x76, 0xa9, 0x14, 0x93, 0x32, 0x1d, 0xf4, 0xf3, 0xad, 0x08, 0x86, 0x1b, 0x52, 0xba, 0x33, 0x47, 0x1c, 0xde, 0x11, 0x6f, 0x29, 0xd3, 0x18, 0x88, 0xac, 0x00, 0x77, 0x0a, 0x26, 0x00, 0x00, 0x00, 0x00, 0x00, 0x19, 0x76, 0xa9, 0x14, 0xec, 0x12, 0xd7, 0xed, 0xb3, 0x98, 0x97, 0x50, 0x1f, 0x14, 0x8e, 0xea, 0x03, 0x81, 0xc6, 0x2b, 0xeb, 0x09, 0xd5, 0xde, 0x88, 0xac, 0x00, 0x54, 0x91, 0xc6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x19, 0x76, 0xa9, 0x14, 0x43, 0x4f, 0xa9, 0xfa, 0x34, 0x91, 0xb1, 0xc5, 0x12, 0x45, 0x29, 0x8a, 0x01, 0x27, 0xcd, 0x5d, 0x6f, 0x9e, 0x5f, 0x85, 0x88, 0xac, 0x00, 0x54, 0x94, 0xad, 0x09, 0x00, 0x00, 0x00, 0x00, 0x19, 0x76, 0xa9, 0x14, 0x60, 0xda, 0x5e, 0xe2, 0xf5, 0x44, 0xa1, 0xb1, 0x4d, 0xfd, 0x46, 0xa8, 0x79, 0xe2, 0xe3, 0x5a, 0xee, 0x5c, 0x9d, 0x7c, 0x88, 0xac, 0x00, 0x99, 0x9e, 0x45, 0x00, 0x00, 0x00, 0x00, 0x00, 0x19, 0x76, 0xa9, 0x14, 0x9c, 0x30, 0xe0, 0x41, 0xff, 0x45, 0xb5, 0x64, 0x06, 0x8f, 0x2a, 0x10, 0xac, 0x09, 0x55, 0x7f, 0xa7, 0x96, 0x2e, 0x0c, 0x88, 0xac, 0x00, 0xfc, 0x24, 0x31, 0x07, 0x00, 0x00, 0x00, 0x00, 0x19, 0x76, 0xa9, 0x14, 0x12, 0x43, 0x49, 0x1a, 0x06, 0x7c, 0x13, 0x4c, 0xff, 0xa0, 0xdb, 0xcd, 0xa4, 0x70, 0xf0, 0x43, 0x84, 0x04, 0x58, 0x0e, 0x88, 0xac, 0x00, 0x68, 0xc2, 0xe1, 0x04, 0x00, 0x00, 0x00, 0x00, 0x19, 0x76, 0xa9, 0x14, 0xe7, 0xd0, 0x80, 0xe3, 0xad, 0xcc, 0x38, 0x5d, 0x7c, 0xdf, 0x34, 0x6b, 0xcd, 0x4b, 0xb8, 0xac, 0xb5, 0xd9, 0xd5, 0xfb, 0x88, 0xac, 0x00, 0x8a, 0x01, 0x59, 0x00, 0x00, 0x00, 0x00, 0x00, 0x19, 0x76, 0xa9, 0x14, 0x3c, 0xbf, 0x43, 0xd0, 0x4e, 0xec, 0xf2, 0xd1, 0xbb, 0x86, 0x7b, 0xe3, 0xa4, 0xea, 0x0f, 0xb1, 0xa3, 0xce, 0x53, 0x21, 0x88, 0xac, 0x00, 0x65, 0x48, 0x2d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x19, 0x76, 0xa9, 0x14, 0xb5, 0xa3, 0xfd, 0x1c, 0xb9, 0x57, 0xd9, 0x81, 0x29, 0xe9, 0x38, 0x78, 0xdf, 0xfb, 0x1f, 0x07, 0xe1, 0xfd, 0x4b, 0x21, 0x88, 0xac, 0x00, 0x3a, 0xba, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x19, 0x76, 0xa9, 0x14, 0x78, 0x77, 0x3b, 0x83, 0x8c, 0x4b, 0xa6, 0x62, 0xec, 0xfc, 0x40, 0xba, 0xff, 0x3d, 0x56, 0xec, 0x3b, 0xc9, 0x4d, 0x3b, 0x88, 0xac, 0x00, 0x57, 0x22, 0x2a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x19, 0x76, 0xa9, 0x14, 0x53, 0xf7, 0xf4, 0x48, 0xd1, 0x36, 0x11, 0xbc, 0xe6, 0x2b, 0xf9, 0xc3, 0xe1, 0x19, 0xbc, 0x92, 0x3b, 0x98, 0xe4, 0x6d, 0x88, 0xac, 0x00, 0x81, 0xe9, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x19, 0x76, 0xa9, 0x14, 0xdb, 0xca, 0xf5, 0xe1, 0xd0, 0xf8, 0xce, 0xb8, 0x37, 0x43, 0x26, 0x19, 0xa8, 0x0d, 0xf6, 0xf9, 0xd3, 0xe3, 0x14, 0x7e, 0x88, 0xac, 0x00, 0xf0, 0xba, 0x64, 0x00, 0x00, 0x00, 0x00, 0x00, 0x19, 0x76, 0xa9, 0x14, 0xb1, 0x9c, 0x47, 0xd9, 0x5c, 0x81, 0x86, 0xf1, 0x8b, 0xff, 0xd3, 0x4c, 0x96, 0xbc, 0xd9, 0x56, 0xe9, 0xe1, 0x17, 0xfd, 0x88, 0xac, 0x00, 0xa1, 0xa5, 0x04, 0x01, 0x00, 0x00, 0x00, 0x00, 0x19, 0x76, 0xa9, 0x14, 0xde, 0x4e, 0x4c, 0x70, 0x61, 0x97, 0x5c, 0xff, 0x27, 0x42, 0x25, 0xc6, 0x31, 0x03, 0x5f, 0xdf, 0x48, 0x2f, 0xbd, 0x77, 0x88, 0xac, 0x00, 0x87, 0xed, 0x69, 0x00, 0x00, 0x00, 0x00, 0x00, 0x19, 0x76, 0xa9, 0x14, 0x64, 0x2b, 0xf7, 0x0b, 0x3f, 0x5a, 0xae, 0x18, 0x82, 0x64, 0x0e, 0xf6, 0x88, 0x09, 0x3c, 0x50, 0x59, 0x47, 0x65, 0x4e, 0x88, 0xac, 0x00, 0xef, 0x25, 0x19, 0x05, 0x00, 0x00, 0x00, 0x00, 0x19, 0x76, 0xa9, 0x14, 0xf1, 0x25, 0x77, 0xa8, 0x2e, 0x7e, 0x19, 0x8c, 0x4d, 0xe0, 0x0d, 0x9b, 0x8b, 0x13, 0x07, 0xc2, 0x76, 0x13, 0xc1, 0xe6, 0x88, 0xac, 0x00, 0x25, 0x3c, 0x9b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x19, 0x76, 0xa9, 0x14, 0x41, 0x9a, 0x1b, 0x82, 0xcd, 0x36, 0x37, 0x4e, 0xba, 0xe9, 0x8c, 0x9f, 0xd0, 0x73, 0x0b, 0x7b, 0xf4, 0x49, 0x48, 0x65, 0x88, 0xac, 0x00, 0x3e, 0xa7, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x19, 0x76, 0xa9, 0x14, 0xda, 0xfc, 0x43, 0x45, 0xd7, 0xe6, 0x05, 0x6e, 0x84, 0x18, 0x2c, 0xc4, 0x4d, 0x69, 0x8c, 0x27, 0x65, 0x20, 0xac, 0x87, 0x88, 0xac, 0x00, 0x84, 0x4a, 0x11, 0x00, 0x00, 0x00, 0x00, 0x00, 0x19, 0x76, 0xa9, 0x14, 0xde, 0xef, 0xa2, 0x2f, 0x48, 0xac, 0xe4, 0x6e, 0xff, 0xa7, 0x7c, 0x12, 0xd0, 0x44, 0x06, 0x5a, 0xce, 0x55, 0x73, 0x6b, 0x88, 0xac, 0x00, 0x05, 0x9b, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x19, 0x76, 0xa9, 0x14, 0x8d, 0xbc, 0xa0, 0xf6, 0xe9, 0xca, 0x03, 0xed, 0x23, 0x44, 0x00, 0x0c, 0x3e, 0xdc, 0x6a, 0xab, 0x8c, 0x92, 0xc9, 0xa2, 0x88, 0xac, 0x00, 0x00, 0x00, 0x00};
    
    vector<unsigned char> vch(ch, ch + sizeof(ch));
    CDataStream stream(vch, SER_DISK, CLIENT_VERSION);
    CTransaction tx;
    stream >> tx;
    BOOST_CHECK_MESSAGE(tx.CheckTransaction(), "Simple deserialized transaction should be valid.");

    // Check that duplicate txins fail
    tx.vin.push_back(tx.vin[0]);
    BOOST_CHECK_MESSAGE(!tx.CheckTransaction(), "Transaction with duplicate txins should be invalid.");
}

//
// Helper: create two dummy transactions, each with
// two outputs.  The first has 11 and 50 CENT outputs
// paid to a TX_PUBKEY, the second 21 and 22 CENT outputs
// paid to a TX_PUBKEYHASH.
//
static std::vector<CTransaction>
SetupDummyInputs(CBasicKeyStore& keystoreRet, MapPrevTx& inputsRet)
{
    std::vector<CTransaction> dummyTransactions;
    dummyTransactions.resize(2);

    // Add some keys to the keystore:
    CKey key[4];
    for (int i = 0; i < 4; i++)
    {
        key[i].MakeNewKey(i % 2);
        keystoreRet.AddKey(key[i]);
    }

    // Create some dummy input transactions
    dummyTransactions[0].vout.resize(2);
    dummyTransactions[0].vout[0].nValue = 11*CENT;
    dummyTransactions[0].vout[0].scriptPubKey << key[0].GetPubKey() << OP_CHECKSIG;
    dummyTransactions[0].vout[1].nValue = 50*CENT;
    dummyTransactions[0].vout[1].scriptPubKey << key[1].GetPubKey() << OP_CHECKSIG;
    inputsRet[dummyTransactions[0].GetHash()] = make_pair(CTxIndex(), dummyTransactions[0]);

    dummyTransactions[1].vout.resize(2);
    dummyTransactions[1].vout[0].nValue = 21*CENT;
    dummyTransactions[1].vout[0].scriptPubKey.SetBitcoinAddress(key[2].GetPubKey());
    dummyTransactions[1].vout[1].nValue = 22*CENT;
    dummyTransactions[1].vout[1].scriptPubKey.SetBitcoinAddress(key[3].GetPubKey());
    inputsRet[dummyTransactions[1].GetHash()] = make_pair(CTxIndex(), dummyTransactions[1]);

    return dummyTransactions;
}

BOOST_AUTO_TEST_CASE(test_Get)
{
    CBasicKeyStore keystore;
    MapPrevTx dummyInputs;
    std::vector<CTransaction> dummyTransactions = SetupDummyInputs(keystore, dummyInputs);

    CTransaction t1;
    t1.vin.resize(3);
    t1.vin[0].prevout.hash = dummyTransactions[0].GetHash();
    t1.vin[0].prevout.n = 1;
    t1.vin[0].scriptSig << std::vector<unsigned char>(65, 0);
    t1.vin[1].prevout.hash = dummyTransactions[1].GetHash();
    t1.vin[1].prevout.n = 0;
    t1.vin[1].scriptSig << std::vector<unsigned char>(65, 0) << std::vector<unsigned char>(33, 4);
    t1.vin[2].prevout.hash = dummyTransactions[1].GetHash();
    t1.vin[2].prevout.n = 1;
    t1.vin[2].scriptSig << std::vector<unsigned char>(65, 0) << std::vector<unsigned char>(33, 4);
    t1.vout.resize(2);
    t1.vout[0].nValue = 90*CENT;
    t1.vout[0].scriptPubKey << OP_1;

    BOOST_CHECK(t1.AreInputsStandard(dummyInputs));
    BOOST_CHECK_EQUAL(t1.GetValueIn(cidShinys, dummyInputs), (50+21+22)*CENT);

    // Adding extra junk to the scriptSig should make it non-standard:
    t1.vin[0].scriptSig << OP_11;
    BOOST_CHECK(!t1.AreInputsStandard(dummyInputs));

    // ... as should not having enough:
    t1.vin[0].scriptSig = CScript();
    BOOST_CHECK(!t1.AreInputsStandard(dummyInputs));
}

BOOST_AUTO_TEST_CASE(test_GetThrow)
{
    CBasicKeyStore keystore;
    MapPrevTx dummyInputs;
    std::vector<CTransaction> dummyTransactions = SetupDummyInputs(keystore, dummyInputs);

    MapPrevTx missingInputs;

    CTransaction t1;
    t1.vin.resize(3);
    t1.vin[0].prevout.hash = dummyTransactions[0].GetHash();
    t1.vin[0].prevout.n = 0;
    t1.vin[1].prevout.hash = dummyTransactions[1].GetHash();;
    t1.vin[1].prevout.n = 0;
    t1.vin[2].prevout.hash = dummyTransactions[1].GetHash();;
    t1.vin[2].prevout.n = 1;
    t1.vout.resize(2);
    t1.vout[0].nValue = 90*CENT;
    t1.vout[0].scriptPubKey << OP_1;

    BOOST_CHECK_THROW(t1.AreInputsStandard(missingInputs), runtime_error);
    BOOST_CHECK_THROW(t1.GetValueIn(cidShinys, missingInputs), runtime_error);
}

BOOST_AUTO_TEST_SUITE_END()
