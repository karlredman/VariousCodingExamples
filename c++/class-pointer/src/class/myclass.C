/* 3a.c
   Class definitions for Myclass
*/
 
#include <string.h>
#include "myclass.h"

myclass::myclass()
  :  myString(NULL)
{
  /* nothing to do here. (The string is set to Null though) */
}

myclass::myclass(char *p)
  :  myString(NULL)
{
  //if we got a NULL than just initialize.
  if(p == NULL)
    return;

  //otherwise allocate some memory 
  // (it is assumed that the string has a null char at the end '\0')
  myString = new char[strlen(p)+1];

  //check that we have the memory
  if(myString != NULL)
    {
      //save p data (copying the data into p)
      strcpy(myString, p);
    }
}

myclass::~myclass()
{
  if(myString != NULL)
    {
      //dealocate memory
      delete [] myString;
    }
}

char *
myclass::get_string()
{
  // return the address of a copy of myString
  return myString;
}

char 
myclass::get_stringChar(int elem)
{
  //return a charecter of the array
  return myString[elem];
}

char *
myclass::set_string(char *s)
{
  //if we got a NULL just return null,
  //  do nothing.
  if(s == NULL)
    {
      return NULL;
    }

  if(myString != NULL)
    {
      //if myString is already set then destroy it and
      // make a new one.
      delete [] myString;
      myString = NULL;
    }

  //we assume that we have a null terminated char array.
  myString = new char[strlen(s)+1];

  if(myString != NULL)
    {
      //copy the string 's' into myString
      strcpy(myString, s);
    }

  return myString;
}

char *
myclass::do_work()
{
  //return string after removing the last charecter
  
  /* Note: i'm cheating here by not copying the string
     into another memory location and then copying the 
     string (minus one charecter) back into myString

     here I'm just shortening the string
  */

  myString[strlen(myString)-1]='\0';

  return myString;




  /*
    here is what should be done here:

    //allocate another string
    char *tmpString = new char[strlen(myString1)+1];

    //copy myString into tmpString
    strcpy(tmpString, myString);
    
    //delete the contents of myString
    delete [] myString;


    //make a new myString (just shorter)
    char *myString = new char[strlen(myString1)];
    
    
    //copy tmpString back into myString (that is now shorter)
    strcpy(myString, tmpString);
    
    //put the missing null char at the end
    myString[strlen(myString)-1]='\0';

  */
    
}
