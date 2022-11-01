#ifndef openFiles_h
#define openFiles_h
#include <iostream>
#include <string>

#include "filesys.h"
#include "bitmap.h"
#include "synch.h"

class OpenFiles {
    private:
        int* openFileCount; // vector con los archivos del usuario que estan abiertos
        BitMap *openFileMap;// bitmap para controlar los archivos abiertos
        Lock* openFileLock;
        int current_threads;// cantidad de threads que estan usando el sistema de archivos
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