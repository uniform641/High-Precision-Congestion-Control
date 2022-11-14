#ifndef BLOCKCHAIN_TXPOOL_H
#define BLOCKCHAIN_TXPOOL_H

#include <vector>
#include <map>
#include "ns3/ptr.h"
#include "ns3/log.h"
#include "ns3/object.h"
#include "blockchain-common.h"

namespace ns3 {
class BlockchainTxpool : public Object {
public:
    uint64_t m_txCapacity;
    Ptr<std::vector<Ptr<Transaction>>> m_txpool;

    BlockchainTxpool() {
        NS_LOG_FUNCTION_NOARGS();
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

    void Init(uint64_t txCapacity = 1000) {
        m_txCapacity = txCapacity;
        m_txpool = CreateObject<std::vector<Ptr<Transaction>>>();
        m_txpool->resize(m_txCapacity);
    }

    bool AddTransaction(Ptr<Transaction> tx) {
        if (tx == nullptr || m_txpool->size() >= m_txCapacity)
            return false;
        m_txpool->push_back(tx);
        return true;
    }

    void AddTransactions(std::vector<Ptr<Transaction>>& txs) {
        // TODO : redesign return type and implement then
    }

    // return false if the transaction does not exist
    bool DropTransaction(Ptr<Transaction> tx) {
        if (tx == nullptr)
            return true;
        for (auto it = m_txpool->begin(); it != m_txpool->end(); it++) {
            if (*it == tx) {
                m_txpool->erase(it);
                return true;
            }
        }
        return false;
    }

    void DropTransactionsInBlock(Ptr<Block> block) {

    }

    bool HasTransaction(Ptr<Transaction> tx) {

    }

    bool HasTransaction(TransactionID txId) {

    }

    std::map<TransactionID, bool> HasTransactions(std::vector<TransactionID>& txIds) {

    }

    Ptr<Transaction> GetTransaction(TransactionID txId) {

    }

    std::vector<Ptr<Transaction>> GetTransactions(std::vector<TransactionID>& txIds) {

    }

    Ptr<std::vector<Ptr<Transaction>>> GetTransactions(uint64_t maxTxCount) {

    }

    Ptr<std::vector<Ptr<Transaction>>> GetAllTransactions() {

    }


};
}

#endif