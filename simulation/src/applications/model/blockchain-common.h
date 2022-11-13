#ifndef BLOCKCHAIN_COMMON
#define BLOCKCHAIN_COMMON

#include <stdint.h>
#include <vector>
#include "ns3/ptr.h"

namespace ns3 {
// support max 2^16(65536) nodes due to transaction and block ID encoding
using NodeAddress = uint64_t;
using TransactionID = uint64_t;
using BlockID = uint64_t;

struct Transaction {
    TransactionID m_id;
    NodeAddress m_sender;
    NodeAddress m_receiver;
    uint64_t m_createTime;
    uint64_t m_importTime;
    uint64_t m_dataLength;

    Transaction(TransactionID id, NodeAddress sender, NodeAddress receiver, uint64_t createTime, uint64_t dataLength) :
            m_id(id), m_sender(sender), m_receiver(receiver), m_createTime(createTime), m_dataLength(dataLength) {}
};

struct Block {
    BlockID m_id;
    NodeAddress m_miner;
    uint64_t m_createTime;
    uint64_t m_dataLength;
    uint64_t m_txCount;
    std::vector<Transaction> m_txs;
};

NodeAddress GenerateWorkerAddress(uint64_t workerIndex) {
    return 0x1000000000000000 + (workerIndex & 0x0FFFFFFFFFFFFFFF);
}

NodeAddress GenerateClientAddress(uint64_t clientIndex) {
    return 0x2000000000000000 + (clientIndex & 0x0FFFFFFFFFFFFFFF);
}

TransactionID GenerateTransactionID(uint64_t transactionIndex, NodeAddress clientAddress) {
    return (clientAddress << 48) + (transactionIndex & 0x0000FFFFFFFFFFFF);
}

BlockID GenerateBlockID(uint64_t blockIndex, NodeAddress minerAddress) {
    return (minerAddress << 48) + (blockIndex & 0x0000FFFFFFFFFFFF);
}
}

#endif