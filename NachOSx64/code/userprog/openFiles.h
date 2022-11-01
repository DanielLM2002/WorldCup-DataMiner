#ifndef openFiles_h
#define openFiles_h
#include <iostream>
#include <string>

#include "filesys.h"
#include "bitmap.h"
#include "synch.h"

class OpenFiles {
    private:
        int* openFileCount; 
        BitMap *openFileMap;
        Lock* openFileLock;
        int current_threads;
    public:
        OpenFiles();
        ~OpenFiles();
        int Open(int file);
        int Close(int file);
        bool isOpen(int file);
        int getOpenCount(int file);
        void addThread();
        void removeThread();
        void Print();
};



#endif // openFiles_h