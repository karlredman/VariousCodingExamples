//consumer.c  -creates shared memory, and displays the contents

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define MEM_SZ 4096

struct shared_use_st
{
  int written_by_you;
  char some_text[BUFSIZ];
};

int main()
{
  int running = 1;
  void *shared_memory = (void *)0;
  struct shared_use_st *shared_stuff;
  int shmid;

  //seed random number generator
  srand((unsigned int) getpid());

  ////////////////////////////////////////////////////////////////
  //create the shared memory
  shmid = shmget((key_t)1234, MEM_SZ, 0666 |IPC_CREAT);

  //check for error
  if(shmid == -1)
    {
      fprintf(stderr, "shmget failed\n");
      exit(EXIT_FAILURE);
    }

  /////////////////////////////////////////////////////////////////
  //make memory available
  shared_memory = shmat(shmid, (void *)0, 0);
  
  //check for error
  if(shared_memory == (void *)-1)
    {
      fprintf(stderr, "shmat failed\n");
      exit(EXIT_FAILURE);
    }
  
  //success
  printf("Memory attached at %x\n", (int)shared_memory);
  
  /////////////////////////////////////////////////////////////////

  // assign shared_memory segment to shared_stuff.
  shared_stuff =(struct shared_use_st *)shared_memory;

  //initialize shared memory access structure
  shared_stuff->written_by_you = 0;

  //loop to display producer's data. quit when "end" is entered
  while(running)
    {
      //confirm data present
      if(shared_stuff->written_by_you)
	{
	  //display data
	  printf("you wrote: %s", shared_stuff->some_text);
	  
	  //force producer (and everyone else) to wait
	  sleep(rand()%4);
	 
	  //reset data present flag
	  shared_stuff->written_by_you = 0;

	  //terminate?
	  if(strncmp(shared_stuff->some_text, "end", 3) == 0)
	    running = 0;
	}
    }//end wile (process) loop

  //detach shared memory
  if(shmdt(shared_memory) == -1)
    {
      fprintf(stderr, "shmdt failed\n");
      exit(EXIT_FAILURE);
    }

  //remove shared memory
  if(shmctl(shmid, IPC_RMID, 0) == -1)
    {
      fprintf(stderr, "shmctl(IPC_RMID) failed\n");
      exit(EXIT_FAILURE);
    }
  
  //normal exit
  exit(EXIT_SUCCESS);
  
}//end main
