#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	printf("this is test3: a program with arguments\n");
	printf("this program will demonstrate and error condition\n");

	for(int i = 1; i < argc; i++)
		printf("test3 argv%d: %s, ", i, argv[i]);

	printf("\n");
	fflush(NULL);
	
	//sleep(1);

	printf("Program Error\n");
	fflush(NULL);

	return(1);
}
