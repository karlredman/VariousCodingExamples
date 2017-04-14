// text.c
#include <Xm/Xm.h>
#include <Xm/Text.h>

XtAppContext context;
Widget toplevel, text;

int main(int argc, char *argv[])
{
  Arg al[10];
  int ac;

  // create the toplevel shell
  toplevel = XtAppInitialize(&context, "", NULL, 0, &argc, argv, NULL,
			     NULL, 0);

  //create text  widget
  ac=0; 
  XtSetArg(al[ac], XmNeditMode, XmMULTI_LINE_EDIT); ac++;
  XtSetArg(al[ac], XmNheight, 200); ac++;
  XtSetArg(al[ac], XmNwidth, 200); ac++;
  text = XmCreateText(toplevel, "text", al, ac);
  XtManageChild(text);



  XtRealizeWidget(toplevel);
  XtAppMainLoop(context);

  return 0;
}




