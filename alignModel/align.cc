/*
  alignment.cc : 
  An excersize and test in byte packed buffer conversion to 
  and from a native boundry using named types, namespaces, a table and a
  type conversion class.
*/

//posix
#define POSIX_SOURCE 1		// we're posix complient

//standard headers
#include <stdio.h>
#include <assert.h>
#include <string.h>

//local headers
#include "mkalign.h"		// structure conversion support

//local prototyps
int doWork(void *Lmystruct, int buffsize, int db, int function);
int pack(char *buffer, int buffsize, int db, int function);
int unpack(char *buffer, int buffsize, int db, int function);

int main()
{
  ////test instantiation
  alignN::mystruct *aN = new alignN::mystruct; // dynamic Natural struct
  align2::mystruct *a2 = new align2::mystruct; // dynamic 2byte aligned struct

  //assert pounters if not valid
  assert(aN);
  assert(a2);

  ////test usage in byte conversion

  alignN::mystruct Lmystruct;

  Lmystruct.c1 = 'x';		// char
  Lmystruct.li = 0xffff;	// long
  Lmystruct.si = 0xff;		// short
  Lmystruct.c2 = 'x';		// char
  
  // embeded structure
  Lmystruct.as.si = 0xff;	// short

  Lmystruct.as.c[0] = 'x';	// char (2byte)
  Lmystruct.as.c[1] = 'x';

  Lmystruct.as.li = 0xffff;	// long
  Lmystruct.as.psz = "x12345x";	// char *

  //also needs pointer to function

  int error = 0;
  error = doWork( (void *)&Lmystruct, sizeof(Lmystruct), 0, 0);

  alignN::mystruct x[5][2];
  
  x[1][1].c1 = 'x';

  a2->as.si = Lmystruct.as.si;
  memcpy(&a2->as.c, &Lmystruct.as.c, sizeof(a2->as.c));
  
  //delete pointers
  delete aN;
  delete a2;

  printf("use a debugger to step through process (ie. dbx alignModel)\n");
  return error;
  }


int doWork(void *pmystruct, int buffSize, int db, int function)
  {
    // function emulates a packet compression with send and receive.

    //mystruct is part of a bigger peice - emulate that
    //copy *pmystruct
    char buffer[1024];
    memcpy(buffer, pmystruct, sizeof(alignN::mystruct));

    int error = 0;
    
    ////** buffer is a naturally aligned object

    //pack buffer, realign and compress packet
    if( (error = pack( (char *)buffer, sizeof(buffer), db, function)) )
      return error;

    ////** buffer is a 2 byte aligned object

    //Xmit packet
    //...............

    // emulate work at server
    align2::mystruct a2;
    memcpy(&a2, buffer, sizeof(align2::mystruct));

    a2.c1 = 'y';		// char
    
    a2.li = 0x0001;		// long
    a2.si = 0x01;		// short
    a2.c2 = 'y';		// char
    
    // embeded structure
    a2.as.si = 0x01;	// short
    
    a2.as.c[0] = 'z';	// char (2byte)
    a2.as.c[1] = 'z';
    
    a2.as.li = 0x0001;	// long
    a2.as.psz = "z54321z";	// char *

    memcpy(buffer, &a2, sizeof(a2));
    
    //recv packet
    //..............

    //decompress packet and unpack buffer 
    if( (error = unpack( (char *)buffer, sizeof(buffer), db, function)) )
      return error;

    ////** buffer is a naturally aligned object

    //copy buffer back to the struct it came from
    memcpy(pmystruct, buffer, sizeof(alignN::mystruct));

    //other work........

    return error;
  }


int pack( char *buffer, int buffSize, int db, int function)
{
  int error = 0;

  //lookup db number and function code - figure out defined type
  int dType = getDataType(db, function);

  //convert buffer from native packing to 2byte backing
  if( (error = convertNto2(buffer, dType)) )
    return error;
  
  return error;
}

int unpack( char *buffer, int buffSize, int db, int function)
{
  int error = 0;
  
  //lookup db number and function code - figure out defined type
  int dType = getDataType(db, function);

  //convert buffer from 2byte to native packing
  if( (error = convert2toN(buffer, dType)) )
    return error;
  
  return error;
}
















