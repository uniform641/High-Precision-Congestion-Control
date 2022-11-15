#ifndef BLOCKCHAIN_NETWORK_TCP_H
#define BLOCKCHAIN_NETWORK_TCP_H

#include "ns3/object.h"
#include "ns3/ptr.h"

#include "blockchain-common.h"
#include "blockchain-network-base.h"

namespace ns3 {
class BlockchainNetworkTCP : public BlockchainNetworkBase, public Object {
public:
    static TypeId GetTypeId(void);
};
}

#endif