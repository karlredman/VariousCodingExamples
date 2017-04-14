//mystructs.h - structures used to test alignment methodology
//with namespaces

//allow this file to be included more than once
#ifdef  INCL_AGAIN
#undef _MYSTRUCTS_H
#undef INCL_AGAIN
#endif

#ifndef _MYSTRUCTS_H
#define _MYSTRUCTS_H 1

//demonstrate turning pack 2 off
#ifndef INCL_NOPACKING
#pragma pack(2);
#endif

//structures - poorly laid out on purpose for testing

typedef struct _ANOTHERSTRUCT {
  short		si;
  char          c[2];
  long		li;
  char *	psz;		/* char array */
} anotherstruct;

typedef struct _MYSTRUCT {
  char		c1;		/* single byte */
  long		li;	        /*likely to crash on 4byte alignment */
  short         si;
  char		c2;
  anotherstruct as;		/* embeded structure */
} mystruct;


#endif /* end - #ifndef _ALIGN_H */
