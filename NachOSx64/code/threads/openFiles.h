#ifndef openFiles_h
#define openFiles_h

#include <iostream>

#include "bitmap.h"

class OpenFiles {
    private:
        int* openFileCount; // Vector with user opened files
        BitMap* openFilesMap; // A bitmap to control our vector
        int ThreadsInUse; // How many threads are using the table
        //Lock* tab_lock;
    public:
        OpenFiles();
        ~OpenFiles();
        int Open(int); // Register the file handle 
        int Close(int); // Unregister the file handle
        bool isOpen(int); 
        int getOpenCount(int);
        void addThread(); // If a usar thread is using this table, add it
        void removeThread(); // If a user thread is using this table, delete it
        void Print(); // Print contents
};
#endif 
