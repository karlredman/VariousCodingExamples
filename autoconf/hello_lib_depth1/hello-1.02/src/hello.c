#ifdef HAVE_CONFIG_H
	#include <config.h>
#endif

#include <stdio.h>
#include <hello.h>
#include <common.h>

main()
{
	printf("hello world!\n");
	printf("from hello.h HELLO_MSG: %s\n", HELLO_MSG);

#ifdef VERSION
	printf("VERSION %s\n", VERSION);
#else
	printf("no VERSION macro found\n");
#endif
	hello_lib_msg();
}
