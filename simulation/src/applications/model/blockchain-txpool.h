#ifndef BLOCKCHAIN_TXPOOL_H
#define BLOCKCHAIN_TXPOOL_H

#include <vector>
#include <map>

#include "ns3/ptr.h"
#include "ns3/log.h"
#include "ns3/object.h"

#include "blockchain-common.h"

namespace ns3 {
NS_LOG_COMPONENT_DEFINE ("BlockchainTxpool");
NS_OBJECT_ENSURE_REGISTERED (BlockchainTxpool);

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
        // TODO: redesign return type and implement then
    }

    // return false if the transaction does not exist
    bool DropTransaction(Ptr<Transaction> tx) {
        // TODO: optimize
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
        if (block == nullptr)
            return;
        for (auto tx : block->m_txs) {
            DropTransaction(tx);
        }
    }

    bool HasTransaction(Ptr<Transaction> tx) {
        if (tx == nullptr)
            return false;
        for (auto it = m_txpool->begin(); it != m_txpool->end(); it++) {
            if (*it == tx) {
                return true;
            }
        }
        return false;
    }

    bool HasTransaction(TransactionID txId) {
        for (auto it = m_txpool->begin(); it != m_txpool->end(); it++) {
            if ((*it)->m_id == txId) {
                return true;
            }
        }
        return false;
    }

    std::map<TransactionID, bool> HasTransactions(std::vector<TransactionID>& txIds) {
        std::map<TransactionID, bool> result;
        for (auto txId : txIds) {
            result[txId] = HasTransaction(txId);
        }
        return result;
    }

    Ptr<Transaction> GetTransaction(TransactionID txId) {
        for (auto it = m_txpool->begin(); it != m_txpool->end(); it++) {
            if ((*it)->m_id == txId) {
                return *it;
            }
        }
        return nullptr;
    }

    std::vector<Ptr<Transaction>> GetTransactions(std::vector<TransactionID>& txIds) {
        std::vector<Ptr<Transaction>> result;
        for (auto txId : txIds) {
            result.push_back(GetTransaction(txId));
        }
        return result;
    }

    std::vector<Ptr<Transaction>> GetTransactions(uint64_t maxTxCount) {
        maxTxCount = maxTxCount > m_txpool->size() ? m_txpool->size() : maxTxCount;
        std::vector<Ptr<Transaction>> result;
        for (uint64_t i = 0; i < maxTxCount; i++) {
            result.push_back((*m_txpool)[i]);
        }
        return result;
    }

    std::vector<Ptr<Transaction>> GetAllTransactions() {
        return *m_txpool;
    }

    uint64_t GetTxNum() {
        return m_txpool->size();
    }
};
}

#endif