/* 3a.c
Program that demonstrates a solution the the problem 
presented as #3 in the file STG_TEST under the toplevel
doc directory
*/
 
#include <stdio.h>
#include "3a.h"

char message1[] =
"This program demonstrate a solution to problem 3 of \n"
"STG_TEST under the doc directory. \n"
"The first problem with the code is that NULL is defined\n"
"improperly. If we were writting something that needed to\n"
"be portable accross systems that may or may not already \n"
"have NULL defined we need to add a prepocessor condition \n"
"that allows us to deal with NULL properly.\n"
"\n"
"Next the constructures were changed to allow for the use of";

char message2[] =
"NULL as a declaration parameter to class Thing.\n"
"A destructer was added as well. A Thing that is created"
"with a NULL char * does not allocate any memory, while a\n"
"Thing that is declared with a non-NULL char * does allocate\n"
"memory and stores the contens of whatever was passed to it.\n"
"\n"
"Please review the source code under \"src/cc/\" for a more\n"
"in depth look at the solution.\n";

int main(int argc, char *argv[])
{
  //Thing thing1((char)NULL);
  Thing thing1();
  //Thing thing1a((char *)NULL);
  Thing thing1a();
  Thing thing2("hi there");

  printf("\n%s\n", message1);
  printf("\n%s\n", message2);
}

