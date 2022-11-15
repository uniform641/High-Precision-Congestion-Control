#ifndef BLOCKCHAIN_NETWORK_BASE_H
#define BLOCKCHAIN_NETWORK_BASE_H

#include <string>

#include "ns3/log.h"
#include "ns3/object.h"
#include "ns3/ptr.h"

#include "blockchain-common.h"
#include "blockchain-network-tcp.h"
#include "blockchain-network-p2p.h"
#include "blockchain-network-rdma.h"

namespace ns3 {
enum BlockchainNetworkType {
    BNT_NONE,
    BNT_TCP,
    BNT_P2P,
    BNT_RDMA
};

BlockchainNetworkType GetNetworkType(std::string networkName) {
    if (networkName == "tcp") {
        return BNT_TCP;
    } else if (networkName == "p2p") {
        return BNT_P2P;
    } else if (networkName == "rdma") {
        return BNT_RDMA;
    } else {
        return BNT_NONE;
    }
}

NS_LOG_COMPONENT_DEFINE ("BlockchainNetworkBase");
NS_OBJECT_ENSURE_REGISTERED (BlockchainNetworkBase);

class BlockchainNetworkBase {
public:
    BlockchainNetworkBase() {
        NS_LOG_FUNCTION_NOARGS();
    }

    virtual ~BlockchainNetworkBase() {
        NS_LOG_FUNCTION_NOARGS();
    }

    static TypeId GetTypeId(void) {
        static TypeId tid = TypeId("ns3::BlockchainNetworkBase")
                .SetParent<Object>()
                .AddConstructor<BlockchainNetworkBase>();
        return tid;
    }

    virtual void Init() {

    }
};
}

#endif