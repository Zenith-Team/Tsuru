#pragma once

#include "sead/treemapimpl.h"
#include "sead/freelist.h"
#include "sead/safestring.h"

namespace sead {

template <s32 KeyStrN, typename Value>
class StrTreeMap : public TreeMapImpl<SafeString> {
public:
    class Node : public TreeMapNode<SafeString> {
    public:
        Node(const SafeString& akey, const Value& avalue, StrTreeMap<KeyStrN, Value>* mapV)
            : value(avalue)
            , map(mapV)
        {
            BufferedSafeString key(keyStr, KeyStrN + 1);
            key.copy(akey);
            this->key_ = key;
        }

        virtual void erase_() {
            this->map->eraseNode(this);
        }

        SafeString& key() {
            return this->key_;
        }

        Value& getValue() {
            return this->value;
        }

    private:
        Value value;
        StrTreeMap<KeyStrN, Value>* map;
        char keyStr[KeyStrN + 1];
    };

public:
    template <typename T> // T = {*}Delegate2<..., SafeString&, Value&>
    class ForEachConstContext {
    public:
        ForEachConstContext(const T& afun)
            : fun(afun)
        { }

        void call(TreeMapNode<SafeString>* n) {
            Node* node = static_cast<Node*>(n);
            this->fun(node->key(), node->getValue());
        }

    private:
        const T& fun;
    };

public:
    StrTreeMap()
        : size(0)
        , nodeMax(0)
    { }

    void setBuffer(s32 nodeMaxV, void* buf) {
        if (nodeMaxV > 0) {
            if (buf != nullptr) {
                this->nodeMax = nodeMaxV;
                this->freeList.init(buf, sizeof(Node), nodeMaxV);
            }
            else {
                // SEAD_ASSERT_MSG(false, "buf is null");
            }
        }
        else {
            // SEAD_ASSERT_MSG(false, "nodeMaxV[%d] must be larger than zero", nodeMaxV);
        }
    }

    void allocBuffer(s32 nodeMaxV, Heap* heap, s32 alignment = 4) {
        // SEAD_ASSERT(freeList.work() == nullptr);
        if (nodeMaxV > 0) {
            void* buf = new(heap, alignment) u8[nodeMaxV * sizeof(Node)]; // NewArray<u8>(nodeMaxV * sizeof(Node), heap, alignment)
            this->setBuffer(nodeMaxV, buf);
        }
        else {
            // SEAD_ASSERT_MSG(false, "nodeMaxV[%d] must be larger than zero", nodeMaxV);
        }
    }

    void freeBuffer() {
        if (this->isBufferReady()) {
            this->clear();
            delete[] static_cast<u8*>(this->freeList.work()); // DeleteArray<u8>(freeList.work())
            this->nodeMax = 0;
            this->freeList.cleanup();
        }
    }

    bool isBufferReady() const {
        return this->freeList.work() != nullptr;
    }

    bool isEmpty() const {
        return this->size == 0;
    }

    bool isFull() const {
        return this->size >= this->nodeMax;
    }

    s32 getSize() const {
        return this->size;
    }

    s32 maxSize() const {
        return this->nodeMax;
    }

    Value* find(const SafeString& key) const {
        Node* node = static_cast<Node*>(TreeMapImpl<SafeString>::find(key));
        if (node != nullptr)
            return &node->value();

        return nullptr;
    }

    void insert(const SafeString& key, const Value& value) {
        if (!this->isFull()) {
            Node* node = new (this->freeList.get()) Node(key, value, this);
            this->size++;
            TreeMapImpl<SafeString>::insert(node);
        }
        else {
            Value* p_value = this-> find(key);
            if (p_value != nullptr) {
                new (p_value) Value(value); // ???
            }
            else {
                // SEAD_ASSERT_MSG(false, "map is full.");
            }
        }
    }

    void clear() {
        TreeMapImpl<SafeString>::forEach(
            DelegateCreator<
                StrTreeMap<KeyStrN, Value>,
                TreeMapNode<SafeString>*
            >(
                this,
                &StrTreeMap<KeyStrN, Value>::eraseNodeForClear
            )
        );
        this->size = 0;
        this->root = nullptr;
        this->freeList.init(this->freeList.work(), sizeof(Node), this->nodeMax);
    }

    void eraseNode(Node* node) {
        this->freeList.put(node);
        this->size--;
    }

    void eraseNodeForClear(TreeMapNode<SafeString>* n) {
        static_cast<Node*>(n)->value(); // ... ?
    }

    template <typename T> // T = {*}Delegate2<..., SafeString&, Value&>
    void forEach(const T& fun) const {
        ForEachConstContext<T> context(fun);

        TreeMapImpl<SafeString>::forEach(
            DelegateCreator<
                ForEachConstContext<T>,
                TreeMapNode<SafeString>*
            >(
                &context,
                &ForEachConstContext<T>::call
            )
        );
    }

protected:
    FreeList freeList;
    s32 size;
    s32 nodeMax;
};

template <s32 KeyStrN, typename Value, s32 N>
class FixedStrTreeMap : public StrTreeMap<KeyStrN, Value> {
public:
    FixedStrTreeMap()
        : StrTreeMap<KeyStrN, Value>()
    {
        StrTreeMap<KeyStrN, Value>::setBuffer(N, this->work);
    }

protected:
    void setBuffer(s32 nodeMax, void* buf);
    void allocBuffer(s32 nodeMax, Heap* heap, s32 alignment = 4);
    void freeBuffer();

protected:
    u8 work[N*sizeof(StrTreeMap<KeyStrN, Value>::Node)];
};

}
