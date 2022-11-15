#ifndef BLOCKCHAIN_CONSENSUS_PBFT_H
#define BLOCKCHAIN_CONSENSUS_PBFT_H

#include "ns3/object.h"
#include "ns3/ptr.h"

#include "blockchain-common.h"
#include "blockchain-consensus-base.h"

namespace ns3 {
class BlockchainConsensusPBFT : public BlockchainConsensusBase, public Object {
public:
    static TypeId GetTypeId(void);
};
}

#endif