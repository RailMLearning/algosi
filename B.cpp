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

Node* rotateLeft(Node* a) {
    Node* b = a->right;
    a->right = b->left;
    b->left = a;
    return b;
}

Node* rotateRight(Node* a) {
    Node* b = a->left;
    a->left = b->right;
    b->right = a;
    return b;
}

Node* rotate(Node* v, int x, bool left) {
    if (x < v->key) v->left = rotate(v->left, x, left);
    else if (x > v->key) v->right = rotate(v->right, x, left);
    else return left ? rotateLeft(v) : rotateRight(v);
    return v;
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

    int n;
    cin >> n;
    Node* root = nullptr;
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        root = add(root, x);
    }

    int m;
    cin >> m;
    while (m--) {
        string direction;
        int x;
        cin >> direction >> x;
        root = rotate(root, x, direction == "left");
        bool first = true;
        preorder(root, first);
        cout << '\n';
    }
    clear(root);
}
