#include <gtest/gtest.h>
#include "../main.cpp"

TEST(BinaryTreeTest, Insert) {
    TreeNode* root = nullptr;

    root = insert(root, 10, 'A');
    root = insert(root, 20, 'B');
    root = insert(root, 5, 'C');

    EXPECT_EQ(root->key, 10);
    EXPECT_EQ(root->value, 'A');

    EXPECT_EQ(root->left->key, 5);
    EXPECT_EQ(root->left->value, 'C');

    EXPECT_EQ(root->right->key, 20);
    EXPECT_EQ(root->right->value, 'B');

    delete root->left;
    delete root->right;
    delete root;
}