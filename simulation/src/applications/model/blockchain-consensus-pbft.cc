#include "blockchain-consensus-pbft.h"

namespace ns3 {
NS_LOG_COMPONENT_DEFINE("BlockchainConsensusPBFT");
NS_OBJECT_ENSURE_REGISTERED(BlockchainConsensusPBFT);

BlockchainConsensusPBFT::BlockchainConsensusPBFT() {
    NS_LOG_FUNCTION_NOARGS();
}

BlockchainConsensusPBFT::~BlockchainConsensusPBFT() {
    NS_LOG_FUNCTION_NOARGS();
}

TypeId BlockchainConsensusPBFT::GetTypeId(void) {
    static TypeId tid = TypeId("ns3::BlockchainConsensusPBFT")
            .SetParent<BlockchainConsensusBase>()
            .AddConstructor<BlockchainConsensusPBFT>();
    return tid;
}

void BlockchainConsensusPBFT::Init(Ptr<BlockchainBlockchain> blockchain,
                                   Ptr<BlockchainNetworkBase> network,
                                   Ptr<BlockchainTxpool> txpool,
                                   Ptr<BlockchainVerifier> verifier,
                                   Ptr<std::vector<NodeAddress>> neighborId,
                                   uint64_t nodeIndex) {
    m_blockchain = blockchain;
    m_network = network;
    m_txpool = txpool;
    m_verifier = verifier;

    m_nodeIndex = nodeIndex;
    m_nodeId = GenerateWorkerAddress(nodeIndex);

    m_view = 0;
    m_numBlock = 0;
    m_numNode = neighborId->size();

    m_nodeRole = BlockchainConsensusNodeRole::BCNR_FOLLOWER;
    m_nodeState = BlockchainConsensusNodeState::BCNS_INIT;

    m_neighborId = std::vector<NodeAddress>(*neighborId);
    m_neighborId.erase(std::remove(m_neighborId.begin(), m_neighborId.end(), m_nodeId), m_neighborId.end());
}

void BlockchainConsensusPBFT::Start() {
    m_currentRoundLastSeenActive = Simulator::Now();
    Simulator::Schedule(MilliSeconds(blockchainConsensusPBFTLeaderTimeout), &CheckTimeout, this);
}

void BlockchainConsensusPBFT::Stop() {

}

BlockchainConsensusAlgorithm BlockchainConsensusPBFT::GetConsensusAlgorithmType() {
    return BlockchainConsensusAlgorithm::BCA_PBFT;
}

BlockchainConsensusNodeRole BlockchainConsensusPBFT::GetConsensusNodeRole() {
    return m_nodeRole;
}

BlockchainConsensusNodeState BlockchainConsensusPBFT::GetConsensusNodeState() {
    return m_nodeState;
}

void BlockchainConsensusPBFT::UpdateNodeRole() {
    if (IsLeader() && m_nodeRole != BlockchainConsensusNodeRole::BCNR_LEADER) {
        m_nodeRole = BlockchainConsensusNodeRole::BCNR_LEADER;
        PackAndPreprepare();
    } else if (!IsLeader() && m_nodeRole == BlockchainConsensusNodeRole::BCNR_LEADER) {
        m_nodeRole = BlockchainConsensusNodeRole::BCNR_FOLLOWER;
    }
}

bool BlockchainConsensusPBFT::IsLeader() {
    return ((m_view + m_numBlock) % m_numNode) + 1 == m_nodeIndex;
}

void BlockchainConsensusPBFT::CheckTimeout() {
    if (Simulator::Now() - m_currentRoundLastSeenActive >= MilliSeconds(blockchainConsensusPBFTLeaderTimeout)) {
        // make agreement on changing view(directly change view for simplicity)
        m_view += 1;
        UpdateNodeRole();
        ResetRoundActive();
    }
    Simulator::Schedule(MilliSeconds(blockchainConsensusPBFTLeaderTimeout) - MilliSeconds(Simulator::Now() - m_currentRoundLastSeenActive), &CheckTimeout, this);
}

void BlockchainConsensusPBFT::ResetRoundActive() {
    m_currentRoundLastSeenActive = Simulator::Now();
}

void BlockchainConsensusPBFT::PackAndPreprepare() {
    Ptr<std::vector<Ptr<Transaction>>> txs = CreateObject<std::vector<Ptr<Transaction>>>();
    FetchTxs(txs);
    Pack(txs);
    if (m_blockToConsensus->IsEmptyBlock()) {
        // wait for timeout(for simplicity)
        return;
    }
    Preprepare();
}

void BlockchainConsensusPBFT::Preprepare() {
    
}

void BlockchainConsensusPBFT::FetchTxs(Ptr<std::vector<Ptr<Transaction>>> txs, uint64_t attemptLeft) {
    if (attemptLeft <= 0)
        return;
    if (m_txpool->GetTxNum() >= blockchainConsensusMinTxsInBlock || attemptLeft == 1) {
        std::vector<Ptr<Transaction>> txsInTxpool = m_txpool->GetAllTransactions();
        txs->insert(txs->end(), txsInTxpool.begin(), txsInTxpool.end());
        return;
    }
    Simulator::Schedule(MilliSeconds(blockchainConsensusFetchTxInterval), &FetchTxs, txs, attemptLeft-1);
}

void BlockchainConsensusPBFT::Pack(Ptr<std::vector<Ptr<Transaction>>> txs) {
    m_blockToConsensus = CreateObject<Block>();
    uint64_t newBlockIndex = m_blockchain->GetNextBlockIndex();
    m_blockToConsensus->m_id = GenerateBlockID(newBlockIndex, m_nodeId);
    m_blockToConsensus->m_parentId = m_blockchain->GetTailBlockId();
    m_blockToConsensus->m_miner = m_nodeId;
    m_blockToConsensus->m_createTime = 0; // TODO: not implement
    m_blockToConsensus->m_txs = *txs;
    m_blockToConsensus->m_txCount = txs->size();
}

}