#include "main.h"
Cache::Cache(SearchEngine* s,ReplacementPolicy* r):rp(r),s_engine(s) {}
Cache::~Cache(){
	delete rp;
	delete s_engine;
}
Data* Cache::read(int addr) {
    bool exist = false; // check address exist in cache
    int index = 0; // index of element containing this address.
    if( s_engine ->numElem == 0) return NULL;
    else{
        for (int i = 0; i < s_engine ->numElem; i++){
            if(s_engine->arr[i]->addr == addr){
                exist = true;
                index = i;
                rp->numCall[index]++;
                rp->pushStack(index);
                rp->deleteHeap(rp->heap, index);
                rp->insertHeap(rp->heap, index, rp->numCall[index]);
                break;
            }
        }
        if(exist) return s_engine->arr[index]->data;
        else return NULL;
    }
}
Elem* Cache::put(int addr, Data* cont) {
    Elem* result;
    int index;
    Elem* newElem = new Elem(addr, cont, true);
    if( s_engine->numElem >= 0 && s_engine->numElem < MAXSIZE){ //in case cache is not full
        s_engine->arr[s_engine->numElem] = newElem;
        rp->numCall[s_engine->numElem] = 0;
        rp->insertHeap(rp->heap, s_engine->numElem, rp->numCall[s_engine->numElem]);
        s_engine->numElem++;
        return NULL;
    }
    else if (s_engine->numElem == MAXSIZE){ //in case cache is full
        enum typeReplace{
            mfu,
            lfu,
            mfru,
            lfru
        };
        switch(rp->policy){
            case mfu:
                index = rp->heap[0]->index;
                result = s_engine->arr[index];
                s_engine->arr[index] = newElem;
                rp->numCall[index] = 0;
                rp->deleteHeap(rp->heap, index);
                rp->insertHeap(rp->heap, index, rp->numCall[index]);
                return result;
                break;
            case lfu:
                break;
            case mfru:
                break;
            case lfru:
                break;
            default:
                break;
        }
        
        
        // if(addr % 2 == 0){
        //     index = queuePrio();
        //     result = arr[index];
        //     arr[index] = newElem;
        //     p = MAXSIZE + 1;
        //     return result;
        // }
        // else{
        //     index = stackPrio();
        //     result = arr[index];
        //     arr[index] = newElem;
        //     p = MAXSIZE + 1;
        //     return result;
        // }
    }
    return NULL;
}
Elem* Cache::write(int addr, Data* cont) {
    return NULL;
}
void Cache::printRP() {
}
void Cache::printSE() {
}
void Cache::printLP() {
}
