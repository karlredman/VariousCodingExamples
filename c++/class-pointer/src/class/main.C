/* main.C
Program that demonstrates a char array used in a class
under a couple of circumstances
*/
 
#include <stdio.h>
#include <myclass.h>

// a friendly static string that is global
char message1[] =
"This program uses a string called myString that is a private\n"
"member of the class myClass\n"
"\n";

int main(int argc, char *argv[])
{
  //demonstrate the class in a couple of ways
  myclass thing1("hi there");
  myclass thing2("");

  char *lstring;

  printf("\n%s\n", message1);

  printf("############## part 1 ###########################\n");

  //add a string to thing2
  thing2.set_string("here is a string");

  //print thing1 and thing2
  printf ("%s, %s.\n", thing1.get_string(), thing2.get_string());



  printf("############## part 2 ###########################\n");

  //change thing1 to look more like an option symbol
  //(not that I can even rember what one looks like :)
  thing2.set_string("THNGX");

  //print thing2 in this form
  printf("here is thing2:%s\n", thing2.get_string());
  
  //lopp off the last char
  printf("calling do_work for thing2: %s\n", thing2.do_work() );

  //print thing2 again after the work on it
  printf("here is thing2 again:%s\n", thing2.get_string() );


  printf("############## part 3 ###########################\n");


  //now lets manipulate the string outside the class

  /*
    Note: this is really bad form -use a const pointer to make
    this not available to users.
  */

  lstring = thing2.get_string();
  
  //put a null char right in the middle of const
  lstring[2] = '\0';
  
  printf("here is lstring: %s\n", lstring);
  printf("here is thing2.get_string(): %s\n", thing2.get_string());


  return 0;
}

