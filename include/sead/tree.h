#pragma once

#include <types.h>

namespace sead {

class TreeNode {
public:
    TreeNode();

    void clearChildLinksRecursively_();
    void clearLinks();
    s32 countChildren() const;
    void detachAll();
    void detachSubTree();
    TreeNode* findRoot();
    const TreeNode* findRoot() const;
    void insertAfterSelf(TreeNode*);
    void insertBeforeSelf(TreeNode*);
    void pushBackChild(TreeNode*);
    void pushBackSibling(TreeNode*);
    void pushFrontChild(TreeNode*);

    TreeNode* parent;
    TreeNode* child;
    TreeNode* next;
    TreeNode* prev;
};

template <typename T>
class TTreeNode : public TreeNode {
public:
    T data;
};

}