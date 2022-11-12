#ifndef BLOCKCHAIN_CONSENSUS_BASE_H
#define BLOCKCHAIN_CONSENSUS_BASE_H

#include <ns3/object.h>
#include <ns3/ptr.h>
#include <blockchain-blockchain.h>
#include <blockchain-network-base.h>
#include <blockchain-verifier.h>
#include <blockchain-txpool.h>


namespace ns3 {
enum BlockchainConsensusAlgorithm {
    BCA_NONE,
    BCA_PBFT,
    BCA_RAFT
};
enum BlockchainConsensusNodeState {
    BCNS_NONE,
    BCNS_INIT,
    BCNS_PREPARE,
    BCNS_COMMIT,
    BCNS_DONE
};
enum BlockchainConsensusNodeRole {
    BCNR_NONE,
    BCNR_LEADER,
    BCNR_FOLLOWER,
    BCNR_CANDIDATE
};

class BlockchainConsensusBase : public Object {
public:
    Ptr<BlockchainBlockchain> m_blockchain;
    Ptr<BlockchainNetworkBase> m_network;
    Ptr<BlockchainTxpool> m_txpool;
    Ptr<BlockchainVerifier> m_verifier;

    BlockchainConsensusAlgorithm algorithm;
    BlockchainConsensusNodeState state;
    BlockchainConsensusNodeRole role;

    static TypeId GetTypeId(void);
    BlockchainConsensusBase();
    
    virtual ~BlockchainConsensusBase();
};
}

#endif