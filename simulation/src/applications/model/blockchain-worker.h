#ifndef BLOCKCHAIN_WORKER
#define BLOCKCHAIN_WORKER

#include <string>
#include <map>
#include <vector>

#include "ns3/application.h"
#include "ns3/event-id.h"
#include "ns3/ptr.h"
#include "ns3/ipv4-address.h"
#include "ns3/uinteger.h"

#include "blockchain-common.h"
#include "blockchain-verifier.h"
#include "blockchain-blockchain.h"
#include "blockchain-network-base.h"
#include "blockchain-txpool.h"
#include "blockchain-consensus-base.h"

namespace ns3 {

class Socket;
class Packet;

class BlockchainWorker : public Application {
public:
    static TypeId GetTypeId (void);

    BlockchainWorker ();
    virtual ~BlockchainWorker ();

    NodeAddress GetNodeId();
    uint64_t GetNodeIndex();


protected:
    virtual void DoDispose (void);

private:
    virtual void StartApplication (void);
    virtual void StopApplication (void);

    uint64_t m_nodeIndex;
    NodeAddress m_nodeId;
    std::string m_consensusName; // ['pbft', 'raft']
    std::string m_networkType; // ['rdma', 'tcp', 'p2p']
    // Ptr<std::map<uint64_t, 
    Ptr<BlockchainBlockchain> m_blockchain;
    Ptr<BlockchainTxpool> m_txpool;
    Ptr<BlockchainVerifier> m_verifier;
    Ptr<BlockchainNetworkBase> m_network;
    Ptr<BlockchainConsensusBase> m_consensus;

};
  
} // Namespace ns3


#endif