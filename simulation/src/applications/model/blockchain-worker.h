#ifndef BLOCKCHAIN_WORKER
#define BLOCKCHAIN_WORKER

#include "ns3/application.h"
#include "ns3/event-id.h"
#include "ns3/ptr.h"
#include "ns3/ipv4-address.h"

namespace ns3 {

class Socket;
class Packet;

class BlockchainWorker : public Application
{
public:
  static TypeId GetTypeId (void);

  BlockchainWorker ();
  virtual ~BlockchainWorker ();

  void Init();
  void Start();
  void Stop();

protected:
  virtual void DoDispose (void);

private:
  
    virtual void StartApplication (void);
    virtual void StopApplication (void);
  
    uint64_t m_nodeId;
    
  
    Ipv4Address m_sip, m_dip;
    uint16_t m_sport, m_dport;
    uint32_t m_win; // bound of on-the-fly packets
    uint64_t m_baseRtt; // base Rtt
};
  
} // Namespace ns3


#endif