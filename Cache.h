#ifndef CACHE_H
#define CACHE_H

#include "main.h"
class SearchEngine {
    //TODO
public:
    Elem** arr = new Elem*[MAXSIZE];
    int numElem;
public:
    class Node; // forward declare
    Node* root;
public:
    Node* insert(Elem* element, int index, Node*& root){
    if(root == NULL){
        root = new Node(element,index, NULL, NULL);
        // cout << bst->addr;
    }
    else if( element->addr < root->element->addr){
        root->left = insert(element, index, root->left);
    }
    else if(element->addr > root->element->addr){
        root->right = insert(element, index, root->right);
    }
    return root; 
    }

    void delNode(Node*& root, Elem* element){
        if(root == NULL) return;
        if(element->addr < root->element->addr) delNode(root->left, element);
        else if(element->addr > root->element->addr)delNode(root->right, element);
        else{
            if(root->left == NULL){
                Node* temp = root;
                root = root->right;
                delete temp; // Note --- can check lai rac bo nho
            }
            else if(root->right == NULL){
                Node* temp = root;
                root = root->left;
                delete temp;
            }
            else{
                Node* temp = root->right;
                while(temp->left != NULL) temp = temp->left;
                root->element = temp->element;
                delNode(root->right, temp->element);
            }
        }
    }
    
    Node* makeEmpty(Node*& root){
        if(root == NULL) return NULL;
        else{
            makeEmpty(root->left);
            makeEmpty(root->right);
            delete root;
        }
        return NULL;
    }
    void printInOrder(Node*& root){
        if(root == NULL){
            return;
        }
        // cout << "Print BST in inorder:/n";
        printInOrder(root->left);
        cout << root->element->addr << " " << root->element->data->getValue() << " " << (root->element->sync?"true":"false") << endl;
        printInOrder(root->right);
    }
    void printPreOrder(Node*& root){
        if(root == NULL){
            return;
        } 
        cout << root->element->addr << " " << root->element->data->getValue() << " " << (root->element->sync?"true":"false") << endl;
        printPreOrder(root->left);
        printPreOrder(root->right);
    }
    void PrintBST(){
        cout << "Print BST in inorder:/n";
        printInOrder(root);
        cout << "Print BST in preorder:/n";
        printPreOrder(root);
    }
class Node{
    public:
        Elem* element;
        int index; // index cua element trong arr
        Node* left;
        Node* right;
    public:
        Node(){
            element = NULL;
            index = 0;
            left = NULL;
            right = NULL;
        }
        Node(Elem* element, int index, Node* left, Node* right){
            this->element = element;
            this->index = index;
            this->left = left;
            this->right = right;
        }
        ~Node(){};
    };    
    virtual void setRoot(){};     
    SearchEngine(){
        numElem = 0;
        for(int i = 0; i < MAXSIZE; i++){
            arr[i] = NULL;
        }
    }
    ~SearchEngine(){
        root = makeEmpty(root);
        if(numElem <= MAXSIZE){
            for(int i = 0; i < numElem; i++) delete arr[i];
        }
        else{
            for(int i = 0; i < MAXSIZE; i++) delete arr[i];
        }
        delete[] arr;
    }
};

class ReplacementPolicy {
// property
public:
    //check cs thay the la loai nao
    enum typeReplace{
        mfu,
        lfu,
        mfru,
        lfru
    };
    typeReplace policy; // chính sách thay thế cache
    int* numCall = new int[MAXSIZE]; // dem so lan dc goi cua moi ptu
    int* stack = new int[MAXSIZE]; // stack ve index tgian su dung gan day
    class Node; // forward declare    
    Node** heap = new Node*[MAXSIZE];
    int curNumOfHeap;
// methods
    // function to push in stack
    bool isStackEmpty(){
        bool check = true;
        for(int i = 0; i < MAXSIZE; i++){
            if (stack[i] != -1) check = false;
            break; 
        }
        return check;
    }
    int numElemStack(){
        int count = 0;
        for(int i = 0; i < MAXSIZE; i++){
            if(stack[i] != -1) count++;
        }
        return count;
    }
    void swapStack(){
        for(int i = 0; i < MAXSIZE - 1; i++){
            stack[i] = stack[i+1];
        }
    }
    void pushStack(int index){
        if(isStackEmpty()) stack[0] = index;
        else{
            if(numElemStack() < MAXSIZE) stack[numElemStack()] = index;
            else{
                swapStack();
                stack[MAXSIZE-1] = index;
            }
        }
    }
    // heap
    void virtual reheapUp(Node**& heap, int index);
    void virtual reheapDown(Node**& heap, int index);
    
    void insertHeap(Node**& heap, int index, int count){
        if(curNumOfHeap >= MAXSIZE) return;
        else{
            Node* newNode = new Node(index, count);
            heap[curNumOfHeap] = newNode;
            curNumOfHeap++;
            reheapUp(heap, curNumOfHeap-1);
        }
    }

    void deleteHeap(Node**& heap, int index){
        int indexDel;
        for(int i = 0 ; i < curNumOfHeap; i++){
            if(heap[i]->index == index){
                indexDel = i;
                break;
            }
        }
        Node* temp = heap[indexDel];
        heap[indexDel] = heap[curNumOfHeap - 1];
        delete temp;
        heap[curNumOfHeap - 1] = NULL;
        curNumOfHeap--;
        reheapDown(heap, index);
    }
    //
    void virtual setTypeReplace();

public:
    class Node{
    public:
        int index;
        int counter;// so lan goi o index
    public:
        Node(){
            index = 0;
            counter = 0;
        }
        Node(int index, int counter){
            this->index = index;
            this->counter = counter;
        }
        ~Node();
    };
    ReplacementPolicy(){
        for(int i = 0; i < MAXSIZE; i++){
            numCall[i] = 0;
            stack[i] = -1;
            heap[i] = NULL;
        }
        curNumOfHeap = 0; 
    };
    ~ReplacementPolicy(){
        int i = 0;
        while(i < MAXSIZE){
            if(heap[i] != NULL) delete heap[i];
            i++;
        }
        delete[] heap;
        delete[] numCall;
    }

};


class MFU : public ReplacementPolicy {
    //TODO
public:
    void setTypeReplace(){
        policy = mfu;
    }
public:
    void swap(Node**& maxHeap, int child, int dad) {
        Node* temp = maxHeap[child];
        maxHeap[child] = maxHeap[dad];
        maxHeap[dad] = temp;
    }

    void reheapUp(Node**& maxheap, int index)
    {   // maxheap
        if (index > curNumOfHeap - 1) return;
        if (index > 0) {
            int parent = (index-1)/2;
            if (maxheap[index]->counter > maxheap[parent]->counter) {
                swap(maxheap, index, parent);
                reheapUp(maxheap, parent);
            }
        }
    }

    void reheapDown(Node**& maxheap, int index)
    {
        int leftChild = index*2 + 1;
        int rightChild = index*2 + 2;
        int maxChild;
        if (leftChild <= curNumOfHeap - 1) {
            if (rightChild <= curNumOfHeap - 1 && maxheap[rightChild]->counter >= maxheap[leftChild]->counter)
                maxChild = rightChild;
            else maxChild = leftChild;
            if (maxheap[maxChild]->counter > maxheap[index]->counter) {
                swap(maxheap, maxChild, index);
                reheapDown(maxheap, maxChild);
            }
        }
    }
public:
    MFU();
    ~MFU();
};

class LFU : public ReplacementPolicy {
    //TODO
public:
    void setTypeReplace(){
        policy = lfu;
    }
    void swap(Node**& minHeap, int child, int dad) {
        Node* temp = minHeap[child];
        minHeap[child] = minHeap[dad];
        minHeap[dad] = temp;
    }

    void reheapUp(Node**& minHeap, int index)
    {   // minHeap
        if (index > curNumOfHeap - 1) return;
        if (index > 0) {
            int parent = (index-1)/2;
            if (minHeap[index]->counter < minHeap[parent]->counter) {
                swap(minHeap, index, parent);
                reheapUp(minHeap, parent);
            }
        }
    }

    void reheapDown(Node**& minHeap, int index)
    {
        int leftChild = index*2 + 1;
        int rightChild = index*2 + 2;
        int minChild;
        if (rightChild <= curNumOfHeap - 1) {
            if (minHeap[leftChild]->counter <= minHeap[rightChild]->counter)
                minChild = leftChild;
            else minChild = rightChild;
            if (minHeap[minChild]->counter < minHeap[index]->counter) {
                swap(minHeap, minChild, index);
                reheapDown(minHeap, minChild);
            }
        }
    }

public:
    LFU();
    ~LFU();
};
class MFRU: public ReplacementPolicy {
    //TODO
public:
    void setTypeReplace(){
        policy = mfru;
    }
};

class LFRU: public ReplacementPolicy {
    //TODO
public:
    void setTypeReplace(){
        policy = lfru;
    }
};

class BST : public SearchEngine {
public:
    void setRoot(){
        root = NULL;
    }
};
#endif