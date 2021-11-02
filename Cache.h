#ifndef CACHE_H
#define CACHE_H

#include "main.h"


class ReplacementPolicy {
protected:
	int count;
	Elem** arr;
	
public:
	virtual int insert(Elem* e,int idx) = 0;//insert e into arr[idx] if idx != -1 else into the position by replacement policy
	virtual void access(int idx) = 0;//idx is index in the cache of the accessed element 
	virtual int remove() = 0; 
	virtual void print() = 0;
	
	bool isFull() {return count == MAXSIZE;}
	bool isEmpty() {return count == 0;}
	Elem* getValue(int idx){return arr[idx];}
	void replace(int idx,Elem* e) {
		delete arr[idx];
		access(idx);
		arr[idx] = e;
	}
};

class SearchEngine {
public:
	virtual Elem* search(int) = 0; // -1 if not found
	virtual void insert(Elem*) = 0;
	virtual	void remove(Elem*) = 0;
	virtual void print() = 0;
};

class FIFO : public ReplacementPolicy {
public:
	FIFO(){count = 0; arr = new Elem*[MAXSIZE];}
	~FIFO(){}
	int insert(Elem* e,int idx){return 0;}
	void access(int idx) {}
	int remove(){return 0;}
	void print(){}
};

class MRU : public ReplacementPolicy {
public:
	MRU(){}
	~MRU(){}
	int insert(Elem* e,int idx){return 0;}
	void access(int idx){}
	int remove(){return 0;}
	void print(){}
};
class LRU: public MRU {
public:
	int remove() override {return 0;}
};

class LFU: public ReplacementPolicy {
public:
	LFU(){}
	~LFU(){}
	int insert(Elem* e,int idx){return 0;}
	void access(int idx){}
	int remove(){return 0;}
	void print(){}
};

class DBHashing: public SearchEngine {
public:
	DBHashing(int (*h1)(int),int (*h2)(int),int s){}
	~DBHashing(){}
	Elem* search(int){return NULL;};// -1 if not found
	void insert(Elem*){}
	void remove(Elem*){}
	void print(){}
};

class Node {
public:
    Elem* elem;
    Node* left;
    Node* right;
    int height;
    
    Node(){left = right = NULL; elem = NULL; height = 0;}
    Node(Elem* e, Node* l = NULL, Node* r = NULL) {
//        static int num = 1;
//        cout<<"node "<<num<<" created"<<endl; // check if delete all
//        num++;
        
        elem = e; // point to the elem that exist in queue
        left = l; right = r;
        height = 1;
    }
    ~Node() {
//        static int num = 1;
//        cout<<"node "<<num<<" deleted"<<endl; // check if delete all
//        num++;
        
        // we cannot delete because we must return the del elem
        //if(elem && elem->data) delete elem;
        if(left) delete left;
        if(right) delete right;
    }
    bool isLeaf() {
        if(left == NULL && right == NULL) {
            return true;
        }
        else {
            return false;
        }
    }
    int getAddr() {return elem->addr;}
    Data* getData() {return elem->data;}
};
class AVL : public SearchEngine{
    Node* root;
    int count;

    // helper function
    void insert(Node*&, Elem*);
    //bool remove(Node*&, Elem*);
    Node* remove(Node*, Elem*);
    void inorder(Node* curr) {
        if(curr == NULL) return;
        
        inorder(curr->left);
        curr->elem->print();
        inorder(curr->right);
    }
    void preorder(Node* curr) {
        if(curr == NULL) return;
        
        curr->elem->print();
        preorder(curr->left);
        preorder(curr->right);
    }
    int height(Node*);
    int bf(Node* node) {
        if(node == NULL) {
            return 0;
        }
        else if(node->isLeaf()) {
            return 0;
        }
        return height(node->left) - height(node->right);
    }
    Node* min(Node* node) {
        Node* i = node;
        while(i && i->left) {
            i = i->left;
        }
        return i;
    }
    bool balance(Node*&);
    void LL(Node*&);
    void RR(Node*&);
    void LR(Node*&);
    void RL(Node*&);
    bool checkAllBalance(Node*);
    int greater(int left, int right) {
        return (left>right)? left:right;
    }
    
public:
    AVL() {root = NULL; count = 0;} // virtual node for root
    ~AVL() {
        if(root) delete root; // delete all tree base on DOMINO
    }
    void remove(Elem* e) {
        root = remove(root, e);
    }
    void print() {
        inorder(root);
		preorder(root);
    }
    int height() {
        return height(root);
    }
    void insert(Elem* e) { 
        insert(root, e);
        count++;
    }
    Elem* search(int);
    bool checkAllBalance();
    int size() {
        return count;
    }
};







#endif