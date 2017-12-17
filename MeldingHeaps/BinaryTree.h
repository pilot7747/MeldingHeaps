//
//  BinaryTree.h
//  MeldingHeaps
//
//  Created by Nikita Pavlichenko on 05.12.2017.
//  Copyright © 2017 Nikita Pavlichenko. All rights reserved.
//

#ifndef BinaryTree_h
#define BinaryTree_h

template<typename T>
struct Node {
    Node* left;
    Node* right;
    T key;
    size_t dist;
};

template <typename T>
using BinaryTree = Node<T>*;

template <typename T>
void DeleteTree(BinaryTree<T> root) {
    if (root == nullptr)
        return;
    /*if (root->left == nullptr && root->right == nullptr)
        delete root;
    DeleteTree(root->left);
    DeleteTree(root->right);*/
    if(root->left != nullptr) DeleteTree(root->left);
    if(root->right != nullptr) DeleteTree(root->right);
    delete root;
}

template <typename T>
BinaryTree<T> make_binary_tree(T key) {
    Node<T>* tempNode = new Node<T>();
    tempNode->left = nullptr;
    tempNode->right = nullptr;
    tempNode->key = key;
    tempNode->dist = 0;
    return tempNode;
}


#endif /* BinaryTree_h */
