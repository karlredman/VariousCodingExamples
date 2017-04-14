/*qq1.c*/

#include <Xm/Xm.h>
#include <Xm/Label.h>
#include <Xm/Text.h>

XtAppContext context;
XmStringCharSet char_set=XmSTRING_DEFAULT_CHARSET;

Widget toplevel, label, text;

main(int argc, char *argv[])
{
  Arg al[10];
  int ac;

  /* create the toplevel shell */
  toplevel=XtAppInitialize(&context, "", NULL, 0, &argc, argv,
			   NULL, NULL, 0); 

  /*create label widget */
  ac=0;
  XtSetArg(al[ac], XmNlabelString,
	   XmStringCreateLtoR("Hello World!", char_set)); ac++;
  label=XmCreateLabel(toplevel, "label", al, ac);
  XtManageChild(label);

  //create text  widget
  ac=0; 
  XtSetArg(al[ac], XmNeditMode, XmMULTI_LINE_EDIT); ac++;
  XtSetArg(al[ac], XmNheight, 200); ac++;
  XtSetArg(al[ac], XmNwidth, 200); ac++;
  text = XmCreateText(toplevel, "text", al, ac);
  XtManageChild(text);

  //set resources (after creation)
  ac=0;
  XtSetArg(al[ac], XmNheight, 300); ac++;
  XtSetArg(al[ac], XmNwidth, 300); ac++;
  XtSetValues(label, al, ac);

  XtRealizeWidget(toplevel);
  XtAppMainLoop(context);
}





