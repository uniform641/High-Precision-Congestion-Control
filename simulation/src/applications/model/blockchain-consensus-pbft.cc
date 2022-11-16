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
    m_blockNumber = 0;

    m_neighborId = std::vector<NodeAddress>(*neighborId);
    m_neighborId.erase(std::remove(m_neighborId.begin(), m_neighborId.end(), m_nodeId), m_neighborId.end());
}

}