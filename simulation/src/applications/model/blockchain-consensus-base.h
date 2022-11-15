#ifndef BLOCKCHAIN_CONSENSUS_BASE_H
#define BLOCKCHAIN_CONSENSUS_BASE_H

#include <string>

#include "ns3/object.h"
#include "ns3/ptr.h"
#include "ns3/log.h"

#include "blockchain-blockchain.h"
#include "blockchain-network-base.h"
#include "blockchain-verifier.h"
#include "blockchain-txpool.h"
#include "blockchain-common.h"
#include "blockchain-consensus-pbft.h"
#include "blockchain-consensus-raft.h"


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
    BlockchainConsensusBase();
    virtual ~BlockchainConsensusBase();

    static TypeId GetTypeId(void);
    
    // initialize consensus parameters
    virtual void Init(Ptr<BlockchainBlockchain> blockchain,
                      Ptr<BlockchainNetworkBase> network,
                      Ptr<BlockchainTxpool> txpool,
                      Ptr<BlockchainVerifier> verifier,
                      std::string consensusName);
    // start consensus
    virtual void Start();
    // stop consensus
    virtual void Stop();
    virtual Ptr<BlockchainBlockchain> GetBlockchain();
    virtual Ptr<BlockchainNetworkBase> GetNetwork();
    virtual Ptr<BlockchainTxpool> GetTxpool();
    virtual Ptr<BlockchainVerifier> GetVerifier();

private:
    Ptr<BlockchainBlockchain> m_blockchain;
    Ptr<BlockchainNetworkBase> m_network;
    Ptr<BlockchainTxpool> m_txpool;
    Ptr<BlockchainVerifier> m_verifier;

    BlockchainConsensusAlgorithm algorithm;
    BlockchainConsensusNodeState state;
    BlockchainConsensusNodeRole role;

};

BlockchainConsensusAlgorithm ConsensusAlgorithmType(std::string consensus);
Ptr<BlockchainConsensusBase> GetConsensusAlgorithm(std::string consensus);
}

#endif