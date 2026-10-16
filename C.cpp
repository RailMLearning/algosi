#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

struct Node {
    int key;
    int height = 1;
    Node* left = nullptr;
    Node* right = nullptr;

    explicit Node(int x) : key(x) {}
};

int height(Node* v) {
    return v ? v->height : 0;
}

void update(Node* v) {
    v->height = 1 + max(height(v->left), height(v->right));
}

int balanceFactor(Node* v) {
    return height(v->right) - height(v->left);
}

Node* rotateLeft(Node* a) {
    Node* b = a->right;
    a->right = b->left;
    b->left = a;
    update(a);
    update(b);
    return b;
}

Node* rotateRight(Node* a) {
    Node* b = a->left;
    a->left = b->right;
    b->right = a;
    update(a);
    update(b);
    return b;
}

Node* balance(Node* v) {
    update(v);
    if (balanceFactor(v) == 2) {
        if (balanceFactor(v->right) < 0) {
            v->right = rotateRight(v->right);
        }
        return rotateLeft(v);
    }
    if (balanceFactor(v) == -2) {
        if (balanceFactor(v->left) > 0) {
            v->left = rotateLeft(v->left);
        }
        return rotateRight(v);
    }
    return v;
}

Node* add(Node* v, int x) {
    if (!v) return new Node(x);
    if (x < v->key) v->left = add(v->left, x);
    else if (x > v->key) v->right = add(v->right, x);
    else return v;
    return balance(v);
}

bool exists(Node* v, int x) {
    while (v) {
        if (x == v->key) return true;
        v = x < v->key ? v->left : v->right;
    }
    return false;
}

void preorder(Node* v, bool& first) {
    if (!v) return;
    if (!first) cout << ' ';
    cout << v->key;
    first = false;
    preorder(v->left, first);
    preorder(v->right, first);
}

void clear(Node* v) {
    if (!v) return;
    clear(v->left);
    clear(v->right);
    delete v;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int q;
    cin >> q;
    Node* root = nullptr;
    while (q--) {
        string cmd;
        cin >> cmd;
        if (cmd == "add" || cmd == "exists") {
            int x;
            cin >> x;
            if (cmd == "add") root = add(root, x);
            else cout << (exists(root, x) ? "YES" : "NO") << '\n';
        } else if (cmd == "root") {
            if (root) cout << root->key << '\n';
            else cout << "Empty\n";
        } else if (cmd == "height") {
            cout << height(root) << '\n';
        } else if (cmd == "print") {
            bool first = true;
            if (!root) cout << "Empty";
            else preorder(root, first);
            cout << '\n';
        }
    }
    clear(root);
}
