#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

struct TreeNode {
    int key;
    char value; // Допоміжне поле
    TreeNode* left;
    TreeNode* right;
    int height;

    TreeNode(int k, char v) : key(k), value(v), left(nullptr), right(nullptr), height(1) {}
};

// Прототипи функцій
TreeNode* createBinaryTree(int n);
void printTree(TreeNode* root, TreeNode* highlight = nullptr);
TreeNode* createBinarySearchTree(int n);
TreeNode* insert(TreeNode* node, int key, char value);
TreeNode* balanceTree(TreeNode* root);
TreeNode* deleteLeaf(TreeNode* root, int key);
TreeNode* deleteSingleChild(TreeNode* root, int key);
TreeNode* deleteTwoChildren(TreeNode* root, int key);
TreeNode* deleteSubtree(TreeNode* root, int key);
TreeNode* findMin(TreeNode* root);
TreeNode* deleteNode(TreeNode* root, int key);
TreeNode* findMinElementInOrder(TreeNode* root);
void inorder(TreeNode* root);

// AVL специфічні функції
int height(TreeNode* N);
int max(int a, int b);
TreeNode* rightRotate(TreeNode* y);
TreeNode* leftRotate(TreeNode* x);
int getBalance(TreeNode* N);

void menu();

// Основна функція
int main() {
    TreeNode* root = nullptr;
    int choice, n, key;
    char value;

    do {
        cout << "\nМеню:\n";
        cout << "1. Створити бінарне дерево\n";
        cout << "2. Вивести бінарне дерево\n";
        cout << "3. Створити бінарне дерево пошуку\n";
        cout << "4. Додати новий елемент у бінарне дерево пошуку\n";
        cout << "5. Збалансувати бінарне дерево пошуку\n";
        cout << "6. Видалити лист бінарного дерева\n";
        cout << "7. Видалити елемент із одним дочірнім вузлом\n";
        cout << "8. Видалити елемент із двома дочірніми вузлами\n";
        cout << "9. Видалити піддерево\n";
        cout << "10. Знайти перший елемент із мінімальним значенням (інфіксний обхід)\n";
        cout << "0. Вийти\n";
        cout << "Ваш вибір: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Введіть кількість елементів: ";
                cin >> n;
                root = createBinaryTree(n);
                break;
            case 2:
                printTree(root);
                break;
            case 3:
                cout << "Введіть кількість елементів: ";
                cin >> n;
                root = createBinarySearchTree(n);
                break;
            case 4:
                cout << "Введіть ключ та значення для додавання (ціле число і символ): ";
                cin >> key >> value;
                root = insert(root, key, value);
                break;
            case 5:
                root = balanceTree(root);
                break;
            case 6:
                cout << "Введіть ключ листа для видалення: ";
                cin >> key;
                root = deleteLeaf(root, key);
                break;
            case 7:
                cout << "Введіть ключ елемента із одним дочірнім вузлом для видалення: ";
                cin >> key;
                root = deleteSingleChild(root, key);
                break;
            case 8:
                cout << "Введіть ключ елемента із двома дочірніми вузлами для видалення: ";
                cin >> key;
                root = deleteTwoChildren(root, key);
                break;
            case 9:
                cout << "Введіть ключ кореня піддерева для видалення: ";
                cin >> key;
                root = deleteSubtree(root, key);
                break;
            case 10:
            {
                TreeNode* minNode = findMinElementInOrder(root);
                if (minNode) {
                    cout << "Перший елемент із мінімальним значенням: " << minNode->key << " " << minNode->value << endl;
                } else {
                    cout << "Дерево порожнє.\n";
                }
            }
                break;
            case 0:
                cout << "Вихід...\n";
                break;
            default:
                cout << "Невірний вибір, спробуйте ще раз.\n";
        }
    } while (choice != 0);
}

TreeNode* createBinaryTree(int n) {
    if (n <= 0) return nullptr;
    TreeNode* root = new TreeNode(rand() % 100, 'A' + rand() % 26);
    queue<TreeNode*> q;
    q.push(root);

    for (int i = 1; i < n; ++i) {
        TreeNode* node = q.front();
        q.pop();
        if (!node->left) {
            node->left = new TreeNode(rand() % 100, 'A' + rand() % 26);
            q.push(node->left);
        } else if (!node->right) {
            node->right = new TreeNode(rand() % 100, 'A' + rand() % 26);
            q.push(node->right);
        } else {
            q.push(node);
        }
    }
    return root;
}

void printTree(TreeNode* root, TreeNode* highlight) {
    if (!root) return;
    queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
        int levelSize = q.size();
        while (levelSize--) {
            TreeNode* node = q.front();
            q.pop();
            if (node == highlight) {
                cout << "[" << node->key << "," << node->value << "] ";
            } else {
                cout << node->key << "," << node->value << " ";
            }
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
        cout << endl;
    }
}

TreeNode* createBinarySearchTree(int n) {
    if (n <= 0) return nullptr;
    TreeNode* root = nullptr;

    for (int i = 0; i < n; ++i) {
        int key = rand() % 100;
        char value = 'A' + rand() % 26;
        root = insert(root, key, value);
    }
    return root;
}

int height(TreeNode* N) {
    if (N == nullptr)
        return 0;
    return N->height;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

TreeNode* rightRotate(TreeNode* y) {
    TreeNode* x = y->left;
    TreeNode* T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    // Return new root
    return x;
}

TreeNode* leftRotate(TreeNode* x) {
    TreeNode* y = x->right;
    TreeNode* T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    // Return new root
    return y;
}

int getBalance(TreeNode* N) {
    if (N == nullptr)
        return 0;
    return height(N->left) - height(N->right);
}

TreeNode* insert(TreeNode* node, int key, char value) {
    if (node == nullptr)
        return new TreeNode(key, value);

    if (key < node->key)
        node->left = insert(node->left, key, value);
    else if (key > node->key)
        node->right = insert(node->right, key, value);
    else // Duplicate keys are not allowed in BST
        return node;

    node->height = 1 + max(height(node->left), height(node->right));

    int balance = getBalance(node);

    // Left Left Case
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    // Left Right Case
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

TreeNode* findMin(TreeNode* root) {
    while (root->left) root = root->left;
    return root;
}

TreeNode* deleteNode(TreeNode* root, int key) {
    if (!root) return root;

    if (key < root->key) {
        root->left = deleteNode(root->left, key);
    } else if (key > root->key) {
        root->right = deleteNode(root->right, key);
    } else {
        if (!root->left || !root->right) {
            TreeNode* temp = root->left ? root->left : root->right;

            if (!temp) {
                temp = root;
                root = nullptr;
            } else
                *root = *temp;

            delete temp;
        } else {
            TreeNode* temp = findMin(root->right);

            root->key = temp->key;
            root->value = temp->value;

            root->right = deleteNode(root->right, temp->key);
        }
    }

    if (!root) return root;

    root->height = 1 + max(height(root->left), height(root->right));

    int balance = getBalance(root);

    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

TreeNode* deleteLeaf(TreeNode* root, int key) {
    TreeNode* node = root;
    TreeNode* parent = nullptr;

    while (node && node->key != key) {
        parent = node;
        if (key < node->key) {
            node = node->left;
        } else {
            node = node->right;
        }
    }

    if (!node || (node->left || node->right)) return root;

    if (!parent) {
        delete root;
        return nullptr;
    }

    if (parent->left == node) {
        parent->left = nullptr;
    } else {
        parent->right = nullptr;
    }
    delete node;
    return root;
}

TreeNode* deleteSingleChild(TreeNode* root, int key) {
    TreeNode* node = root;
    TreeNode* parent = nullptr;

    while (node && node->key != key) {
        parent = node;
        if (key < node->key) {
            node = node->left;
        } else {
            node = node->right;
        }
    }

    if (!node || (node->left && node->right)) return root;

    TreeNode* child = node->left ? node->left : node->right;

    if (!parent) {
        delete root;
        return child;
    }

    if (parent->left == node) {
        parent->left = child;
    } else {
        parent->right = child;
    }
    delete node;
    return root;
}

TreeNode* deleteTwoChildren(TreeNode* root, int key) {
    return deleteNode(root, key);
}

TreeNode* deleteSubtree(TreeNode* root, int key) {
    return deleteNode(root, key);
}

TreeNode* findMinElementInOrder(TreeNode* root) {
    static TreeNode* minNode = nullptr;
    if (!root) return minNode;

    findMinElementInOrder(root->left);
    if (!minNode || root->key < minNode->key) {
        minNode = root;
    }
    findMinElementInOrder(root->right);

    return minNode;
}

void inorder(TreeNode* root) {
    if (!root) return;
    inorder(root->left);
    cout << root->key << "," << root->value << " ";
    inorder(root->right);
}

TreeNode* balanceTree(TreeNode* root) {
    return root;
}
