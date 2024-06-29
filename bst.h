#ifndef BST_H
#define BST_H

#pragma once
#include "book.h"

#include <string>
#include <vector>

// Book Management team (Jackson Hopkins and Ian Laabs) work implemented here

class BST {
public:
    BST();
    ~BST();
    void insert(const Book& book);
    std::vector<Book> search(const std::string& query) const;

private:
struct TreeNode {
        Book book;
        TreeNode* left;
        TreeNode* right;
        TreeNode(const Book& book) : book(book), left(nullptr), right(nullptr) {}
    };

    TreeNode* root;
    void insert(TreeNode*& node, const Book& book);
    void search(TreeNode* node, const std::string& query, std::vector<Book>& results) const;
    void clear(TreeNode* node);
    void inorderTraversal(TreeNode* node) const;
};

#endif // BST_H
