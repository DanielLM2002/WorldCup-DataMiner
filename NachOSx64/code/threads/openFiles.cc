#include "openFiles.h"
#define amount_of_files 128

OpenFiles::OpenFiles() {
    openFileCount = new int[amount_of_files];
    openFilesMap = new BitMap(amount_of_files);
    ThreadsInUse = 0;
}

OpenFiles::~OpenFiles() {
    delete openFileCount;
    delete openFilesMap;
}

void OpenFiles::addThread() {
    this->ThreadsInUse++;
}

void OpenFiles::removeThread() {
    this->ThreadsInUse--;
}

int OpenFiles::Open(int fileHandle) {
    if (this->ThreadsInUse == 0) {
        return -1;
    }
    if (this->openFilesMap->Test(fileHandle)) {
        this->openFileCount[fileHandle]++;
        return 0;
    } else {
        this->openFilesMap->Mark(fileHandle);
        this->openFileCount[fileHandle] = 1;
        return 0;
    }
}

int OpenFiles::Close(int fileHandle) {
    if (this->ThreadsInUse == 0) {
        return -1;
    }
    if (this->openFilesMap->Test(fileHandle)) {
        this->openFileCount[fileHandle]--;
        if (this->openFileCount[fileHandle] == 0) {
            this->openFilesMap->Clear(fileHandle);
        }
        return 0;
    } else {
        return -1;
    }
}

bool OpenFiles::isOpen(int fileHandle) {
    return this->openFilesMap->Test(fileHandle);
}

int OpenFiles::getOpenCount(int fileHandle) {
    int unixHandle = fileHandle;
    if (isOpen(fileHandle)) 
        unixHandle = this->openFileCount[fileHandle];
    return unixHandle;
}

void OpenFiles::Print() {
    std::cout << "OpenFiles:" << std::endl;
    for(int i = 0; i < amount_of_files; i++) {
        std::cout << "Index" << this->openFileCount[i] << "\n";
    }
    std::cout << std::endl;
}