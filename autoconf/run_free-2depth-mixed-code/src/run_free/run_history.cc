//run-history.cc
#include <stdio.h>
#include <string.h>

#include <gtk/gtk.h>

#include <assert.h>

#include "run-free.h"

int writeHistory(char *s);
int readHistory(GSList *h);
void freeHistoryList(GSList *h);
int historyInit(GList *cbItems);

extern GSList *historyList;

int writeHistory(char *s)
{
  FILE *fp;
  int retval = 0;
  int wLen = 0;

  //create file
  fp = fopen(RF_HISTORY_FILE_NAME, "a+");
  
  //write command line to file
  if((wLen = fputs(s, fp)) > 0)
    {
      retval = -1;
    }
  //else write a new line
   fputs("\n", fp);

  fclose(fp);			// close file

  return retval;
}

int readHistory(GSList *h)
{
  //read the history file. a series of null terminated strings in the
  //linked list s

  //returns -1 on error, 0 for no history
  
  FILE *fp;
  int numItems = 0;

  //open the file real quic to make sure it exists
  if( (fp = fopen(RF_HISTORY_FILE_NAME, "a+") ) == NULL)
    {
      g_print("run-free: history file ERROR\n");
      return -1;
    }
  fclose(fp);

  //open file
  if( (fp = fopen(RF_HISTORY_FILE_NAME, "r") ) == NULL)
    {
      g_print("run-free: history file not found\n");
      return -1;
    }

  //read each line of the file and add a list element
  char s[RF_MAX_COMMAND_LEN];
  int c;
  int i =0;
  char *string;

  memset(s, '\0', sizeof(s));

  while(1)
    {
      if( (c = fgetc(fp)) == EOF)
	{
	  //g_print("end of file\n");
	  break;
	}
      if(c != '\n')
	{
	  //	  g_print("%c", c);
	  s[i] = (unsigned char)c;
	  i++;
	  continue;
	}
      else
	{
	  //	  g_print("\nnewline detected\n");
	  i=0;
	}

      string = new char[strlen(s)+1];
      strcpy(string, s);

      //g_print("string: %s\n",string);

      historyList = g_slist_append(historyList, string);

      numItems++;
      memset(s, '\0', sizeof(s));
    }
  fclose(fp);
  
  return numItems;
}

void freeHistoryList(GSList *h)
{
  GSList *p = historyList;
  for(int i = 0; i < (int)g_slist_length(h); i++, p = p->next)
    delete p->data;
}



int historyInit(GList *cbitems)
{
  int histItems = 0;
  
  if((  histItems = readHistory(historyList) ) > 0)
    //if((  histItems = readHistory(h) ) > 0)
    {
      GSList *hItem = NULL;
      hItem = g_slist_last(historyList);
      
      assert(hItem != NULL);

      int e = g_slist_length(historyList)-1;
      int i = 0;
      for(; i < (RF_MAX_COMBO_ELEM-1) && (hItem != NULL); i++, --e,
	    hItem = g_slist_nth(historyList, e))
	{
	  //g_print("%s\n",(char *)hItem->data);
	  cbitems = g_list_append(cbitems, (char *)hItem->data);
	}
    }
  else
    {
      // This is expected to be the default list and new items will be
      //  added afte the program is first run
      cbitems = g_list_append(cbitems, "cd /etc/; emacs"); 
      cbitems = g_list_append(cbitems, "Eterm");
      cbitems = g_list_append(cbitems, "ls #use with term checkbox");
      cbitems = g_list_append(cbitems, "cat $HOME/.profile #use with term checkbox");
    }
  return 0;
}
