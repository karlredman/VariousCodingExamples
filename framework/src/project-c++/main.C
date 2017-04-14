/* project-template my-project main.c file
 */

#include <iostream>
#include "classes.h"

int main()
{
  int *p = NULL;
  int i = 0;

  myclass c;
  (void *)p = c.getData();
  cout << *p << endl;

  i = (int) *(int *)c.getData();
  cout << i << endl;

  cout << (int) *(int *)c.getData() << endl;

  cout << "done." << endl;
  return(0);
}
