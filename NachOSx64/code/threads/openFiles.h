#ifndef openFiles_h
#define openFiles_h

#include <iostream>

// #include "../userprog/bitmap.h"
#include "bitmap.h"

class OpenFiles {
    private:
        int* openFileCount;
        BitMap* openFilesMap;
        int ThreadsInUse;
    public:
        OpenFiles();
        ~OpenFiles();
        int Open(int); 
        int Close(int);
        bool isOpen(int); 
        int getOpenCount(int);
        void addThread();
        void removeThread();
        void Print();
        void SetMemory();
};
#endif