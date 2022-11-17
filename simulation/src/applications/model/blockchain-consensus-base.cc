#include "blockchain-consensus-base.h"

namespace ns3 {
NS_LOG_COMPONENT_DEFINE ("BlockchainConsensusBase");
NS_OBJECT_ENSURE_REGISTERED (BlockchainConsensusBase);

BlockchainConsensusBase::BlockchainConsensusBase() {
    NS_LOG_FUNCTION_NOARGS();
}

BlockchainConsensusBase::~BlockchainConsensusBase() {
    NS_LOG_FUNCTION_NOARGS();
}

TypeId BlockchainConsensusBase::GetTypeId(void) {
    static TypeId tid = TypeId("ns3::BlockchainConsensusBase")
            .SetParent<Object>()
            .AddConstructor<BlockchainConsensusBase>();
    return tid;
}

void BlockchainConsensusBase::Init(Ptr<BlockchainBlockchain> blockchain,
                    Ptr<BlockchainNetworkBase> network,
                    Ptr<BlockchainTxpool> txpool,
                    Ptr<BlockchainVerifier> verifier,
                    Ptr<std::vector<NodeAddress>> neighborId,
                    uint64_t nodeIndex) {
    // do nothing
}

BlockchainConsensusAlgorithm BlockchainConsensusBase::GetConsensusAlgorithmType() {
    return BlockchainConsensusAlgorithm::BCA_NONE;
}

BlockchainConsensusNodeState BlockchainConsensusBase::GetConsensusNodeState() {
    return BlockchainConsensusNodeState::BCNS_NONE;
}

BlockchainConsensusNodeRole BlockchainConsensusBase::GetConsensusNodeRole() {
    return BlockchainConsensusNodeRole::BCNR_NONE;
}



BlockchainConsensusAlgorithm ConsensusAlgorithmType(std::string consensus) {
    if (consensus == "pbft") {
        return BCA_PBFT;
    } else if (consensus == "raft") {
        return BCA_RAFT;
    } else {
        return BCA_NONE;
    }
}

Ptr<BlockchainConsensusBase> CreateConsensusAlgorithm(std::string consensus) {
    switch (ConsensusAlgorithmType(consensus)) {
        case BCA_PBFT:
            return CreateObject<BlockchainConsensusPBFT>();
        case BCA_RAFT:
            return CreateObject<BlockchainConsensusRaft>();
        default:
            NS_LOG_ERROR("Unknown consensus algorithm: " << consensus);
            return CreateObject<BlockchainConsensusBase>();
    }
}
}