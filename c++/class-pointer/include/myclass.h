/* myclass.h
Class used to demonstrate returning objects and their data to calling
functions
*/

#ifndef __MYCLASS_H

class myclass {

public:
  myclass();
  myclass(char *);
  myclass(char);

  ~myclass();

  /**************************** string functions ***********/
  char *get_string();		/* return the string */

  char get_stringChar(int elem);/* return a char of the string (by element) */

  char *set_string(char *);	/* set the string. A NULL argument
				     does nothing and returns NULL
				  */

  char *do_work();		/* do work on the string */

  /**************************** data ********************/
  
 private:
  char *myString;		/* a pointer to a string */
};

#endif //__MYCLASS_H
