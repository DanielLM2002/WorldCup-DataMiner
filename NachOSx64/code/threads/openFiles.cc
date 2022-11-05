#include "openFiles.h"
#define amount_of_files 128

OpenFiles::OpenFiles() {
    openFileCount = new int[amount_of_files];
    openFilesMap = new BitMap(amount_of_files);
    ThreadsInUse = 0;
    SetMemory();
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
    int fileMemory = 0;
    addThread();
    int result =0;
    if (this->ThreadsInUse == 0) {
        this ->openFilesMap -> Mark(fileMemory);
        this ->openFileCount[fileMemory] = 1;
        printf("There is no space for a new file. Please close a file first.");
    } else if (this->ThreadsInUse >= 1) {
        if (this ->openFilesMap->Test(fileHandle)) {
            fileMemory = this->openFilesMap->Find();
            openFileCount[fileMemory] = fileHandle;
            result = fileMemory;
        } else {
            printf("File is already open");
            result = 1;
        }
    } else {
        printf("ERROR, there are no threads to work with");
        result = -1;
    }
    return result;
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
    // std::cout << "OpenFiles:" << std::endl;
    // for(int i = 0; i < amount_of_files; i++) {
    //     std::cout << "Index" << this->openFileCount[i] << "\n";
    // }
    // std::cout << std::endl;
    printf("No se implemento\n");
}

void OpenFiles::SetMemory() {
    int index = 0;
    for(;index <= 3; ++index){
        this->openFilesMap->Mark(index);
        this->openFileCount[index] = index;
    }
}