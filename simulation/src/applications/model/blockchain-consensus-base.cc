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
                    std::string consensusName) {
    m_blockchain = blockchain;
    m_network = network;
    m_txpool = txpool;
    m_verifier = verifier;
    algorithm = ConsensusAlgorithmType(consensusName);
    state = BCNS_NONE;
    role = BCNR_NONE;
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

Ptr<BlockchainConsensusBase> GetConsensusAlgorithm(std::string consensus) {
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