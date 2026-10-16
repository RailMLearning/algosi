#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

struct Node {
    int key;
    Node* left = nullptr;
    Node* right = nullptr;

    explicit Node(int x) : key(x) {}
};

Node* add(Node* v, int x) {
    if (!v) return new Node(x);
    if (x < v->key) v->left = add(v->left, x);
    if (x > v->key) v->right = add(v->right, x);
    return v;
}

Node* erase(Node* v, int x) {
    if (!v) return nullptr;
    if (x < v->key) {
        v->left = erase(v->left, x);
    } else if (x > v->key) {
        v->right = erase(v->right, x);
    } else {
        if (!v->left || !v->right) {
            Node* child = v->left ? v->left : v->right;
            delete v;
            return child;
        }
        Node* next = v->right;
        while (next->left) next = next->left;
        v->key = next->key;
        v->right = erase(v->right, next->key);
    }
    return v;
}

bool exists(Node* v, int x) {
    while (v) {
        if (x == v->key) return true;
        v = x < v->key ? v->left : v->right;
    }
    return false;
}

int height(Node* v) {
    if (!v) return 0;
    return 1 + max(height(v->left), height(v->right));
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
        if (cmd == "add" || cmd == "del" || cmd == "exists") {
            int x;
            cin >> x;
            if (cmd == "add") root = add(root, x);
            else if (cmd == "del") root = erase(root, x);
            else cout << (exists(root, x) ? "YES" : "NO") << '\n';
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
