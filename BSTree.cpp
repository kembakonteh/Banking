//
//  BSTree.cpp
//  Assignment6
//
//  Created by Kemba Konteh on 12/1/19.
//  Copyright © 2019 Kemba Konteh. All rights reserved.
//

#include "BSTree.hpp"


//#include "BSTree.h"


// constructor for BSTree class
BSTree::BSTree()
{
    this->root = nullptr;
}


// destructor for BSTree class
BSTree::~BSTree()
{
    Empty();
}


// empty the tree by de-allocating all the nodes
void BSTree::Empty()
{
    Free(this->root);
    this->root == nullptr;
}

// recursive helper function for implementing Empty()
void BSTree::Free(Node* node)
{
    if( node == nullptr )
        return;
    Free(node->left);
    Free(node->right);
    delete node;
}
        

// check whether the tree is empty or not
bool BSTree::isEmpty() const
{
    return (this->root == nullptr);
}


// insert object, parameter holds pointer to the account to be inserted
bool BSTree::Insert(Account* acct)
{
    int key = acct->getNumber();
    Node *prev, *current;
    current = this->root;
    while( current != nullptr )
    {
        if( key == (current->pAcct)->getNumber() )
            return false;
        prev = current;
        if( key < (current->pAcct)->getNumber() )
            current = current->left;
        else if( key > (current->pAcct)->getNumber() )
            current = current->right;
    }
    Node *newNode = new Node;
    newNode->pAcct = acct;
    newNode->left = nullptr;
    newNode->right = nullptr;
    if( key < (prev->pAcct)->getNumber() )
        prev->left = newNode;
    if( key > (prev->pAcct)->getNumber() )
        prev->right = newNode;
    return true;
}


// retrieve object, first parameter is the ID of the account
// second parameter holds pointer to found object, NULL if not found
bool BSTree::Retrieve(const int &key, Account* &acct) const
{
    acct = Find(this->root, key);
    if( acct == nullptr )
        return false;
    else
        return true;
}

// recursive helper function for implementing Retrieve()
Account* BSTree::Find(const Node* node, const int &key) const
{
    if( node == nullptr )
        return nullptr;
    if( key == (node->pAcct)->getNumber() )
        return (node->pAcct);
    if( key < (node->pAcct)->getNumber() )
        return Find(node->left, key);
    if( key > (node->pAcct)->getNumber() )
        return Find(node->right, key);
}


// display the contents of the tree to cout
void BSTree::Display() const
{
    DisplayNode(this->root);
}

// recursive helper function for implementing Display()
void BSTree::DisplayNode(const Node* node) const
{
    DisplayNode(node->left);
    (node->pAcct)->display();
    DisplayNode(node->right);
}
