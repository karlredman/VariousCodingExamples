/*label.c*/

#include <Xm/Xm.h>
#include <Xm/Label.h>

XtAppContext context;
XmStringCharSet char_set=XmSTRING_DEFAULT_CHARSET;

Widget toplevel, label;

main(int argc, char *argv[])
{
	Arg al[10];
	int ac;

	/* create the toplevel shell */
	toplevel=XtAppInitialize(&context, "", NULL, 0, &argc, argv, NULL, NULL, 0);

	/*create label widget */
	ac=0;

	XtSetArg(al[ac], XmNlabelString,
		XmStringCreateLtoR("Hello World!", char_set)); ac++;
	XtSetArg(al[ac], XmNheight, 300); ac++;
	XtSetArg(al[ac], XmNwidth, 300); ac++;
	

	label=XmCreateLabel(toplevel, "label", al, ac);
	XtManageChild(label);
	
	XtRealizeWidget(toplevel);
	XtAppMainLoop(context);
}
