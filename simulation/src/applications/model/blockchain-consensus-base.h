#ifndef BLOCKCHAIN_CONSENSUS_BASE_H
#define BLOCKCHAIN_CONSENSUS_BASE_H

#include "ns3/object.h"
#include "ns3/ptr.h"
#include "ns3/log.h"

#include "blockchain-blockchain.h"
#include "blockchain-network-base.h"
#include "blockchain-verifier.h"
#include "blockchain-txpool.h"
#include "blockchain-common.h"


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

    BlockchainConsensusBase() {
        NS_LOG_FUNCTION_NOARGS();
    }

    virtual ~BlockchainConsensusBase() {
        NS_LOG_FUNCTION_NOARGS();
    }

    static TypeId GetTypeId(void) {
        static TypeId tid = TypeId("ns3::BlockchainConsensusBase")
                .SetParent<Object>()
                .AddConstructor<BlockchainConsensusBase>();
        return tid;
    }
    
    // initialize consensus parameters
    virtual void Init() {

    }

    // start consensus
    virtual void Start() {

    }

    // stop consensus
    virtual void Stop() {

    }

    virtual void SetBlockchain(Ptr<BlockchainBlockchain> blockchain) {

    }

    virtual void SetNetwork(Ptr<BlockchainNetworkBase> network) {

    }

    virtual void SetTxpool(Ptr<BlockchainTxpool> txpool) {

    }

    virtual void SetVerifier(Ptr<BlockchainVerifier> verifier) {

    }
};
}

#endif