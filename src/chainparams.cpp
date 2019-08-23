// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2017 The PIVX developers
// Copyright (c) 2019 The CBN Developers
// Copyright (c) 2019 The CBN Developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"
#include "bignum.h"
#include "random.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

using namespace std;
using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

/*
---------------
algorithm: quark
pzTimestamp: 20190823 CBN by ZioFabry
pubkey: 04678afdb0fe5548271967f1a67130b7105cd6a828e03909a67962e0ea1f61deb649f6bc3f4cef38c4f35504e51ec112de5c384df7ba0b8d578a4c702b6bf11d5f
bits: 504365040
time: 1566556888
merkle root hash: bde5e7c436152badd8eb13c3dfb89ebb5b388f1c00e5872d6544455f2291b91d
Searching for genesis hash...
nonce: 350780
genesis hash: 000003e617a4fa30e29e380303cc75e3f68b369343eed70c88daccaf0fafe402
*/

/**
 * Main network
 */

//! Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress>& vSeedsOut, const SeedSpec6* data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7 * 24 * 60 * 60;
    for (unsigned int i = 0; i < count; i++) {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

//   What makes a good checkpoint block?
// + Is surrounded by blocks with reasonable timestamps
//   (no blocks before with a timestamp after, none after with
//    timestamp before)
// + Contains no strange transactions
static Checkpoints::MapCheckpoints mapCheckpoints =
    boost::assign::map_list_of
    (    0, uint256("0x000003e617a4fa30e29e380303cc75e3f68b369343eed70c88daccaf0fafe402"));

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1566556888, // * UNIX timestamp of last checkpoint block
    0,          // * total number of transactions between genesis and last checkpoint (the tx=... number in the SetBestChain debug.log lines)
    1440        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of(0, uint256("0x000003e617a4fa30e29e380303cc75e3f68b369343eed70c88daccaf0fafe402"));

static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1566556888, // * UNIX timestamp of last checkpoint block
    0,          // * total number of transactions between genesis and last checkpoint (the tx=... number in the SetBestChain debug.log lines)
    1440        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of(0, uint256("0x000003e617a4fa30e29e380303cc75e3f68b369343eed70c88daccaf0fafe402"));
static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    1550524693, // * UNIX timestamp of last checkpoint block
    0,          // * total number of transactions between genesis and last checkpoint (the tx=... number in the SetBestChain debug.log lines)
    1440        // * estimated number of transactions per day after checkpoint
};

class CMainParams : public CChainParams
{
public:
    CMainParams()
    {
        networkID                      = CBaseChainParams::MAIN;
        strNetworkID                   = "main";

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0]             = 0x34;
        pchMessageStart[1]             = 0xd3;
        pchMessageStart[2]             = 0x22;
        pchMessageStart[3]             = 0xcc;

        vAlertPubKey                   = ParseHex("04224483a67480210035aa0921f58737bc08ed0867782832653590d5398acdc8a3415bf9d2e8496919ae44c10785ae99ac1587543d1ed98c1f6d1da30d74a86d55");
        nDefaultPort                   = 9538;
        nSubsidyHalvingInterval        = 1050000;
        nMaxReorganizationDepth        = 100;
        nEnforceBlockUpgradeMajority   = 750;
        nRejectBlockOutdatedMajority   = 950;
        nToCheckBlockUpgradeMajority   = 1000;
        nMinerThreads                  = 0;

        bnProofOfWorkLimit             = ~uint256(0) >> 20;
        nTargetTimespan                =  1 * 60; 
        nTargetSpacing                 =  1 * 60;  // CBN: 1 minute blocks during POW (block 1-200)

        bnProofOfStakeLimit            = ~uint256(0) >> 20;
        nTargetTimespanPOS             = 40 * 60; 
        nTargetSpacingPOS              =  1 * 60;  // CBN: 1 minute blocks during POS

        nMaturity                      = 5; // 6 block maturity (+1 elsewhere)
        nMasternodeCountDrift          = 20;
        nMaxMoneyOut                   = 1000000 * COIN; // 1 million max supply

        /** Height or Time Based Activations **/
        nLastPOWBlock                  = 1000;
        nModifierUpdateBlock           = 1;

/*
---------------
algorithm: quark
pzTimestamp: 20190823 CBN by ZioFabry
pubkey: 04678afdb0fe5548271967f1a67130b7105cd6a828e03909a67962e0ea1f61deb649f6bc3f4cef38c4f35504e51ec112de5c384df7ba0b8d578a4c702b6bf11d5f
bits: 504365040
time: 1566556888
merkle root hash: bde5e7c436152badd8eb13c3dfb89ebb5b388f1c00e5872d6544455f2291b91d
Searching for genesis hash...
nonce: 350780
genesis hash: 000003e617a4fa30e29e380303cc75e3f68b369343eed70c88daccaf0fafe402
*/
        const char* pszTimestamp       = "20190823 CBN by ZioFabry";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig         = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue           = 0 * COIN;
        txNew.vout[0].scriptPubKey     = CScript() << ParseHex("04678afdb0fe5548271967f1a67130b7105cd6a828e03909a67962e0ea1f61deb649f6bc3f4cef38c4f35504e51ec112de5c384df7ba0b8d578a4c702b6bf11d5f") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock          = 0;
        genesis.hashMerkleRoot         = genesis.BuildMerkleTree();
        genesis.nVersion               = 1;
        genesis.nTime                  = 1566556888;
        genesis.nBits                  = 504365040;
        genesis.nNonce                 = 350780;

        hashGenesisBlock               = genesis.GetHash();
        assert(hashGenesisBlock        == uint256("0x000003e617a4fa30e29e380303cc75e3f68b369343eed70c88daccaf0fafe402"));
        assert(genesis.hashMerkleRoot  == uint256("0xbde5e7c436152badd8eb13c3dfb89ebb5b388f1c00e5872d6544455f2291b91d"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,  28);  // Start with 'C' from https://en.bitcoin.it/wiki/List_of_address_prefixes
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,  63);  // Start with 'S' from https://en.bitcoin.it/wiki/List_of_address_prefixes
        base58Prefixes[SECRET_KEY]     = std::vector<unsigned char>(1, 193);  // from https://en.bitcoin.it/wiki/List_of_address_prefixes
        
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >(); // BIP32 pubkeys start with 'xpub' (Bitcoin defaults)
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >(); // BIP32 prvkeys start with 'xprv' (Bitcoin defaults)
        base58Prefixes[EXT_COIN_TYPE]  = boost::assign::list_of(0x80)(0x00)(0x92)(0xf1).convert_to_container<std::vector<unsigned char> >(); // BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md 109 	0x800092f1

        vFixedSeeds.clear();
        vSeeds.clear();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        vSeeds.push_back(CDNSSeedData("seed01.connectbusinessnet.com", "seed01.connectbusinessnet.com"));
        vSeeds.push_back(CDNSSeedData("seed02.connectbusinessnet.com", "seed02.connectbusinessnet.com"));
        vSeeds.push_back(CDNSSeedData("seed03.connectbusinessnet.com", "seed03.connectbusinessnet.com"));
        vSeeds.push_back(CDNSSeedData("seed04.connectbusinessnet.com", "seed04.connectbusinessnet.com"));
        vSeeds.push_back(CDNSSeedData("explorer.connectbusinessnet.com", "explorer.connectbusinessnet.com"));

        fMiningRequiresPeers           = true;
        fAllowMinDifficultyBlocks      = false;
        fDefaultConsistencyChecks      = false;
        fRequireStandard               = true;
        fMineBlocksOnDemand            = false;
        fSkipProofOfWorkCheck          = false;
        fTestnetToBeDeprecatedFieldRPC = false;
        fHeadersFirstSyncingActive     = false;

        nPoolMaxTransactions           = 3;
        strSporkKey                    = "0442ecc9fca281ba331d036e08db81b42c82a27f4912dfc4e38a010ed59fb5b60c91e864eef4999d8d7b4ba47b1a3482672df1edb0d0b1125ce5c9ce03c34d4984";
        strMasternodePoolDummyAddress  = "CdoAbRJs8rKsge9R9qEWoAamrBgatAU8JC";
        nStartMasternodePayments       = 1525192183; 

        nBudget_Fee_Confirmations      = 6; // Number of confirmations for the finalization fee

        strTreasuryAddress             = "";
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return data;
    }
};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CMainParams
{
public:
    CTestNetParams()
    {
        networkID                      = CBaseChainParams::TESTNET;
        strNetworkID                   = "test";
        pchMessageStart[0]             = 0x4b;
        pchMessageStart[1]             = 0x2e;
        pchMessageStart[2]             = 0x33;
        pchMessageStart[3]             = 0xbd;
        vAlertPubKey                   = ParseHex("048933f84c80766e9eb1c2388042c51a74786e0d5db146cff2b60ab3bff05a2d30c824c69c1b45e7527a0d5ea1c8069c5043c91692501206a8d8f4db67b07e4793");
        nDefaultPort                   = 19538;
        nEnforceBlockUpgradeMajority   = 51;
        nRejectBlockOutdatedMajority   = 75;
        nToCheckBlockUpgradeMajority   = 100;
        nMinerThreads                  = 0;

        bnProofOfWorkLimit             = ~uint256(0) >> 20;
        nTargetTimespan                =  1 * 60; 
        nTargetSpacing                 =  1 * 60;  // CBN: 1 minute blocks during POW (block 1-200) on testnet

        bnProofOfStakeLimit            = ~uint256(0) >> 20;
        nTargetTimespanPOS             =  40 * 60; 
        nTargetSpacingPOS              =   1 * 60;  // CBN: 1 minute blocks during POS on testnet

        nLastPOWBlock                  = 1000;
        nMaturity                      = 5;
        nMasternodeCountDrift          = 4;
        nModifierUpdateBlock           = 1;
        nMaxMoneyOut                   = 1000000 * COIN; // 1 million max supply

        //! Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime                  = 1566556888;
        genesis.nNonce                 = 350780;

        hashGenesisBlock               = genesis.GetHash();
        assert(hashGenesisBlock        == uint256("0x000003e617a4fa30e29e380303cc75e3f68b369343eed70c88daccaf0fafe402"));
        assert(genesis.hashMerkleRoot  == uint256("0xbde5e7c436152badd8eb13c3dfb89ebb5b388f1c00e5872d6544455f2291b91d"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,  88);  // Start with 'c' from https://en.bitcoin.it/wiki/List_of_address_prefixes
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 125);  // Start with 's' from https://en.bitcoin.it/wiki/List_of_address_prefixes
        base58Prefixes[SECRET_KEY]     = std::vector<unsigned char>(1, 193);  // from https://en.bitcoin.it/wiki/List_of_address_prefixes

        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >(); // BIP32 pubkeys start with 'xpub' (Bitcoin defaults)
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >(); // BIP32 prvkeys start with 'xprv' (Bitcoin defaults)
        base58Prefixes[EXT_COIN_TYPE]  = boost::assign::list_of(0x80)(0x00)(0x00)(0x01).convert_to_container<std::vector<unsigned char> >(); // Testnet BIP44 coin type is '1' (All coin's testnet default)
        
        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        fMiningRequiresPeers           = true;
        fAllowMinDifficultyBlocks      = false;
        fDefaultConsistencyChecks      = false;
        fRequireStandard               = false;
        fMineBlocksOnDemand            = false;
        fTestnetToBeDeprecatedFieldRPC = true;

        nPoolMaxTransactions           = 2;
        strSporkKey                    = "04a26ac821499207a8efcc279a8340b35102af41754570789a7be835bc0cb7426c9d9825abf9110fdb812dc278295ed075e8d52b825996fc5325351b0c5dfc43ba";
        strMasternodePoolDummyAddress  = "cU3MyatPLSVQQ96WAtxB5gstgW2qSxGzxs";
        nStartMasternodePayments       = genesis.nTime + 86400; // 24 hours after genesis
        nBudget_Fee_Confirmations      = 3; // Number of confirmations for the finalization fee. We have to make this very short
                                            // here because we only have a 8 block finalization window on testnet

        strTreasuryAddress             = "";
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataTestnet;
    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CTestNetParams
{
public:
    CRegTestParams()
    {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "regtest";
        strNetworkID = "regtest";
        pchMessageStart[0] = 0x20;
        pchMessageStart[1] = 0xee;
        pchMessageStart[2] = 0x32;
        pchMessageStart[3] = 0xbc;
        nSubsidyHalvingInterval = 150;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 1;
        nTargetTimespan = 24 * 60 * 60; // CBN: 1 day
        nTargetSpacing = 2 * 60;        // CBN: 1 minutes
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        genesis.nTime = 1566556888;
        genesis.nBits = 504365040;
        genesis.nNonce = 350780;

        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 14034;
        // assert(hashGenesisBlock        == uint256("0x000003e617a4fa30e29e380303cc75e3f68b369343eed70c88daccaf0fafe402"));

        vFixedSeeds.clear(); //! Regtest mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Regtest mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataRegtest;
    }
};
static CRegTestParams regTestParams;

/**
 * Unit test
 */
class CUnitTestParams : public CMainParams, public CModifiableParams
{
public:
    CUnitTestParams()
    {
        networkID = CBaseChainParams::UNITTEST;
        strNetworkID = "unittest";
        nDefaultPort = 51478;
        vFixedSeeds.clear(); //! Unit test mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Unit test mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fAllowMinDifficultyBlocks = false;
        fMineBlocksOnDemand = true;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        // UnitTest share the same checkpoints as MAIN
        return data;
    }

    //! Published setters to allow changing values in unit test cases
    virtual void setSubsidyHalvingInterval(int anSubsidyHalvingInterval) { nSubsidyHalvingInterval = anSubsidyHalvingInterval; }
    virtual void setEnforceBlockUpgradeMajority(int anEnforceBlockUpgradeMajority) { nEnforceBlockUpgradeMajority = anEnforceBlockUpgradeMajority; }
    virtual void setRejectBlockOutdatedMajority(int anRejectBlockOutdatedMajority) { nRejectBlockOutdatedMajority = anRejectBlockOutdatedMajority; }
    virtual void setToCheckBlockUpgradeMajority(int anToCheckBlockUpgradeMajority) { nToCheckBlockUpgradeMajority = anToCheckBlockUpgradeMajority; }
    virtual void setDefaultConsistencyChecks(bool afDefaultConsistencyChecks) { fDefaultConsistencyChecks = afDefaultConsistencyChecks; }
    virtual void setAllowMinDifficultyBlocks(bool afAllowMinDifficultyBlocks) { fAllowMinDifficultyBlocks = afAllowMinDifficultyBlocks; }
    virtual void setSkipProofOfWorkCheck(bool afSkipProofOfWorkCheck) { fSkipProofOfWorkCheck = afSkipProofOfWorkCheck; }
};
static CUnitTestParams unitTestParams;


static CChainParams* pCurrentParams = 0;

CModifiableParams* ModifiableParams()
{
    assert(pCurrentParams);
    assert(pCurrentParams == &unitTestParams);
    return (CModifiableParams*)&unitTestParams;
}

const CChainParams& Params()
{
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(CBaseChainParams::Network network)
{
    switch (network) {
    case CBaseChainParams::MAIN:
        return mainParams;
    case CBaseChainParams::TESTNET:
        return testNetParams;
    case CBaseChainParams::REGTEST:
        return regTestParams;
    case CBaseChainParams::UNITTEST:
        return unitTestParams;
    default:
        assert(false && "Unimplemented network");
        return mainParams;
    }
}

void SelectParams(CBaseChainParams::Network network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;

    SelectParams(network);
    return true;
}
