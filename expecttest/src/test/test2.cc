#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	printf("this is test2: a program with arguments\n");

	for(int i = 1; i < argc; i++)
		printf("test2 argv%d: %s, ", i, argv[i]);

	printf("\n");
	fflush(NULL);

	sleep(10);

	printf("Program test2 Running\n");
	fflush(NULL);

	sleep(60);

	printf("Program test2 Done\n");

	return 0;
}
