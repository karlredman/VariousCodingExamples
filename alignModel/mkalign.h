//align.h - structures used to test alignment methodology
//with namespaces

//allow this file to be included more than once
#ifdef  INCL_AGAIN
#undef _ALIGN_H
#endif

#ifndef _ALIGN_H
#define _ALIGN_H 1

/*
  Setup namespaces to represent the same data types using 
  different byte alignment schemes
  */

//Possible compile time option
#ifndef NATURAL_ALIGNMENT
#define NATURAL_ALIGNMENT 4	/* DEFAULT TO FOUR BYTE ALIGNMENT!!! */
#endif

//Global no packing - sets namespace/class stuff to nopacking
#define INCL_NOPACKING 1

#define MAX_STRUCT_SIZE 1024

class alignN
{
public:
#ifdef __GNUC__
	#pragma align NATURAL_ALIGNMENT	//naturally aligned structures are instantiated
#else 
	#pragma pack(NATURAL_ALIGNMENT)	//naturally aligned structures are instantiated
#endif

#define INCL_AGAIN		// re-include this header
#include "mystructs.h"		//include structures

};

class align2
{
public:
#pragma pack(2)			// 2 byte alignment

#define INCL_AGAIN		// re-include this header
#include "mystructs.h"		// include structures
};

//////////////////byte order conversion routines ////////////////////////////////////
				/* macros stolen from gnu samba project -ksr */

////big endian routines
//positioning and base macros
#define CVAL(buf, pos) (((unsigned char *) (buf))[pos])
#define PVAL(buf, pos) ((unsigned)CVAL(buf, pos))

//get 2 bytes from buf
#define SVAL(buf, pos) (PVAL(buf,pos) | PVAL(buf, (pos)+1)<<8)

//put 2 bytes into buf
#define SSVAL(buf, pos, val) SSVALX((buf), (pos), ( (uint16)(val) ) )
#define SSVALX(buf, pos, val) (CVAL(buf, pos)=(val)&0xFF, CVAL(buf, pos+1)=(val)>>8)

//get 4 bytes from buf
#define IVAL(buf, pos) (SVAL(buf, pos) | SVAL(buf, (pos)+1)<<16)

//put 4 bytes into buf
#define SIVALX(buf, pos, val) (SSVALX(buf, pos, val&0xffff), ssvalx(buf, pos+2, val>>16))


////little endian routines ("I"ntel)
//get 
#define ISVAL(buf, pos) (*(short *)((char *)(buf) + (pos))) /* 16 bits */
#define IIVAL(buf, pos) (*(int   *)((char *)(buf) + (pos)))   /* 32 bits */

//put
#define SISVAL(buf, pos, val) ISVAL(buf,pos)=((short) (val)) /* 16 bits */
#define SIIVAL(buf, pos, val) IISVAL(buf,pos)=((int) (val)) /* 32 bits */


/////////////// type definitions for conversions ///////////////////////////////

////direction of conversion
enum {
  aNto2,			/* natural to 2byte */
  a2toN //,			/* 2byte to natural */
//#define a4toN,			/* most likely natural */
//#define aNto4,			/*  */
//#define a8toN,			/* not supported yet */
//#define aNto8,			/*  */
};


				/* user types */

enum {
  s_MYSTRUCT,
    s_ANOTHERSTRUCT
    };


				/* error codes */
#define ALIGN_TYPE_NOT_SUPPORTED 0x0001


				/*  prototypes */

//data extraction
int getUval(void *val, void *buff, int numbytes, int swap);
void getval(void *val, void *buff, int numbytes);

//decide datatypes and do work
int getDataType(int db, int function);
int convertNto2(char *buffer, int dType);
int convert2toN(char *buffer, int dType);

//align structure function prototypes
int align_mystruct(char *buffer, int alignment);
int align_anotherstruct(char *buffer, int alignment);

#ifdef __GNUC__
	#pragma align NATURAL_ALIGNMENT
#else
	#pragma pack(NATURAL_ALIGNMENT)	/* re-establish natural alignment */
#endif
#endif /* end - #ifndef _ALIGN_H */









