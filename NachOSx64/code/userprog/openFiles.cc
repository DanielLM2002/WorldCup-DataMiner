#include "openFiles.h"

#define amountOfFiles 255

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
    delete this->current_threads;
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
                for (int i = 0; i < amountOfFiles; i++) {
                    if (this->openFileMap->Test(i)) {
                        this->openFileMap[i] = -2;
                        this->openFileMap->Clear(i);
                    }
                    if(this->openFileMap->NumClear() == amountOfFiles) {
                       clearFiles = true;
                    }
                }
            }
            close_file = 1;
        }
    this->openFileLock->Release();
    return close_file;
}

bool OpenFiles::isOpen(int handler) {
    return this->openFileMap->Test(handler);
}

int OpenFiles::getOpenCount(int handler) {
    int osHandler = -666;
    if(isOpen(handler)) {
        osHandler = this->openFileCount[handler];
    }
}

void OpenFiles::addThread() {
    this->current_threads++;
}

void OpenFiles::removeThread() {
    if(this->current_threads > 0) {
        this->current_threads--;
    } else {
        std::cout << "The threads cant be negative" << std::endl;
        exit(2);
    }
}

void OpenFiles::Print() {
    std::cout << "OpenFiles: " << std::endl;
    for (int i = 0; i < amountOfFiles; i++) {
        if (this->openFileMap->Test(i)) {
            std::cout << "File: " << i << " is open" << std::endl;
        }
    }
}
