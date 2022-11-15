#ifndef BLOCKCHAIN_WORKER
#define BLOCKCHAIN_WORKER

#include <string>

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


protected:
    virtual void DoDispose (void);

private:

    virtual void StartApplication (void);
    virtual void StopApplication (void);

    uint64_t m_nodeIndex;
    NodeAddress m_nodeId;
    std::string m_consensusName; // ['pbft', 'raft']
    Ptr<BlockchainBlockchain> m_blockchain;
    Ptr<BlockchainNetworkBase> m_network;
    Ptr<BlockchainTxpool> m_txpool;
    Ptr<BlockchainVerifier> m_verifier;
    Ptr<BlockchainConsensusBase> m_consensus;

};
  
} // Namespace ns3


#endif