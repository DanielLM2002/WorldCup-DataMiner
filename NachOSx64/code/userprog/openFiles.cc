#include "openFiles.h"

#define amountOfFiles 128
OpenFiles::OpenFiles() {
    this->openFileCount = new int[amountOfFiles];
    this->openFileMap = new BitMap(amountOfFiles);
    openFileLock = new Lock("openFileLock");
    for (int i = 0; i < 3; i++) {
        this->openFileCount[i] = i;
        this->openFileMap->Mark(i);
    }
    this->current_threads = 0;
}

OpenFiles::~OpenFiles() {
    delete this->openFileCount;
    delete this->openFileMap;
    delete this->openFileLock;
}

int OpenFiles::Open(int getOpenCount) {
    this->openFileLock->Acquire();
        addThread();
        int newID = this->openFileMap->Find();
        this->openFileCount[newID] = getOpenCount;
    this->openFileLock->Release();
    return newID;
}

int OpenFiles::Close(int handler) {
    this->openFileLock->Acquire();
        int close_file =  -1;
        if(isOpen(handler)) {
            removeThread();
            if(this->current_threads == 0) {
                bool clearFiles = false;
                
            }
        }
}