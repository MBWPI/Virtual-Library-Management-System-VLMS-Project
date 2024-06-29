#include "bst.h"

#include <iostream>

// Book Management team (Jackson Hopkins and Ian Laabs) work implemented here

BST::BST() : root(nullptr) {}

BST::~BST() {
    clear(root);
}

void BST::insert(const Book& book) {
    insert(root, book);
}

void BST::insert(TreeNode*& node, const Book& book) {
    if (!node) {
        node = new TreeNode(book);
    } else if (book.getTitle() < node->book.getTitle()) {
        insert(node->left, book);
    } else {
        insert(node->right, book);
    }
}

std::vector<Book> BST::search(const std::string& query) const {
    std::vector<Book> results;
    search(root, query, results);
    return results;
}

void BST::search(TreeNode* node, const std::string& query, std::vector<Book>& results) const {
    if (!node) return;
    if (node->book.getTitle().find(query) == 0) {  // Check if the title starts with the query
        results.push_back(node->book);
    }
    search(node->left, query, results);
    search(node->right, query, results);
}

void BST::clear(TreeNode* node) {
    if (!node) return;
    clear(node->left);
    clear(node->right);
    delete node;
}

void BST::inorderTraversal(TreeNode* node) const {
    if (!node) return;
    inorderTraversal(node->left);
    // Process the node (e.g., print the book details)
    inorderTraversal(node->right);
}
