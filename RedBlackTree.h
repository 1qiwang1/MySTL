#pragma once
#include <iostream>
#include <string>
using namespace std;

enum class Color { RED, BLACK };

template <typename Key, typename Value>
class RedBlackTree {
    class Node {
    public:
        Key key;
        Value value;
        Color color;
        Node* left;
        Node* right;
        Node* parent;

        // 构造函数
        Node(const Key& k, const Value& v, Color c, Node* p = nullptr) :
            key(k), value(v), color(c), left(nullptr), right(nullptr), parent(p) {}

        Node():
            color(Color::BLACK), left(nullptr), right(nullptr), parent(nullptr) {}
    };

private:
    Node* root;
    size_t size;
    Node* Nil;

    // 查询某节点
    Node* lookup(Key& key) {
        Node* cmpNode = root;

        while (cmpNode) {
            if (key < cmpNode->key) {
                cmpNode = cmpNode->left;
            }
            else if (key > cmpNode->key) {
                cmpNode = cmpNode->right;
            }
            else {
                return cmpNode;
            }
        }
        return cmpNode;
    }



    // 右旋函数
    void rightRotate(Node* node) {
        Node* l_son = node->left;
        node->left = l_son->right;
        if (l_son->right) {
            l_son->right->parent = node;
        }

        l_son->parent = node->parent;
        if (!node->parent) {
            root = l_son;
        }
        else if (node == node->parent->left) {
            node->parent->left = l_son;
        }
        else {
            node->parent->right = l_son;
        }

        l_son->right = node;
        node->parent = l_son;
    }


    // 左旋函数
    void leftRotate(Node* node) {
        Node* r_son = node->right;

        node->right = r_son->left;

        if (r_son->left) {
            r_son->left->parent = node;
        }

        r_son->parent = node->parent;
        if (!node->parent) {
            root = r_son;
        }
        else if (node == node->parent->left) {
            node->parent->left = r_son;
        }
        else {
            node->parent->right = r_son;
        }

        r_son->left = node;
        node->parent = r_son;
    }


    // 插入修复函数
    void insertFixup(Node* target) {
        // 当目标节点的父节点存在且父节点的颜色是红色时需要修复
        while (target->parent && target->parent->color == Color::RED) {
            // 当目标节点的父节点是祖父节点的左孩子时
            if (target->parent == target->parent->parent->left) {
                Node* uncle = target->parent->parent->right;
                // 叔父节点存在且为红色，进行调整
                if (uncle && uncle->color == Color::RED) {
                    target->parent->color = Color::BLACK;
                    uncle->color = Color::BLACK;
                    target->parent->parent->color = Color::RED;
                    target = target->parent->parent;
                }
                    // 叔父节点为黑色或不存在
                else {
                    // 如果目标节点是父节点的右子节点，进行左旋转
                    if (target == target->parent->right) {
                        target = target->parent;
                        leftRotate(target);
                    }
                    // 调整父节点和祖父节点的颜色，并进行右旋转
                    target->parent->color = Color::BLACK;
                    target->parent->parent->color = Color::RED;
                    rightRotate(target->parent->parent);
                }
            }
            // 当目标节点的父节点是祖父节点的右孩子时
            else {
                // 当目标节点的父节点是祖父节点的右子节点时，与上面对称
                Node* uncle = target->parent->parent->left;
                if (uncle && uncle->color == Color::RED) {
                    target->parent->color = Color::BLACK;
                    uncle->color = Color::BLACK;
                    target->parent->parent->color = Color::RED;
                    target = target->parent->parent;
                }
                else {
                    if (target == target->parent->left) {
                        target = target->parent;
                        rightRotate(target);
                    }
                    target->parent->color = Color::BLACK;
                    target->parent->parent->color = Color::RED;
                    leftRotate(target->parent->parent);
                }
            }
        }
        root->color = Color::BLACK;
    }


    // 插入节点函数
    void insertNode(const Key& key, const Value& value) {
        // 新建一个需要插入的节点
        Node* newNode = new Node(key, value, Color::RED);
        Node* parent = nullptr;
        // 用于比较的节点，初始为根节点
        Node* cmpNode = root;

        while (cmpNode) {
            parent = cmpNode;
            if (newNode->key < cmpNode->key) {
                cmpNode = cmpNode->left;
            }
            else if (newNode->key > cmpNode->key) {
                cmpNode = cmpNode->right;
            }
            else {
                // 如果键相等，则树种已有相等节点的键，删除节点并返回
                delete newNode;
                return;
            }
        }

        size++;

        newNode->parent = parent;
        if (!parent) {
            root = newNode;
        }
        else if (newNode->key < parent->key) {
            parent->left = newNode;
        }
        else {
            parent->right = newNode;
        }

        insertFixup(newNode);
    }


    // 中序遍历
    void inorderTraversal(Node* node) const {
        if (node) {
            inorderTraversal(node->left);
            cout << node->key << " ";
            cout << node->value << " ";
            inorderTraversal(node->right);
        }
    }


    // 辅助函数，用新节点替换旧节点
    void replaceNode(Node* targetNode, Node* newNode) {
        if (!targetNode) {
            root = newNode;
        }
        else if (targetNode == targetNode->parent->left) {
            targetNode->parent->left = newNode;
        }
        else {
            targetNode->parent->right = newNode;
        }

        if (newNode) {
            newNode->parent = targetNode->parent;
        }
    }


    // 寻找以某个节点为根节点的子树中的最小节点
    Node* findMinimumNode(Node* node) {
        while (node->left) {
            node = node->left;
        }
        return node;
    }

    void setColor(Node* node, Color color) {
        if (node == nullptr) {
            return;
        }
        node->color = color;
    }

    // 删除修复函数
    void removeFixup(Node* node) {
        // 如果节点为Nil并且没有父节点，说明它是唯一的节点，直接返回
        if (node == Nil && node->parent == nullptr) {
            return;
        }

        // 当我们没有到达根节点时继续循环
        while (node != root) {
            // 如果节点是其父节点的左子节点
            if (node == node->parent->left) {
                // 兄弟节点是节点父亲的右子节点
                Node* sibling = node->parent->right;


                // 情况1：节点的兄弟节点是红色
                if (getColor(sibling) == Color::RED) {
                    // 重新着色兄弟节点和父节点，并进行左旋
                    setColor(sibling, Color::BLACK);
                    setColor(sibling->parent, Color::RED);
                    leftRotate(node->parent);
                    // 旋转后更新兄弟节点
                    sibling = node->parent->right;
                }

                // 情况2：兄弟节点的两个子节点都是黑色
                if (getColor(sibling->left) == Color::BLACK && (getColor(sibling->right)) == Color::BLACK) {
                    // 重新着色兄弟节点并向上移动
                    setColor(sibling, Color::RED);
                    node = node->parent;
                    // 如果父节点是红色，将其改为黑色并结束
                    if (node->color == Color::RED) {
                        node->color = Color::BLACK;
                        node = root;
                    }
                }
                else {
                    // 情况3：兄弟节点的右子节点是黑色（左子节点是红色）
                    if (getColor(sibling->right) == Color::BLACK) {
                        // 重新着色兄弟节点和兄弟节点的左子节点，并进行右旋
                        setColor(sibling, Color::RED);
                        setColor(sibling->left, Color::BLACK);
                        rightRotate(sibling);
                        // 旋转后更新兄弟节点
                        sibling = node->parent->right;
                    }
                    // 情况4：兄弟节点的右子节点是红色
                    setColor(sibling, getColor(node->parent));
                    setColor(node->parent, Color::BLACK);
                    setColor(sibling->right, Color::BLACK);
                    // 移动到根节点结束
                    node = root;
                }
            }
            else {
                // 当节点是其父节点的右子节点时，对称的情况
                Node* sibling = node->parent->left;

                if (getColor(sibling) == Color::RED) {
                    setColor(sibling, Color::BLACK);
                    setColor(node->parent, Color::RED);
                    rightRotate(node->parent);
                    sibling = node->parent->left;
                }

                if (getColor(sibling->right) == Color::BLACK &&
                    getColor(sibling->left) == Color::BLACK) {
                    setColor(sibling, Color::RED);
                    node = node->parent;
                    if (node->color == Color::RED) {
                        node->color = Color::BLACK;
                        node = root;
                    }
                }
                else {
                    if (getColor(sibling->left) == Color::BLACK) {
                        setColor(sibling->right, Color::BLACK);
                        setColor(sibling, Color::RED);
                        leftRotate(sibling);
                        sibling = node->parent->left;
                    }
                    setColor(sibling, getColor(node->parent));
                    setColor(node->parent, Color::BLACK);
                    setColor(sibling->left, Color::BLACK);
                    rightRotate(node->parent);
                    node = root;
                }
            }
        }
        // 确保当前节点是黑色的，以维持红黑树性质
        setColor(node, Color::BLACK);
    }


    // 获取颜色，空指针为黑色
    Color getColor(Node* node) {
        if (node == nullptr) {
            return Color::BLACK;
        }
        return node->color;
    }



    // 取消Nil哨兵的连接
    void dieConnectNil() {
        if (Nil == nullptr) {
            return;
        }
        if (Nil->parent != nullptr) {
            if (Nil->parent->left) {
                Nil->parent->left = nullptr;
            }
            else {
                Nil->parent->right = nullptr;
            }
        }
    }


    // 删除节点
    void deleteNode(Node* del) {
        // rep初始指向要删除的节点
        Node* rep = del;
        // 要删除节点的孩子节点
        Node* child = nullptr;
        // 替代节点的父节点
        Node* parentRP;
        // 保存要删除节点的原始颜色
        Color origCol = rep->color;

        // 如果删除节点没有左孩子
        if (!del->left) {
            rep = del->right;
            parentRP = del->parent;
            origCol = getColor(rep);
            replaceNode(del, rep);
        }
            // 如果删除节点没有右孩子
        else if (!del->right) {
            rep = del->left;
            parentRP = del->parent;
            origCol = getColor(rep);
            replaceNode(del, rep);
        }
            // 如果删除节点有两个孩子
        else {
            // 找到删除节点右子树中的最小节点作为替代节点
            rep = findMinimumNode(del->right);
            // 保存替代节点的原始颜色
            origCol = rep->color;

            // 如果替代节点不是删除节点的直接右孩子
            if (rep != del->right) {
                // 更新替代节点的父节点
                parentRP = rep->parent;
                // 替代节点的右孩子变成要处理的孩子节点
                child = rep->right;
                // 替代节点的父节点的左孩子指向替代节点的孩子（因为替代节点是最小节点，所以不可能有左孩子）
                parentRP->left = child;
                // 如果替代节点的孩子存在，则更新其父节点
                if (child != nullptr) {
                    child->parent = parentRP;
                }

                // 将替代节点放到删除节点的位置
                del->left->parent = rep;
                del->right->parent = rep;
                rep->left = del->left;
                rep->right = del->right;

                // 如果删除节点有父节点，更新父节点的孩子指向
                if (del->parent != nullptr) {
                    if (del == del->parent->left) {
                        del->parent->left = rep;
                    }
                    else {
                        del->parent->right = rep;
                    }
                    rep->parent = del->parent;
                }
                    // 如果删除节点没有父节点，说明它是根节点
                else {
                    root = rep;
                    root->parent = nullptr;
                }
            }
                // 如果替代节点是删除节点的直接右孩子
            else {
                // 孩子节点指向替代节点的右孩子
                child = rep->right;
                // 替代节点的左孩子指向删除节点的左孩子
                rep->left = del->left;
                // 更新左孩子的父节点
                del->left->parent = rep;

                // 更新删除节点父节点的孩子指向
                if (del->parent != nullptr) {
                    if (del == del->parent->left) {
                        del->parent->left = rep;
                    }
                    else {
                        del->parent->right = rep;
                    }
                    rep->parent = del->parent;
                }
                    // 如果删除节点是根节点
                else {
                    root = rep;
                    root->parent = nullptr;
                }
                // 更新替代节点的父节点
                parentRP = rep;
            }
        }
        // 如果替代节点存在，更新其颜色为删除节点的颜色
        if (rep != nullptr) {
            rep->color = del->color;
        }
        // 如果替代节点不存在，将删除节点的颜色赋给origCol变量
        else {
            origCol = del->color;
        }

        // 如果原始颜色是黑色，需要进行额外的修复操作，因为黑色节点的删除可能会破坏红黑树的性质
        if (origCol == Color::BLACK) {
            // 如果存在孩子节点，进行修复操作
            if (child != nullptr) {
                removeFixup(child);
            }
                // 如果不存在孩子节点，将Nil节点（代表空节点）的父节点设置为替代节点的父节点
            else {
                Nil->parent = parentRP;
                // 如果替代节点的父节点存在，设置其对应的孩子指针为Nil节点
                if (parentRP != nullptr) {
                    if (parentRP->left == nullptr) {
                        parentRP->left = Nil;
                    }
                    else {
                        parentRP->right = Nil;
                    }
                }
                // 进行修复操作
                removeFixup(Nil);
                // 断开Nil节点与树的连接，因为在红黑树中Nil节点通常是单独存在的
                dieConnectNil();
            }
        }
    }

    // 递归释放节点内存
    void deleteTree(Node* node) {
        if (node) {
            deleteTree(node->left);
            deleteTree(node->right);
            delete node;
        }
    }

public:
    // 构造函数
    RedBlackTree() :
            root(nullptr), size(0), Nil(new Node()) {
        Nil->color = Color::BLACK;
    }

    // 析构函数
    ~RedBlackTree() {
        deleteTree(root);
    }

    // 插入节点
    void insert(const Key& key, const Value& value) {
        insertNode(key, value);
    }

    // 删除节点
    void remove(const Key& key) {
        Node* nodeToBeRemoved = lookup(key);
        if (nodeToBeRemoved != nullptr) {
            deleteNode(nodeToBeRemoved);
            size--;
        }
    }

    // 获取红黑树元素个数
    int getSize() {
        return size;
    }

    // 清空红黑树
    void clear() {
        deleteTree(root);
        size = 0;
    }

    // 中序遍历打印
    void print() {
        inorderTraversal(root);
        cout << endl;
    }

    bool empty() {
        return size == 0;
    }

    Value *at(const Key &key) {
        auto ans = lookUp(key);
        if (ans != nullptr) {
            return &ans->value;
        }
        return nullptr;
    }
};

