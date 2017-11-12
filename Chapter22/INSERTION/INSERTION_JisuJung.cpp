//
//  main.cpp
//  insertion
//
//  Created by smartgrid_aict on 2017. 11. 11..
//  Copyright © 2017년 smartgrid_aict. All rights reserved.
//

#include <iostream>
using namespace std;

struct Node {
    int key, priority, size;
    Node *left, *right;
    Node(const int& _key) : key(_key), priority(rand()), size(1), left(NULL), right(NULL) {}
    void setLeft(Node *l) { left = l; calcSize(); }
    void setRight(Node *r) { right = r; calcSize(); }
    void calcSize() {
        size = 1;
        if(left) size += left->size;
        if(right) size += right->size;
    }
    
};


typedef pair<Node*, Node*> NodePair;

NodePair split(Node* root, int key) {
    if(root == NULL) return NodePair(NULL, NULL);
    
    if(root->key < key) {
        NodePair rs = split(root->right, key);
        root->setRight(rs.first);
        return NodePair(root, rs.second);
    }
    
    NodePair ls = split(root->left, key);
    root->setLeft(ls.second);
    return NodePair(ls.first, root);
}

Node* insert(Node* root, Node* node) {
    if(root == NULL) return node;
    
    // 우선순위가 크면 루트를 밀어내고 넣어야 함
    if(root->priority < node->priority) {
        NodePair splitted = split(root, node->key);
        node->setLeft(splitted.first);
        node->setRight(splitted.second);
        return node;
    }
    // root 보다 크면 오른쪽, 작으면 왼쪽
    else if(node->key < root->key) {
        root->setLeft(insert(root->left, node));
    } else {
        root->setRight(insert(root->right, node));
    }
    
    return root;
}

Node* merge(Node* a, Node* b) {
    if(a == NULL) return b;
    if(b == NULL) return a;
    // 우선순위가 더 큰 원소의 left로 작은 애를 넣는다.
    if(a->priority < b->priority) {
        b->setLeft(merge(a, b->left));
        return b;
    }
    a->setRight(merge(a->right, b));
    
    return a;
}

Node* kth(Node* root, int k) {
    int leftSize = 0;
    // 왼쪽은 작은 것들이 몰려있으니 왼쪽 부터 검사
    if(root->left != NULL) leftSize = root->left->size;
    if(k <= leftSize) return kth(root->left, k);
    if(k == leftSize + 1) return root;

    return kth(root->right, k-leftSize-1);
}

Node* erase(Node* root, int key) {
    if(root == NULL) return root;
    if(root->key == key) {
        Node* ret = merge(root->left, root->right);
        delete root;
        return ret;
    }
    
    if(key < root->key) {
        root->setLeft(erase(root->left, key));
    } else {
        root->setRight(erase(root->right, key));
    }
    
    return root;
}

int n, shifted[50000], A[50000];

void solve() {
    Node* cond = NULL;
    for(int i = 0 ; i < n; i++) {
        cond = insert(cond, new Node(i+1));
    }
    
    for(int i = n-1; i >= 0; i--) {
        int larger = shifted[i];
        Node* k = kth(cond, i+1-larger);
        A[i] = k->key;
        cond = erase(cond, k->key);
    }
}

int main(int argc, const char * argv[]) {
    
    freopen("/Users/smartgrid_aict/Desktop/algorithm/insertion/insertion/input.txt", "r", stdin);
    int T;
    cin >> T;
    while(T--) {
        cin >> n;
        for(int i = 0 ; i  < n; i++) {
            cin >> shifted[i];
        }
        
        solve();
        
        for(int i = 0 ; i < n; i++) {
            cout << A[i] << " ";
        }
        
        cout << endl;
        
    }
    return 0;
}
