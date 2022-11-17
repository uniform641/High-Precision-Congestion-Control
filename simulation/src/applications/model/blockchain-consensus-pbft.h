#ifndef BLOCKCHAIN_CONSENSUS_PBFT_H
#define BLOCKCHAIN_CONSENSUS_PBFT_H

#include <vector>
#include <algorithm>

#include "ns3/object.h"
#include "ns3/ptr.h"
#include "ns3/simulator.h"

#include "blockchain-common.h"
#include "blockchain-consensus-base.h"

namespace ns3 {
float blockchainConsensusPBFTLeaderTimeout = 100; // ms

class BlockchainConsensusPBFT : public BlockchainConsensusBase, public Object {
public:
    BlockchainConsensusPBFT();
    virtual ~BlockchainConsensusPBFT();

    static TypeId GetTypeId(void);

    // initialize consensus parameters
    void Init(Ptr<BlockchainBlockchain> blockchain,
              Ptr<BlockchainNetworkBase> network,
              Ptr<BlockchainTxpool> txpool,
              Ptr<BlockchainVerifier> verifier,
              Ptr<std::vector<NodeAddress>> neighborId,
              uint64_t nodeIndex) override;
    // start consensus
    void Start() override;
    // stop consensus
    void Stop() override;
    BlockchainConsensusAlgorithm GetConsensusAlgorithmType() override;
    BlockchainConsensusNodeState GetConsensusNodeState() override;
    BlockchainConsensusNodeRole GetConsensusNodeRole() override;

    void UpdateNodeRole();
    bool IsLeader();
    void PackAndPreprepare();
    void Pack();
    void FetchTxs(Ptr<std::vector<Ptr<Transaction>>>, uint64_t minTxNum, float maxTime);
private:
    uint64_t m_view;
    uint64_t m_numBlock;
    uint64_t m_numNode;
    std::vector<NodeAddress> m_neighborId;
    uint64_t m_nodeIndex;
    NodeAddress m_nodeId;
    BlockchainConsensusNodeRole m_nodeRole;
    BlockchainConsensusNodeState m_nodeState;
    Ptr<Block> m_blockToConsensus;

    Ptr<BlockchainBlockchain> m_blockchain;
    Ptr<BlockchainNetworkBase> m_network;
    Ptr<BlockchainTxpool> m_txpool;
    Ptr<BlockchainVerifier> m_verifier;

    uint64_t m_fetchTxAttemptInterval; // ms
};
}

#endif