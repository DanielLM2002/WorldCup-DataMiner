// exception.cc
//	Entry point into the Nachos kernel from user programs.
//	There are two kinds of things that can cause control to
//	transfer back to here from user code:
//
//	syscall -- The user code explicitly requests to call a procedure
//	in the Nachos kernel.  Right now, the only function we support is
//	"Halt".
//
//	exceptions -- The user code does something that the CPU can't handle.
//	For instance, accessing memory that doesn't exist, arithmetic errors,
//	etc.
//
//	Interrupts (which can also cause control to transfer from user
//	code into the Nachos kernel) are handled elsewhere.
//
// For now, this only handles the Halt() system call.
// Everything else core dumps.
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "system.h"
#include "syscall.h"
#include <netinet/in.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include "synch.h"

#define Char_Size_Of_Array 180

#define PARAM_SYS_CODE_REG 2
#define PARAM_1_REG 4
#define PARAM_2_REG 5
#define PARAM_3_REG 6
#define RETURN_REG 2

Lock syscall_lock ("syscall_lock");

void returnFromSystemCall()
{

   int pc, npc;

   pc = machine->ReadRegister(PCReg);
   npc = machine->ReadRegister(NextPCReg);
   machine->WriteRegister(PrevPCReg, pc);      // PrevPC <- PC
   machine->WriteRegister(PCReg, npc);         // PC <- NextPC
   machine->WriteRegister(NextPCReg, npc + 4); // NextPC <- NextPC + 4


} // returnFromSystemCall

/*
 *  System call interface: Halt()
 */
void NachOS_Halt()
{ // System call 0

   DEBUG('a', "Shutdown, initiated by user program.\n");
   interrupt->Halt();
}

/*
 *  System call interface: void Exit( int )
 */
void NachOS_Exit()
{ // System call 1
   int status = machine->ReadRegister(4);
   if(status == 0){
      currentThread->Finish();
   }else {
      perror("No se pudo salir bien, ERRORR!!");
   }
}

/*
 *  System call interface: SpaceId Exec( char * )
 */
void NachOS_Exec()
{ // System call 2
}

/*
 *  System call interface: int Join( SpaceId )
 */
void NachOS_Join()
{ // System call 3
}

/*
 *  System call interface: void Create( char * )
 */
void NachOS_Create()
{ // System call 4
}

/*
 *  System call interface: OpenFileId Open( char * )
 */
void NachOS_Open()
{ // System call 5
}

/*
 *  System call interface: OpenFileId Write( char *, int, OpenFileId )
 */
void NachOS_Write()
{ // System call 6
   int bufferPointer = machine->ReadRegister(4);
   int size = machine->ReadRegister(5);
   int socketId = machine->ReadRegister(6);
   int bytes_read = 0;
   char * char_buffer = new char[size];
   int counter = 0;
   int counter_aux = 0;
   char* aux;
   int container = 0;
   syscall_lock.Acquire();
   switch(socketId) {
      case 0:
         container = -1;
      break;

      case 1:
         while (counter < size) {
            machine->ReadMem(bufferPointer + counter, 1, &bytes_read);
            char_buffer[counter] = (char) bytes_read;
            counter++;
         }
         printf("%s",char_buffer);
         container = 1;
      break;

      case 2:
         container = -1;
      break;

      default:
         if (currentThread->fileTable->isOpen(socketId)) {
            int openCount = currentThread->fileTable->getOpenCount(socketId);
            int count = 0;
            while (count < size) {
               machine->ReadMem(bufferPointer + count, 1, &bytes_read);
               char_buffer[count] = (char) bytes_read;
               count++;
            }
            container = write(openCount, char_buffer, size);
         } else {
            container = -1;
         }
      break;
   }
   delete char_buffer;
   syscall_lock.Release();
   machine->WriteRegister(2, container);
}

/*
 *  System call interface: OpenFileId Read( char *, int, OpenFileId )
 */
void NachOS_Read() { // System call 7
   int bufferPointer = machine->ReadRegister(4);
   int size = machine->ReadRegister(5);
   int socketId = machine->ReadRegister(6);
   int bytes_read = 0;
   char * char_buffer = new char[size];
   int counter = 0;
   int counter_aux = 0;
   char* aux;
   int container = 0;
   syscall_lock.Acquire();
   switch(socketId) {
      case 0:
         container = -1;
      break;

      case 1:
         container = -1;
      break;

      case 2:
         while (machine->ReadMem(bufferPointer + counter, 1, &bytes_read) 
                && counter < size) {
            char_buffer[counter] = (char) bytes_read;
            counter++;
         }
         counter_aux = counter + 2;
         aux = new char[counter_aux];
         for (int i = 0; i < counter; i++) {
            aux[i] = char_buffer[i];
         }
         aux[counter_aux - 1] = 0;
         char_buffer[size] = 0;
         std::cin >> aux;
         for(int i =0; i < size; ++i){
            machine->WriteMem(bufferPointer + i, 1, aux[i]);
         }
         container = 1;
      break;

      default:
         if (currentThread->fileTable->isOpen(socketId)) {
            int openCount = currentThread->fileTable->getOpenCount(socketId);
            container = read(openCount, char_buffer, size);
            for(int i =0; i < size; ++i){
               machine->WriteMem(bufferPointer + i, 1, char_buffer[i]);
            }
         } else {
            container = -1;
         }
      break;
   }
   delete char_buffer;
   syscall_lock.Release();
   machine->WriteRegister(2, container);
}

/*
 *  System call interface: void Close( OpenFileId )
 */
void NachOS_Close() { // System call 8
   int socketId = machine->ReadRegister(4);
   int container = 0;
   syscall_lock.Acquire();
   if (currentThread->fileTable->isOpen(socketId)) {
      int openCount = currentThread->fileTable->getOpenCount(socketId);
      if (openCount == 1) {
         container = close(socketId);
         currentThread->fileTable->Close(socketId);
      } else {
         currentThread->fileTable->removeThread();
         container = 1;
      }
   } else {
      container = -1;
   }
   syscall_lock.Release();
   machine->WriteRegister(2, container);
}

/*
 *  System call interface: void Fork( void (*func)() )
 */
void NachOS_Fork()
{ // System call 9
}

/*
 *  System call interface: void Yield()
 */
void NachOS_Yield()
{ // System call 10
}

/*
 *  System call interface: Sem_t SemCreate( int )
 */
void NachOS_SemCreate()
{ // System call 11
}

/*
 *  System call interface: int SemDestroy( Sem_t )
 */
void NachOS_SemDestroy()
{ // System call 12
}

/*
 *  System call interface: int SemSignal( Sem_t )
 */
void NachOS_SemSignal()
{ // System call 13
}

/*
 *  System call interface: int SemWait( Sem_t )
 */
void NachOS_SemWait()
{ // System call 14
}

/*
 *  System call interface: Lock_t LockCreate( int )
 */
void NachOS_LockCreate()
{ // System call 15
}

/*
 *  System call interface: int LockDestroy( Lock_t )
 */
void NachOS_LockDestroy()
{ // System call 16
}

/*
 *  System call interface: int LockAcquire( Lock_t )
 */
void NachOS_LockAcquire()
{ // System call 17
}

/*
 *  System call interface: int LockRelease( Lock_t )
 */
void NachOS_LockRelease()
{ // System call 18
}

/*
 *  System call interface: Cond_t LockCreate( int )
 */
void NachOS_CondCreate()
{ // System call 19
}

/*
 *  System call interface: int CondDestroy( Cond_t )
 */
void NachOS_CondDestroy()
{ // System call 20
}

/*
 *  System call interface: int CondSignal( Cond_t )
 */
void NachOS_CondSignal()
{ // System call 21
}

/*
 *  System call interface: int CondWait( Cond_t )
 */
void NachOS_CondWait()
{ // System call 22
}

/*
 *  System call interface: int CondBroadcast( Cond_t )
 */
void NachOS_CondBroadcast()
{ // System call 23
}

/*
 *  System call interface: Socket_t Socket( int, int )
 */
void NachOS_Socket(){ // System call 30
   int domain = machine->ReadRegister(4);
   if (domain == AF_INET_NachOS) {
      domain = AF_INET;
   } else if (domain == AF_INET6_NachOS) {
      domain = AF_INET6;
   } else {
      domain = -1;
      perror("No se pudo crear el socket");
      exit(2);
   }
   int type = machine->ReadRegister(5);
   if (type == SOCK_STREAM_NachOS) {
      type = SOCK_STREAM;
   } else if (type == SOCK_DGRAM_NachOS) {
      type = SOCK_DGRAM;
   } else {
      type = -1;
      perror("No se pudo crear el socket");
      exit(2);
   }
   int id = socket(domain, type, 0);
   int new_id = 0;
   if (id < 0) {
      perror("No se pudo crear el socket");
      exit(2);
   } else {
      new_id = currentThread->fileTable->Open(id);
   }
   machine->WriteRegister(2, new_id);
}


/*
 *  System call interface: Socket_t Connect( char *, int )
 */
void NachOS_Connect() {
   int nachos_handle = machine->ReadRegister(4);
   int bufferPointer = machine->ReadRegister(5);
   int port = machine->ReadRegister(6);
   int bytes_read = 0;
   char char_buffer[Char_Size_Of_Array]; //hostip
   int container = 0;
   if (currentThread->fileTable->isOpen(nachos_handle)) {
      int nachos_id = currentThread->fileTable->getOpenCount(nachos_handle);
      int count = 0;
      while( machine->ReadMem(bufferPointer + count, 1, &bytes_read) && bytes_read != 0 ) {
         machine->ReadMem(bufferPointer + count, 1, &bytes_read);
         char_buffer[count] = (char) bytes_read;
         ++count;
      }
      char_buffer[count] = 0;
      struct sockaddr_in server;
      server.sin_family = AF_INET;
      server.sin_port = htons(port);
      server.sin_addr.s_addr = inet_addr(char_buffer);
      bzero(&(server.sin_zero), 8);
      container = connect(nachos_id, (struct sockaddr *) &server, sizeof(struct sockaddr));
      if(container == -1) {
         perror("No se pudo conectar");
         exit(2);
      }
   }
   machine->WriteRegister(2, container);
}

/*
 *  System call interface: int Bind( Socket_t, int )
 */
void NachOS_Bind() { // System call 32
   // int nachos_handle = machine->ReadRegister(4);
   // int bufferPointer = machine->ReadRegister(5);
   // int size = machine->ReadRegister( );
   // int container = 0;
   // if(currentThread->fileTable->isOpen(nachos_handle)) {
   //    struct sockaddr_in server;
   //    memset((char*) &server, 0, sizeof(server));
   //    server.sin_family = AF_INET;
   //    server.sin_port = htons(bufferPointer);
   //    server.sin_addr.s_addr = htonl(INADDR_ANY);
   //    int unix_handle = currentThread->fileTable->getOpenCount(nachos_handle);
   //    container = bind(unix_handle, (struct sockaddr *) &server, sizeof(server));
   //    if (container == -1) {
   //       perror("No se pudo hacer bind");
   //       exit(2);
   //    }
   // }
   // machine->WriteRegister(2, container);
}

/*
 *  System call interface: int Listen( Socket_t, int )
 */
void NachOS_Listen()
{ // System call 33
   int id = machine->ReadRegister(4);
   int backlog = machine->ReadRegister(5);
   int return_value = listen(id, backlog);
   if (return_value < 0)
   {
      printf("Socket::Listen");
      exit(2);
   }
   machine->WriteRegister(2, return_value);
}

/*
 *  System call interface: int Accept( Socket_t )
 */
void NachOS_Accept()
{ // System call 34
   int id = machine->ReadRegister(4);
   struct sockaddr_in client;
   memset((char *)&client, 0, sizeof(client));
   socklen_t client_length = sizeof(client);
   int return_value = accept(id, (sockaddr *)&client, &client_length);
   if (return_value < 0)
   {
      printf("Socket::Accept");
      exit(2);
   }
   machine->WriteRegister(2, return_value);
}

/*
 *  System call interface: int Shutdown( Socket_t, int )
 */
void NachOS_Shutdown()
{ // System call 25
   int id = machine->ReadRegister(4);
   int how = machine->ReadRegister(5);
   int return_value = shutdown(id, how);
   if (return_value < 0)
   {
      printf("Socket::Shutdown");
      exit(2);
   }
   machine->WriteRegister(2, return_value);
}

//----------------------------------------------------------------------
// ExceptionHandler
// 	Entry point into the Nachos kernel.  Called when a user program
//	is executing, and either does a syscall, or generates an addressing
//	or arithmetic exception.
//
// 	For system calls, the following is the calling convention:
//
// 	system call code -- r2
//		arg1 -- r4
//		arg2 -- r5
//		arg3 -- r6
//		arg4 -- r7
//
//	The result of the system call, if any, must be put back into r2.
//
// And don't forget to increment the pc before returning. (Or else you'll
// loop making the same system call forever!
//
//	"which" is the kind of exception.  The list of possible exceptions
//	are in machine.h.
//----------------------------------------------------------------------

void ExceptionHandler(ExceptionType which)
{
   int type = machine->ReadRegister(2);

   switch (which)
   {

   case SyscallException:
      switch (type)
      {
      case SC_Halt: // System call # 0
         NachOS_Halt();
         break;
      case SC_Exit: // System call # 1
         NachOS_Exit();
         break;
      case SC_Exec: // System call # 2
         NachOS_Exec();
         break;
      case SC_Join: // System call # 3
         NachOS_Join();
         break;

      case SC_Create: // System call # 4
         NachOS_Create();
         break;
      case SC_Open: // System call # 5
         NachOS_Open();
         break;
      case SC_Read: // System call # 6
         NachOS_Read();
         break;
      case SC_Write: // System call # 7
         NachOS_Write();
         break;
      case SC_Close: // System call # 8
         NachOS_Close();
         break;

      case SC_Fork: // System call # 9
         NachOS_Fork();
         break;
      case SC_Yield: // System call # 10
         NachOS_Yield();
         break;

      case SC_SemCreate: // System call # 11
         NachOS_SemCreate();
         break;
      case SC_SemDestroy: // System call # 12
         NachOS_SemDestroy();
         break;
      case SC_SemSignal: // System call # 13
         NachOS_SemSignal();
         break;
      case SC_SemWait: // System call # 14
         NachOS_SemWait();
         break;

      case SC_LckCreate: // System call # 15
         NachOS_LockCreate();
         break;
      case SC_LckDestroy: // System call # 16
         NachOS_LockDestroy();
         break;
      case SC_LckAcquire: // System call # 17
         NachOS_LockAcquire();
         break;
      case SC_LckRelease: // System call # 18
         NachOS_LockRelease();
         break;

      case SC_CondCreate: // System call # 19
         NachOS_CondCreate();
         break;
      case SC_CondDestroy: // System call # 20
         NachOS_CondDestroy();
         break;
      case SC_CondSignal: // System call # 21
         NachOS_CondSignal();
         break;
      case SC_CondWait: // System call # 22
         NachOS_CondWait();
         break;
      case SC_CondBroadcast: // System call # 23
         NachOS_CondBroadcast();
         break;

      case SC_Socket: // System call # 30
         NachOS_Socket();
         break;
      case SC_Connect: // System call # 31
         NachOS_Connect();
         break;
      case SC_Bind: // System call # 32
         NachOS_Bind();
         break;
      case SC_Listen: // System call # 33
         NachOS_Listen();
         break;
      case SC_Accept: // System call # 32
         NachOS_Accept();
         break;
      case SC_Shutdown: // System call # 33
         NachOS_Shutdown();
         break;

      default:
         printf("Unexpected syscall exception %d\n", type);
         ASSERT(false);
         break;
      }
      returnFromSystemCall();
      break;

   case PageFaultException:
   {
      break;
   }

   case ReadOnlyException:
      printf("Read Only exception (%d)\n", which);
      ASSERT(false);
      break;

   case BusErrorException:
      printf("Bus error exception (%d)\n", which);
      ASSERT(false);
      break;

   case AddressErrorException:
      printf("Address error exception (%d)\n", which);
      ASSERT(false);
      break;

   case OverflowException:
      printf("Overflow exception (%d)\n", which);
      ASSERT(false);
      break;

   case IllegalInstrException:
      printf("Ilegal instruction exception (%d)\n", which);
      ASSERT(false);
      break;

   default:
      printf("Unexpected exception %d\n", which);
      ASSERT(false);
      break;
   }
}