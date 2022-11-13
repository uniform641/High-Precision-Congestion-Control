#ifndef BLOCKCHAIN_TXPOOL_H
#define BLOCKCHAIN_TXPOOL_H

#include <vector>
#include "ns3/ptr.h"
#include "blockchain-common.h"

namespace ns3 {
class BlockchainTxpool {
public:
    uint64_t m_txCapacity;
    Ptr<std::vector<Ptr<Transaction>>> m_txpool;
    BlockchainTxpool(uint64_t txCapacity = 1000) : m_txCapacity(txCapacity) {
        NS_LOG_FUNCTION_NOARGS();
        Init();
    }

    virtual ~BlockchainTxpool() {
        NS_LOG_FUNCTION_NOARGS();
    }

    static TypeId GetTypeId(void) {
        static TypeId tid = TypeId("ns3::BlockchainTxpool")
                .SetParent<Object>()
                .AddConstructor<BlockchainTxpool>();
        return tid;
    }

    void Init() {
        m_txpool = CreateObject<std::vector<Ptr<Transaction>>>();
        m_txpool->resize(m_txCapacity);
    }

    void AddTransaction(Ptr<Transaction> tx) {

    }

    void AddTransactions(std::vector<Ptr<Transaction>>& txs) {

    }

    bool DropTransaction(Ptr<Transaction> tx) {

    }

    void DropTransactionsInBlock(Ptr<Block> block) {

    }

    bool HasTransaction(Ptr<Transaction> tx) {

    }


};
}

#endif