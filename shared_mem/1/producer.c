//producer.c  -writes to shared memory from standard input

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
  char buffer[BUFSIZ];
  int shmid;

  //get the shared memory address
  shmid = shmget((key_t)1234, MEM_SZ, 0666 |IPC_CREAT);

  if(shmid == -1)
    {
      fprintf(stderr, "shmget failed\n");
      exit(EXIT_FAILURE);
    }

  shared_memory = shmat(shmid, (void *)0, 0);
  if(shared_memory == (void *)-1)
    {
      fprintf(stderr, "shmat failed\n");
      exit(EXIT_FAILURE);
    }
      
  printf("Memory attached at %x\n", (int)shared_memory);

  shared_stuff = (struct shared_use_st *)shared_memory;

  while(running)
    {
      while(shared_stuff->written_by_you == 1)
	{
	  sleep(1);
	  printf("waiting for client...\n");
	}

      printf("Enter some text: ");
      fgets(buffer, BUFSIZ, stdin);
      
      strcpy(shared_stuff->some_text, buffer);
      shared_stuff->written_by_you = 1;

      if(strncmp(buffer, "end", 3) == 0)
	running = 0;

    }
  
  if(shmdt(shared_memory) == -1)
    {
      fprintf(stderr, "shmdt failed\n");
      exit(EXIT_FAILURE);
    }
  
  exit(EXIT_SUCCESS);
}
