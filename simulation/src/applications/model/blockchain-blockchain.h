#ifndef BLOCKCHAIN_BLOCKCHAIN_H
#define BLOCKCHAIN_BLOCKCHAIN_H

#include <map>

#include "ns3/log.h"
#include "ns3/object.h"
#include "ns3/ptr.h"

#include "blockchain-common.h"

namespace ns3 {
NS_LOG_COMPONENT_DEFINE ("BlockchainBlockchain");
NS_OBJECT_ENSURE_REGISTERED (BlockchainBlockchain);

class BlockchainBlockchain : public Object{
public:
    Ptr<std::map<BlockID, Ptr<Block>>> m_blocks;
    uint64_t m_height;
    Ptr<Block> m_tail;

    BlockchainBlockchain() {
        NS_LOG_FUNCTION_NOARGS();
    }

    virtual ~BlockchainBlockchain() {
        NS_LOG_FUNCTION_NOARGS();
    }

    static TypeId GetTypeId(void) {
        static TypeId tid = TypeId("ns3::BlockchainBlockchain")
                .SetParent<Object>()
                .AddConstructor<BlockchainBlockchain>();
        return tid;
    }

    void Init() {
        m_height = 0;
        m_blocks = CreateObject<std::map<BlockID, Ptr<Block>>>();
        m_tail = nullptr;
    }

    // blockchain height start from 1
    uint64_t GetHeight() {
        return m_height;
    }

    Ptr<Block> GetBlock(uint64_t height) {
        if (height > m_height || height <= 0) {
            return nullptr;
        }
        Ptr<Block> cursor = m_tail;
        for (auto i = 0; m_height - i != height; i++)
            cursor = (*m_blocks)[cursor->m_parentId];
        return cursor;
    }

    Ptr<Block> GetBlock(BlockID blockId) {
        return (*m_blocks)[blockId];
    }

    void AddBlock(Ptr<Block> block) {
        if (block == nullptr)
            return;
        m_height++;
        (*m_blocks)[block->m_id] = block;
        m_tail = block;
    }

    bool HasBlock(BlockID blockId) {
        return (*m_blocks).find(blockId) != (*m_blocks).end();
    }

    uint64_t GetNextBlockIndex() {
        return m_height + 1;
    }

    BlockID GetTailBlockId() {
        if (m_tail == nullptr)
            return (BlockID)0;
        return m_tail->m_id;
    }
};
}

#endif