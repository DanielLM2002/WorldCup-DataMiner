#include "openFiles.h"
#define amount_of_files 128

OpenFiles::OpenFiles() {
    this->openFileCount = new int[amount_of_files];
    this->openFilesMap = new BitMap(amount_of_files);
    for(int i = 0; i < 3; ++i) {
        this->openFileCount[i] = i;
        this->openFilesMap->Mark(i);
    }
    this->ThreadsInUse = 0;
}

OpenFiles::~OpenFiles(){
    delete this->openFileCount;
    delete this->openFilesMap;
}

int OpenFiles::Open(int unixHandle) {
        addThread();
        int new_fd = this->openFilesMap->Find();
        this->openFileCount[new_fd] = unixHandle;
    return new_fd;
}

int OpenFiles::Close(int NachosHandle) {
        int was_sucessful = -1;
        if(isOpen(NachosHandle)) {
            removeThread();
            if(this->ThreadsInUse == 0) {
                bool allClear = false;
                for(int i = 0; i < amount_of_files && !allClear; ++i) {
                    if(this->openFilesMap->Test(i)) {
                        this->openFileCount[i] = -2;
                        this->openFilesMap->Clear(i);
                    }
                    if(this->openFilesMap->NumClear() == amount_of_files) {
                        allClear = true;
                    }
                }
            }
            was_sucessful = 1;
        }
    return was_sucessful;
}

bool OpenFiles::isOpen(int NachosHandle) {
    return this->openFilesMap->Test(NachosHandle);
}

int OpenFiles::getOpenCount(int NachosHandle) {
    int UnixHandle = -666;
    if(isOpen(NachosHandle)) {
        UnixHandle = this->openFileCount[NachosHandle];
    }
    return UnixHandle;
}

void OpenFiles::addThread() {
    ++this->ThreadsInUse;
}

void OpenFiles::removeThread() {
    if(this->ThreadsInUse > 0) {
        --this->ThreadsInUse;
    } else {
        std::cout << "\n\t ERROR: USAGE CAN'T BE NEGATIVE!!!\t\n" << std::endl;
        exit(2);
    }
}

void OpenFiles::Print() {
    std::cout << "\t[Index]\t[Unix_FD]\n";
    for(int i = 0; i < amount_of_files; ++i) {
        std::cout << "\ti\t" << this->openFileCount[i] << "\n";
    }
    std::cout << std::endl;
}

