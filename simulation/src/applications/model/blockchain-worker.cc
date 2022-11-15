#include "blockchain-worker.h"

namespace ns3 {
NS_LOG_COMPONENT_DEFINE ("BlockchainWorker");
NS_OBJECT_ENSURE_REGISTERED (BlockchainWorker);

TypeId BlockchainWorker::GetTypeId (void) {
    static TypeId tid = TypeId ("ns3::BlockchainWorker")
        .SetParent<Application> ()
        .SetGroupName("Applications")
        .AddConstructor<BlockchainWorker> ()
        .AddAttribute ("NodeIndex",
                       "node index from 1",
                       UintegerValue (1),
                       MakeUintegerAccessor (&BlockchainWorker::m_nodeIndex),
                       MakeUintegerChecker<uint64_t> ())
        .AddAttribute("ConsensusAlgorithmName",
                      "name of consensus algorithm ['pbft', 'raft']",
                      StringValue("pbft"),
                      MakeStringAccessor(&BlockchainWorker::m_consensusName),
                      MakeStringChecker())
        .AddAttribute("NetworkType",
                      "type of network ['rdma', 'tcp', 'p2p']",
                      StringValue("tcp"),
                      MakeStringAccessor(&BlockchainWorker::m_networkType),
                      MakeStringChecker())
    ;
    return tid;
}

BlockchainWorker::BlockchainWorker() {
    NS_LOG_FUNCTION_NOARGS();
}

BlockchainWorker::~BlockchainWorker() {
    NS_LOG_FUNCTION_NOARGS();
}

void BlockchainWorker::DoDispose (void) {
    NS_LOG_FUNCTION_NOARGS();
    Application::DoDispose ();
}

void BlockchainWorker::StartApplication (void) {
    NS_LOG_FUNCTION_NOARGS();

    m_nodeId = GenerateWorkerAddress(m_nodeIndex);
    m_blockchain = CreateObject<BlockchainBlockchain>();
    m_txpool = CreateObject<BlockchainTxpool>();
    m_verifier = CreateObject<BlockchainVerifier>();
    m_consensus = GetConsensusAlgorithm(m_consensusName);
    m_network = GetNetwork(m_networkType);
}

void BlockchainWorker::StopApplication (void) {
    NS_LOG_FUNCTION_NOARGS();
}

}