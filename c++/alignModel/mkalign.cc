//mkalign.cc

#include <string.h>
#include "mkalign.h"


int convertNto2(char *buffer, int dType)
{
  //convert a native structure to a 2 byte structure
  switch(dType)
    {
    case s_MYSTRUCT:
      {
	align_mystruct(buffer, aNto2);
      }
    break;
    case s_ANOTHERSTRUCT:
	align_anotherstruct(buffer, aNto2);
    break;
    default:
      return ALIGN_TYPE_NOT_SUPPORTED;
    }
  return 0;
}


int convert2toN(char *buffer, int dType)
{
  //convert a 2byte structure to a native structure
    switch(dType)
    {
    case s_MYSTRUCT:
	align_mystruct(buffer, a2toN);
    break;
    case s_ANOTHERSTRUCT:
	align_anotherstruct(buffer, a2toN);
    break;
    default:
      return ALIGN_TYPE_NOT_SUPPORTED;
    }
  return 0;
}

int getDataType(int db, int function)
{
  //lookup data type in table
  return s_MYSTRUCT;
}

///////// extract data - no byte swaping
void getval(void *val, void *buff, int numbytes)
{
  //unconditionally get a value
  
  unsigned char *p = (unsigned char *)buff;
  unsigned char *q = (unsigned char *)val;
  
  for(int i = 0; i < numbytes; i++)
      *q++ = *p++;
}

//carefull, autoswaping
int getUval(void *val, void *buff, int numbytes, int swap)
{
  //get an unsigned value and swap the bytes if desired

  unsigned char *p = (unsigned char *)buff;
  unsigned char *q = (unsigned char *)val;

  if(swap)
    {
      switch(numbytes)
	{
	case 2:
	  //get and swap 2bytes ("short value")
	  *q = SVAL(buff,0);
	  break;
	case 4:
	  //get and swap 4 bytes ("int value")
	  *q = IVAL(buff,0);
	  break;
	case 8:			// not supported yet
	  return -1;
	  break;
	default:
	  //donothing
	  break;
	}
    }
  else
    for(int i = 0; i < numbytes; i++)
	*q++ = *p++;

  return 0;
}




///////// align structures

int align_mystruct(char *buffer, int a)
{
  char tmpbuff[MAX_STRUCT_SIZE]; // used for embed structure

  switch(a)
    {
    case a2toN:
      {
	align2::mystruct a2;
	alignN::mystruct aN;
	
	memcpy(&a2, buffer,sizeof(align2::mystruct));
	
	getval((void *)&aN.c1, (void *)&a2.c1, sizeof(a2.c1));
	getval((void *)&aN.li, (void *)&a2.li, sizeof(a2.li));
	getval(&aN.si, &a2.si, sizeof(a2.si));
	getval(&aN.c2, &a2.c2, sizeof(a2.c2));
	
	memcpy(&tmpbuff, &a2.as,sizeof(a2.as));
	align_anotherstruct((char *)tmpbuff, a);
	memcpy(&aN.as, &tmpbuff, sizeof(aN.as));
	
	memcpy(buffer, &aN, sizeof(alignN::mystruct));
      }
    break;
    case aNto2:
      {
	align2::mystruct a2;
	alignN::mystruct aN;
	
	memcpy(&aN, buffer,sizeof(alignN::mystruct));
	
	getval(&a2.c1, &aN.c1, sizeof(aN.c1));
	getval(&a2.li, &aN.li, sizeof(aN.li));
	getval(&a2.si, &aN.si, sizeof(aN.si));
	getval(&a2.c2, &aN.c2, sizeof(aN.c2));
	
	memcpy(&tmpbuff, &aN.as,sizeof(aN.as));
	align_anotherstruct((char *)tmpbuff, a);
	memcpy(&a2.as, &tmpbuff, sizeof(a2.as));
	
	memcpy(buffer, &a2, sizeof(align2::mystruct));
      }
    break;
    default:
      //do nothing
      break;
    } // end switch
  
  return 0;
}


#define PSZSIZE 10

int align_anotherstruct(char *buffer, int a)
{
  switch(a)
    {
    case a2toN:
      {
	align2::anotherstruct a2;
	alignN::anotherstruct aN;
	
	memcpy(&a2, buffer,sizeof(align2::anotherstruct));
	
	getval(&aN.si, &a2.si, sizeof(a2.si));
	getval(&aN.c, &a2.c, sizeof(a2.c));
	getval(&aN.li, &a2.li, sizeof(a2.li));
	getval(&aN.psz, &a2.psz, PSZSIZE);
	
	memcpy(buffer, &aN, sizeof(alignN::mystruct));
      }
    case aNto2:
      {
	align2::anotherstruct a2;
	alignN::anotherstruct aN;
	
	memcpy(&aN, buffer,sizeof(align2::anotherstruct));
	
	getval(&a2.si, &aN.si, sizeof(aN.si));
	getval(&a2.c, &aN.c, sizeof(aN.c));
	getval(&a2.li, &aN.li, sizeof(aN.li));
	getval(&a2.psz, &aN.psz, PSZSIZE); 
	
	// cheeted here, this will have to be figured out
	// for now a global table of sizes would do or some class method.
	
	memcpy(buffer, &a2, sizeof(align2::anotherstruct));
      }
    }
  return 0;
}
