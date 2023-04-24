#include "treeNode.h"
#include<iostream>

TreeNode::TreeNode(std::string cntt): content {cntt} {}

std::string TreeNode::getContent() const {
  // your code starts here
  return this->content;
}

TreeNode *TreeNode::getLeftChild() const {
  // your code starts here
  return this->leftChild;
}
TreeNode *TreeNode::getRightChild() const {
  // your code starts here
  return this->rightChild;
}

void TreeNode::updateLeftChild(TreeNode *lChild) {
  // your code starts here
   this->leftChild=lChild;
}

void TreeNode::updateChildren(TreeNode *lChild, TreeNode *rChild) {
  // your code starts here
  this->leftChild= lChild;
  this->rightChild= rChild;
}


OperatorNode::OperatorNode(std::string cntt): TreeNode{cntt} {}

ConstantNode::ConstantNode(std::string cntt): TreeNode{cntt} {}



VariableNode::VariableNode(std::string cntt): TreeNode{cntt} {}
                                                                                                 

TreeNode::~TreeNode() {
  // your code starts here
  delete this->leftChild;
  delete this->rightChild;

}

void TreeNode::printDFS_post(TreeNode* root)
{
   if(root==NULL)
    return;
   printDFS_post(root->leftChild);
   printDFS_post(root->rightChild);
   std::cout<<root->content<<" ";
}