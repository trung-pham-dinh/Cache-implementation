//#include "main.h"
#include "Cache.h"
Cache::Cache(SearchEngine* s,ReplacementPolicy* r):rp(r),s_engine(s) {}
Cache::~Cache(){
	delete rp;
	delete s_engine;
}
Data* Cache::read(int addr) {
    return NULL;
}
Elem* Cache::put(int addr, Data* cont) {
    return NULL;
}
Elem* Cache::write(int addr, Data* cont) {
    return NULL;
}
void Cache::printRP() {
}
void Cache::printSE() {
}


// AVL implementation

bool AVL::checkAllBalance() {
    return checkAllBalance(root);
}
bool AVL::checkAllBalance(Node* node) {
    if(node == NULL) return true;
    
    int bfVal = bf(node);
    if(bfVal >= -1 && bfVal <= 1) {
        bool left = checkAllBalance(node->left);
        bool right = checkAllBalance(node->right);
        return left&&right;
    }
    return false;
}
Elem* AVL::search(int addr) {
    Node* curr = root;
    while(curr) {
        if(addr == curr->getAddr()) {
            return curr->elem;
        }
        curr = (addr < curr->getAddr())? curr->left:curr->right;
    }
    return NULL;
}
Node* AVL::remove(Node* pNode, Elem* e) {
    
    if(pNode == NULL) {
        return pNode;
    }
    
    if(e->addr < pNode->getAddr()) {
        pNode->left = remove(pNode->left, e);
    }
    else if(e->addr > pNode->getAddr()) {
        pNode->right = remove(pNode->right, e);
    }
    else {
        if(pNode->isLeaf()) {
            delete pNode;
            count--;
            return NULL;
        }
        else if(!pNode->left) {
            Node* tmp = pNode->right;
            pNode->left = NULL; pNode->right = NULL;
            delete pNode;
            count--;
            return tmp;
        }
        else if(!pNode->right) {
            Node* tmp = pNode->left;
            pNode->left = NULL; pNode->right = NULL;
            delete pNode;
            count--;
            return tmp;
        }
        else {
//            cout<<"remove: ";
//            pNode->elem->print();
               
            Node* leftmost = min(pNode->right);
//            cout<<"leftmost: ";
//            leftmost->elem->print();
            // swap elem because preventing the case delete the elem tha we still use(if Node's destructor delete elem)
            Elem* tmp = pNode->elem;
            pNode->elem = leftmost->elem;
            leftmost->elem = tmp;
            
            pNode->right = remove(pNode->right, leftmost->elem);

        }
    }
    if(pNode == NULL) return pNode; // can exist this case when delete 1 node tree
    
    pNode->height = 1 + greater(height(pNode->left), height(pNode->right));
    
    balance(pNode);
    
    return pNode;
}
int AVL::height(Node* node) {
    if(node == NULL) return 0;
    else
        return node->height;
}
void AVL::insert(Node*& pNode, Elem* e) {
    if(pNode == NULL) {
        pNode = new Node(e);
        return;
    }
    
    if(e->addr < pNode->getAddr()) {
        insert(pNode->left, e);
    }
    else {
        insert(pNode->right, e);
    }
    
    pNode->height = 1 + greater(height(pNode->left), height(pNode->right));
    
    balance(pNode);
    
}

bool AVL::balance(Node*& pNode) { 
//    cout<<"check balance: ";
//    pNode->elem->print();
    if(pNode == NULL || pNode->isLeaf()) return true; 
    int bfVal = bf(pNode);
    if(bfVal > 1) {
        if(bf(pNode->left) >= 0) { // check if  there is '=' here
            LL(pNode);
        }
        else {
            LR(pNode);
        }
        return false;
    }
    else if(bfVal < -1) {
        if(bf(pNode->right) > 0) { 
            RL(pNode);
        }
        else { // check if  there is '=' here
            RR(pNode);
        }
        return false;
    }
    return true;
}
void AVL::LL(Node*& pNode) {
    Node* leftChild = pNode->left;
    pNode->left = leftChild->right;
    leftChild->right = pNode;
    pNode = leftChild;
    
    pNode->right->height = 1 + greater(height(pNode->right->left), height(pNode->right->right));
    pNode->height = 1 + greater(height(pNode->left), height(pNode->right));
}
void AVL::RR(Node*& pNode) {
    Node* rightChild = pNode->right;
    pNode->right = rightChild->left;
    rightChild->left = pNode;
    pNode = rightChild;
    
    pNode->left->height = 1 + greater(height(pNode->left->left), height(pNode->left->right));
    pNode->height = 1 + greater(height(pNode->left), height(pNode->right));
}
void AVL::LR(Node*& pNode) {
    RR(pNode->left);
    LL(pNode);
}
void AVL::RL(Node*& pNode) {
    LL(pNode->right);
    RR(pNode);
}