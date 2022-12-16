/******************************************
 * My Name is   : Kelvin Do
 * My NSHEID is : 2001770482
 * My Email is  : dok7@unlv.nevada.edu
 * binTree.hpp Does the Following: 
 * implementation file
 * contains binTree class to manage binary trees
******************************************/
#include <iostream>
#include <vector>
using namespace std;

template <typename type>
class binTree
{
    struct binTreeNode
    {
        type data;
        binTreeNode *left;
        binTreeNode *right;
    };

public:
    class binTreeIterator
    {
    public:
        friend class binTree;
        binTreeIterator();
        binTreeIterator(binTreeNode *);
        binTreeIterator leftChild() const;
        binTreeIterator rightChild() const;
        type &operator*() const;
        bool operator==(const binTreeIterator &) const;
        bool operator!=(const binTreeIterator &) const;

    private:
        binTreeNode *binTreeNodePointer;
    };

    binTree();
    binTree(const binTree<type> &);
    const binTree &operator=(const binTree<type> &);
    ~binTree();

    void buildTree(std::vector<type>);
    binTreeIterator rootIterator() const;

private:
    void destroyTree(binTreeNode *);
    void copyTree(binTreeNode *, binTreeNode *);
    void buildTree(std::vector<type>, binTreeNode *, int);

    binTreeNode *root;
};

/**********************************************
 *  binTreeIterator
 *      default constructor
 *      set binTreeNodePointer to NULL
**********************************************/
template <typename type>
binTree<type>::binTreeIterator::binTreeIterator()
{
    binTreeNodePointer = NULL;
}

/**********************************************
 *  binTreeIterator
 *      default constructor with parameter
 *      set binTreeNodePointer to the pointer passed in
**********************************************/
template <typename type>
binTree<type>::binTreeIterator::binTreeIterator(binTreeNode *ptr)
{
    binTreeNodePointer = ptr;
}

/**********************************************
 *  leftChild
 *      return the left node of the current pointer
**********************************************/
template <typename type>
typename binTree<type>::binTreeIterator binTree<type>::binTreeIterator::leftChild() const
{
    return binTreeNodePointer->left;
}

/**********************************************
 *  rightChild
 *      return the right node of the current pointer
**********************************************/
template <typename type>
typename binTree<type>::binTreeIterator binTree<type>::binTreeIterator::rightChild() const
{
    return binTreeNodePointer->right;
}

/**********************************************
 *  operator*
 *      dereferencing operator
 *      returns data within current node
**********************************************/
template <typename type>
type &binTree<type>::binTreeIterator::operator*() const
{
    return binTreeNodePointer->data;
}

/**********************************************
 *  operator==
 *      return true if two binTreeNodePointers are equal to each other
 *      else return false
**********************************************/
template <typename type>
bool binTree<type>::binTreeIterator::operator==(const binTree<type>::binTreeIterator &rhs) const
{
    if (binTreeNodePointer == rhs.binTreeNodePointer)
    {
        return true;
    }

    return false;
}

/**********************************************
 *  operator!=
 *      return true if two binTreeNodePointers are NOT equal to each other
 *      else return false
**********************************************/
template <typename type>
bool binTree<type>::binTreeIterator::operator!=(const binTree<type>::binTreeIterator &rhs) const
{
    if (binTreeNodePointer != rhs.binTreeNodePointer)
    {
        return true;
    }

    return false;
}

/**********************************************
 *  binTree
 *      default constructor
 *      set the root to NULL
**********************************************/
template <typename type>
binTree<type>::binTree()
{
    root = NULL;
}

/**********************************************
 *  binTree
 *      default constructor with parameter
 *      set the root the same root as another tree being passed in
 *      call copyTree
**********************************************/
template <typename type>
binTree<type>::binTree(const binTree<type> &copy)
{
    root = new binTreeNode;
    root->data = copy.root->data;
    root->left = NULL;
    root->right = NULL;
    copyTree(root, copy.root);
}

/**********************************************
 *  operator=
 *      assignment operator
 *      return *this
**********************************************/
template <typename type>
const binTree<type> &binTree<type>::operator=(const binTree<type> &rhs)
{
    destroyTree(root);
    root = NULL;
    if (rhs.root == NULL)
    {
        return *this;
    }

    root = new binTreeNode;
    root->data = rhs.root->data;
    root->left = NULL;
    root->right = NULL;
    copyTree(root, rhs.root);

    return *this;
}

/**********************************************
 *  ~binTree
 *      call destroyTree with the root of the binary tree
**********************************************/
template <typename type>
binTree<type>::~binTree()
{
    destroyTree(root);
}

/**********************************************
 *  buildTree
 *      parameter: vector of values
 *      set the root to the first value within a vector
 *      set the left and right node to NULL
 *      call buildTree recursively
**********************************************/
template <typename type>
void binTree<type>::buildTree(std::vector<type> treeValues)
{
    root = new binTreeNode;
    root->data = treeValues[0];
    root->left = NULL;
    root->right = NULL;

    buildTree(treeValues, root, 0);
}

/**********************************************
 *  buildTree
 *      overloaded function, more parameters
 *      parameter: vector of values
 *      parameter: travseral pointer
 *      parameter: element index for the vector
 *      set the root to the first value within a vector
 *      set the left and right node to NULL
 *      call buildTree recursively
**********************************************/
template <typename type>
void binTree<type>::buildTree(std::vector<type> treeValues, binTreeNode *r, int index)
{
    int leftIndex = index * 2 + 1;
    int rightIndex = (index + 1) * 2;

    //check if the value being add is out of bounds
    if (treeValues[leftIndex] == -1 || leftIndex > treeValues.size() - 1)
    {
        r->left = NULL;
        return;
    }
    //if not, then add the value to the binary tree
    else
    {
        r->left = new binTreeNode;
        r->left->data = treeValues[leftIndex];
        r->left->left = nullptr;
        r->left->right = nullptr;
        //recursively call buildTree for leftIndex
        buildTree(treeValues, r->left, leftIndex);
    }

    //check if the value being add is out of bounds
    if (treeValues[rightIndex] == -1 || rightIndex > treeValues.size() - 1)
    {
        r->right = NULL;
        return;
    }
    //if not, then add the value to the binary tree
    else
    {
        r->right = new binTreeNode;
        r->right->data = treeValues[rightIndex];
        r->right->left = nullptr;
        r->right->right = nullptr;
        //recursively call buildTree for rightIndex
        buildTree(treeValues, r->right, rightIndex);
    }
}

/**********************************************
 *  rootIterator
 *      create an iterator starting at the root of a binary tree
 *      return the iterator
**********************************************/
template <typename type>
typename binTree<type>::binTreeIterator binTree<type>::rootIterator() const
{
    binTreeIterator head(root);
    return head;
}

/**********************************************
 *  destroyTree
 *      call postorder traversal
 *      start from the back of the binary tree
 *      delete the node
 *      recursively delete the tree
**********************************************/
template <typename type>
void binTree<type>::destroyTree(binTreeNode *r)
{
    if (r != NULL)
    {
        destroyTree(r->left);
        destroyTree(r->right);
        delete r;
    }
}

/**********************************************
 *  copyTree
 *      parameter: i is root and j is copy.root
 *      begin to recursively copy the tree
 *      copy contents of j to i
**********************************************/
template <typename type>
void binTree<type>::copyTree(binTreeNode *i, binTreeNode *j)
{
    //if a left node exists in with the tree being copied
    if (j->left != NULL)
    {
        //copy the value to the tree
        i->left = new binTreeNode;
        i->left->data = j->left->data;
        //establish its left and right node as NULL
        i->left->left = NULL;
        i->left->right = NULL;
        //recursively call copyTree
        copyTree(i->left, j->left);
    }

    //if a right node exists in with the tree being copied
    if (j->right != NULL)
    {
        //copy the value to the tree
        i->right = new binTreeNode;
        i->right->data = j->right->data;
        //establish its left and right node as NULL
        i->right->left = NULL;
        i->right->right = NULL;
        //recursively call copyTree
        copyTree(i->right, j->right);
    }
}
