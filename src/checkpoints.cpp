// Copyright (c) 2009-2012 The Bitcoin developers
// Copyright (c) 2011-2012 Litecoin Developers
// Copyright (c) 2013-2024 Bells Developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <boost/assign/list_of.hpp> // for 'map_list_of()'
#include <boost/foreach.hpp>

#include "checkpoints.h"

#include "main.h"
#include "uint256.h"

namespace Checkpoints
{
    typedef std::map<int, uint256> MapCheckpoints;

    //
    // What makes a good checkpoint block?
    // + Is surrounded by blocks with reasonable timestamps
    //   (no blocks before with a timestamp after, none after with
    //    timestamp before)
    // + Contains no strange transactions
    //

	// no checkpoint now, can be added in later releases
    static MapCheckpoints mapCheckpoints =
            boost::assign::map_list_of
            (  0, uint256("0xe5be24df57c43a82d15c2f06bda961296948f8f8eb48501bed1efb929afe0698"))
            (  1000, uint256("0xbda6660ca8dedd6205bf1afd68b1ee0479c293899d308325bbf921adaeafc459"))
            (  10000, uint256("0x6672369ac18c1597d9d062b10847cc92d6fba6218a63291f258450bae789f774"))
            (  25000, uint256("0x2910fc9061c1d458b3104fc7cb3fa3c23dbc8370af203c683a5d09e2f062c0cd"))
            (  50000, uint256("0xee8a74953afdae365ec3d2bc003590b594bd51b2f10e25be5d1960f1e12c6609"))
            (  75000, uint256("0x133b93343f032c06dcbd4b2607f0427fca1a1940279b9d1f9ef1475a37862f9e"))
            (  100000, uint256("0x707c4d80b012f540d1ee4021ad4214a187e7197504f5a0b67b4ae87e2491ff4c"))
            (  110000, uint256("0x4e903f691d8434af6a81091e2ddd832fd74aefd5acc79837bc605b183ddffdb3"))
            (  125000, uint256("0xddc37d2f69cc22dd3ffe482442821cee466b899fa706081bc7f425ab66761f26"))
            (  134000, uint256("0x951580c3396b2058eb8f38cde780dc57cf2ec511b954a18f54beb8f4652df35f"))
			;


    bool CheckBlock(int nHeight, const uint256& hash)
    {
        if (fTestNet) return true; // Testnet has no checkpoints

        MapCheckpoints::const_iterator i = mapCheckpoints.find(nHeight);
        if (i == mapCheckpoints.end()) return true;
        return hash == i->second;
		// return true;
    }

    int GetTotalBlocksEstimate()
    {
        if (fTestNet) return 0;
	
        return mapCheckpoints.rbegin()->first;
		// return 0;
    }

    CBlockIndex* GetLastCheckpoint(const std::map<uint256, CBlockIndex*>& mapBlockIndex)
    {
        if (fTestNet) return NULL;

        BOOST_REVERSE_FOREACH(const MapCheckpoints::value_type& i, mapCheckpoints)
        {
            const uint256& hash = i.second;
            std::map<uint256, CBlockIndex*>::const_iterator t = mapBlockIndex.find(hash);
            if (t != mapBlockIndex.end())
                return t->second;
				// return NULL;
        }
        return NULL;
    }
}
