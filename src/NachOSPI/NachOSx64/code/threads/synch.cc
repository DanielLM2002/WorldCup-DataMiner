// synch.cc 
//	Routines for synchronizing threads.  Three kinds of
//	synchronization routines are defined here: semaphores, locks 
//   	and condition variables (the implementation of the last two
//	are left to the reader).
//
// Any implementation of a synchronization routine needs some
// primitive atomic operation.  We assume Nachos is running on
// a uniprocessor, and thus atomicity can be provided by
// turning off interrupts.  While interrupts are disabled, no
// context switch can occur, and thus the current thread is guaranteed
// to hold the CPU throughout, until interrupts are reenabled.
//
// Because some of these routines might be called with interrupts
// already disabled (Semaphore::V for one), instead of turning
// on interrupts at the end of the atomic operation, we always simply
// re-set the interrupt state back to its original value (whether
// that be disabled or enabled).
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "synch.h"
#include "system.h"

//----------------------------------------------------------------------
// Semaphore::Semaphore
// 	Initialize a semaphore, so that it can be used for synchronization.
//
//	"debugName" is an arbitrary name, useful for debugging.
//	"initialValue" is the initial value of the semaphore.
//----------------------------------------------------------------------

Semaphore::Semaphore(const char* debugName, int initialValue)
{
    name = (char *)debugName;
    value = initialValue;
    queue = new List<Thread*>;
}

//----------------------------------------------------------------------
// Semaphore::Semaphore
// 	De-allocate semaphore, when no longer needed.  Assume no one
//	is still waiting on the semaphore!
//----------------------------------------------------------------------

Semaphore::~Semaphore()
{
    delete queue;
}

//----------------------------------------------------------------------
// Semaphore::P
// 	Wait until semaphore value > 0, then decrement.  Checking the
//	value and decrementing must be done atomically, so we
//	need to disable interrupts before checking the value.
//
//	Note that Thread::Sleep assumes that interrupts are disabled
//	when it is called.
//----------------------------------------------------------------------

void
Semaphore::P()
{
    IntStatus oldLevel = interrupt->SetLevel(IntOff);	// disable interrupts
    
    while (value == 0) { 			// semaphore not available
	queue->Append(currentThread);		// so go to sleep
	currentThread->Sleep();
    } 
    value--; 					// semaphore available, 
						// consume its value
    
    interrupt->SetLevel(oldLevel);		// re-enable interrupts
}

//----------------------------------------------------------------------
// Semaphore::V
// 	Increment semaphore value, waking up a waiter if necessary.
//	As with P(), this operation must be atomic, so we need to disable
//	interrupts.  Scheduler::ReadyToRun() assumes that threads
//	are disabled when it is called.
//----------------------------------------------------------------------

void
Semaphore::V()
{
    Thread *thread;
    IntStatus oldLevel = interrupt->SetLevel(IntOff);

    thread = queue->Remove();
    if (thread != NULL)	   // make thread ready, consuming the V immediately
	scheduler->ReadyToRun(thread);
    value++;
    interrupt->SetLevel(oldLevel);
}

#ifdef USER_PROGRAM
//----------------------------------------------------------------------
// Semaphore::Destroy
// 	Destroy the semaphore, freeing the waiting threads
//	This is used to destroy a user semaphore
//----------------------------------------------------------------------

void
Semaphore::Destroy()
{
    Thread *thread;
    IntStatus oldLevel = interrupt->SetLevel(IntOff);

    while ( (thread = queue->Remove() ) != NULL )	// make thread ready
	scheduler->ReadyToRun(thread);

    interrupt->SetLevel(oldLevel);
}

#endif


// Dummy functions -- so we can compile our later assignments 
// Note -- without a correct implementation of Condition::Wait(), 
// the test case in the network assignment won't work!
Lock::Lock(const char* debugName) {
    this -> name = (char *)debugName;
    sem_lock = new Semaphore(debugName, 1);
    lockOwner = NULL;
}


Lock::~Lock() {
    delete sem_lock;
}


void Lock::Acquire() {
    IntStatus oldLevel = interrupt->SetLevel(IntOff);
    DEBUG('t', "Lock %s is acquired by thread %s", currentThread->getName());
    sem_lock -> P();
    lockOwner = currentThread;


}


void Lock::Release() {
    IntStatus oldLevel = interrupt->SetLevel(IntOff);
    DEBUG('t', "Lock %s is released by thread %s", currentThread->getName());
    if(isHeldByCurrentThread()) { 
        sem_lock -> V();
        lockOwner = NULL;
    }
    (void) interrupt -> SetLevel(oldLevel);
}


bool Lock::isHeldByCurrentThread() {
   return (lockOwner == currentThread);
}

Thread* Lock::getOwner(){
    return lockOwner;
}


Condition::Condition(const char* debugName) {
    name = (char *)debugName;
    queue = new List<Thread*>;

}


Condition::~Condition() {
    delete queue;
}


void Condition::Wait( Lock * conditionLock ) {
    IntStatus oldLevel = interrupt->SetLevel(IntOff);
    DEBUG('t', "Condition %s is waiting by thread %s", currentThread->getName(), name);
    Thread* lockOwner = conditionLock -> getOwner();
    if (lockOwner != NULL) {
        ASSERT(lockOwner == currentThread);
        queue -> Append(currentThread);
        conditionLock -> Release();
        DEBUG('t', "Condition %s is BLocked by the condition %s", currentThread->getName(), name);
        currentThread -> Sleep();
        DEBUG('t', "Condition %s is alive and about to get lock %s", currentThread->getName(), name);
        conditionLock -> Acquire();
    }
}


void Condition::Signal( Lock * conditionLock ) {
    DEBUG('t', "Condition %s is being signalled and blocked on condition %s", currentThread->getName(), name);
    Thread* thread;
    IntStatus oldLevel = interrupt->SetLevel(IntOff);
    if (queue->IsEmpty()==false) {
        thread = (Thread*) queue->Remove();
        DEBUG('t', " the thread woke up \"%s\"\n",thread->getName());
        if (thread != NULL) scheduler->ReadyToRun(thread);
    }
    (void) interrupt->SetLevel(oldLevel);
}


void Condition::Broadcast( Lock * conditionLock ) {
    Thread* thread;
    IntStatus oldLevel = interrupt->SetLevel(IntOff);
    while(queue->IsEmpty() == false) {
        thread = (Thread*) queue->Remove();
        if (thread != NULL) scheduler->ReadyToRun(thread);
    }
    (void) interrupt->SetLevel(oldLevel);
}


// Mutex class
Mutex::Mutex( const char * debugName ) {
    name = (char *)debugName;
    sem_lock = new Semaphore(debugName, 1);
    lockOwner = NULL;
}

Mutex::~Mutex() {
    delete sem_lock;
}

void Mutex::Lock() {
    IntStatus oldLevel = interrupt->SetLevel(IntOff);
    DEBUG('t', "Lock %s is acquired by thread %s", currentThread->getName());
    sem_lock -> P();
    lockOwner = currentThread;
}

void Mutex::Unlock() {
    IntStatus oldLevel = interrupt->SetLevel(IntOff);
    DEBUG('t', "Lock %s is released by thread %s", currentThread->getName());
    sem_lock -> V();
    lockOwner = NULL;
    (void) interrupt -> SetLevel(oldLevel);
}


// Barrier class
Barrier::Barrier( const char * debugName, int count ) {
    name = (char *)debugName;
    sem_lock = new Semaphore(debugName, 1);
    lockOwner = NULL;
    barrierCount = count;
    barrierCountCurrent = 0;

}

Barrier::~Barrier() {
    delete sem_lock;
}

void Barrier::Wait() {
    IntStatus oldLevel = interrupt->SetLevel(IntOff);
    DEBUG('t', "Lock %s is acquired by thread %s", currentThread->getName());
    sem_lock -> P();
    lockOwner = currentThread;
    barrierCountCurrent++;
    if (barrierCountCurrent == barrierCount) {
        sem_lock -> V();
        lockOwner = NULL;
        barrierCountCurrent = 0;
    }
    else {
        sem_lock -> V();
        lockOwner = NULL;
        currentThread -> Sleep();
    }
    (void) interrupt -> SetLevel(oldLevel);
}

