// Copyright (c) 2014 Claudiu Saftoiu

// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "currency.h"
#include "script.h"
#include "main.h"


CurrencyId cidShinys;


bool CCurrency::VerifySignature(const CScript &scriptSig, const CTransaction &tx) const {
    return VerifyScript(scriptSig, scriptPubKey, tx, 0, 0);
}
