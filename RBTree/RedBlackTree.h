#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H


template <typename KEY, typename VAL>
class RBTree
{
private:
    enum Color : unsigned char { RED, BLACK };

    class Node
    {
    public:
        explicit Node(const KEY& key, const VAL& val);

    public:
        KEY key;
        VAL val;
        Node* right;
        Node* left;
        Node* parent;
        Color color;
    };

public:
    void insert(const KEY& key, const VAL& val);
    void insertFixup(const Node& curr);
    void rotateLeft(const Node& curr);
    void rotateRight(const Node& curr);

private:
    Node* root;
};







// RBTree Impl
template <typename KEY, typename VAL>
void RBTree<KEY, VAL>::insert(const KEY& key, const VAL& val)
{
    auto curr = root;
    while (curr != nullptr)
    {
        if      (key < curr->key)   curr = curr->left;
        else if (key > curr->key)   curr = curr->right;
        else                        return;
    }
    Node node{key, val};

    if (root == nullptr)    root = &node;
    else
    {
        // Возможно заранее стоило-бы заготовить указать на parent тк curr здесь должен быть nullptr
        if (key < curr->parent->key)    curr->parent->left  = &node;
        else                            curr->parent->right = &node;
    }
    node.color = RED;

    // Восстановление красно-черных свойств
    insertFixup(node);
}



template <typename KEY, typename VAL>
void RBTree<KEY, VAL>::insertFixup(const Node& curr)
{
    while (curr.parent.color == RED)
    {
        if (curr.parent == curr.parent->parent->left) // Узел curr находится в левом поддереве g
        {
            auto u = curr.parent->parent->right;

            if (u->color == RED)    // Случай 1
            {
                curr.parent->color = BLACK;
                u->color = BLACK;
                curr.parent->parent->color = RED;
                curr = curr.parent->parent;
            }
            else
            {
                if (curr == curr.parent->right) // Случай 2
                {
                    curr = curr.parent;
                    rotateLeft(curr);
                }
                // Случай 3
                curr.parent->color = BLACK;
                curr.parent->parent->color = RED;
                rotateRight(curr.parent->parent);
            }
        }
        else    // curr находится в правом поддереве g (случаи 4-6)
        {

        }
    }

    root->color = BLACK;
}





// Node class Impl
template<typename KEY, typename VAL>
RBTree<KEY, VAL>::Node::Node(const KEY &_key, const VAL &_val) : key(_key), val(_val)
{

}

#endif // REDBLACKTREE_H


