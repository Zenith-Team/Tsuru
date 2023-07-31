#pragma once

#include "types.h"

namespace sead {

template <typename Key>
class TreeMapNode {
public:
    TreeMapNode()
        : left_(nullptr)
        , right_(nullptr)
        , color_(true)
    { }

    virtual ~TreeMapNode() { }

    virtual void erase_() = 0;

    TreeMapNode<Key>* left_;
    TreeMapNode<Key>* right_;
    bool color_;
    Key key_;
};

template <typename Key>
class TreeMapImpl {
public:
    TreeMapImpl()
        : root(nullptr)
    { }

    void insert(TreeMapNode<Key>* node) {
        this->root = this->insert(this->root, node);
        this->root->color_ = false;
    }

    TreeMapNode<Key>* insert(TreeMapNode<Key>* h, TreeMapNode<Key>* node);

    TreeMapNode<Key>* find(const Key& key) const {
        return find(this->root, key);
    }

    TreeMapNode<Key>* find(TreeMapNode<Key>* node, const Key& key) const;

    static TreeMapNode<Key>* rotateLeft(TreeMapNode<Key>* h);
    static TreeMapNode<Key>* rotateRight(TreeMapNode<Key>* h);
    static void flipColors(TreeMapNode<Key>* h);
    static bool isRed(TreeMapNode<Key>* h);

    template <typename T> // T = {*}Delegate1<..., TreeMapNode<Key>*>
    void forEach(const T& fun) const {
        if (this->root != nullptr)
            this->forEach(this->root, fun);
    }

    template <typename T> // T = {*}Delegate1<..., TreeMapNode<Key>*>
    static void forEach(TreeMapNode<Key>* node, const T& fun) {
        if (node->left_ != nullptr)
            forEach(node->left_, fun);

        fun(node);

        if (node->right_ != nullptr)
            forEach(node->right_, fun);
    }

protected:
    TreeMapNode<Key>* root;
};

}
