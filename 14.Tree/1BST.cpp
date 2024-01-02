#include <iostream>
using namespace std;
struct node
{
    node *left;
    int item;
    node *right;
    node(int data)
    {
        left = NULL;
        item = data;
        right = NULL;
    }
};
class BST
{
private:
    node *root;

protected:
    void preorderrec(node *);
    void inorderrec(node *);
    void postorderrec(node *);
    node *deleteNode(node *, int);

public:
    BST();
    bool isEmpty();
    void insert(int);
    void preorder();
    void inorder();
    void postorder();
    void del(int);
    node *search(int);
    ~BST();
};
BST::BST()
{
    root = NULL;
}
bool BST::isEmpty()
{
    return root == NULL;
}
void BST::insert(int data)
{
    node *n = new node(data);
    node *temp;
    if (root == NULL)
    {
        root = n;
    }
    else
    {
        temp = root;
        while (n->item != temp->item)
        {
            if (n->item < temp->item)
            {
                if (temp->left != NULL)
                {
                    temp = temp->left;
                }
                else
                {
                    temp->left = n;
                    break;
                }
            }
            else
            {
                if (temp->right != NULL)
                {
                    temp = temp->right;
                }
                else
                {
                    temp->right = n;
                    break;
                }
            }
        }
        if (temp->item == n->item)
            delete n;
    }
}
void BST::preorderrec(node *temp)
{
    if (temp)
    {
        cout << temp->item << " ";
        preorderrec(temp->left);
        preorderrec(temp->right);
    }
}
void BST::inorderrec(node *temp)
{
    if (temp)
    {
        preorderrec(temp->left);
        cout << temp->item << " ";
        preorderrec(temp->right);
    }
}
void BST::postorderrec(node *temp)
{
    if (temp)
    {
        preorderrec(temp->left);
        preorderrec(temp->right);
        cout << temp->item << " ";
    }
}
void BST::preorder()
{
    preorderrec(root);
}
void BST::inorder()
{
    inorderrec(root);
}
void BST::preorder()
{
    postorderrec(root);
}
node *BST::deleteNode(node *temp, int data)
{
    if (temp == NULL)
        return NULL;
    if (data < temp->item)
    {
        temp->left = deleteNode(temp->left, data);
    }
    else if (data > temp->item)
    {
        temp->right = deleteNode(temp->right, data);
    }
    else
    {
        // No Child
        if (temp->left == NULL && temp->right == NULL)
        {
            delete temp;
            return NULL;
        }
        // Single Child
        if (temp->left == NULL || temp->right == NULL)
        {
            node *child = temp->left ? temp->left : temp->right;
            delete temp;
            return child;
        }
        // Two Children
        node *pred, *parpred;
        parpred = temp;
        pred = temp->left;
        while (pred->right != NULL)
        {
            parpred = pred;
            pred = pred->right;
        }
        temp->item = pred->item;
        if (parpred->right == pred)
            parpred->right = deleteNode(pred, pred->item);
        else if (parpred->left == pred)
            parpred->left = deleteNode(pred, pred->item);
    }
    return temp;
}
void BST::del(int data)
{
    root = deleteNode(root, data);
}
node *BST::search(int data)
{
    node *temp = root;
    while (temp)
    {
        if (temp->item == data)
            return temp;
        if (data < temp->item)
            temp = temp->left;
        else
            temp = temp->right;
    }
    return temp; // OR return NULL;
}
BST::~BST()
{
    while(root)
    {
        del(root->item);
    }
}