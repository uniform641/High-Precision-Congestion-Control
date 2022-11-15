#ifndef BLOCKCHAIN_NETWORK_P2P_H
#define BLOCKCHAIN_NETWORK_P2P_H

#include "ns3/object.h"
#include "ns3/ptr.h"

#include "blockchain-common.h"
#include "blockchain-network-base.h"

namespace ns3 {
class BlockchainNetworkP2P : public BlockchainNetworkBase, public Object {
public:
    static TypeId GetTypeId(void);
};
}

#endif