//font.c
#include <stdlib.h>
#include <Xm/Xm.h>
#include <Xm/Label.h>

XtAppContext context;
XmStringCharSet char_set=XmSTRING_DEFAULT_CHARSET;

Widget toplevel, *label;

int main(int argc, char *argv[])
{
  Arg al[10];
  int ac;
  XFontStruct *font = NULL;
  XmFontList fontlist = NULL;
  char *namestring = NULL;

  //create toplevel shell
  toplevel = XtAppInitialize(&context, "", NULL, 0, &argc, argv, NULL,
			     NULL, 0);

  //create label widget
  ac=0;
  XtSetArg(al[ac], XmNlabelString, XmStringCreateLtoR("Hello World",
						      char_set));
  ac++;
  XtSetArg(al[ac], XmNheight, 300); ac++;
  XtSetArg(al[ac], XmNwidth, 300);ac++;

  //without this the window resizes to the font height and width
  XtSetArg(al[ac], XmNrecomputeSize, False);ac++;

  label = malloc(sizeof(Widget));
  *label = XmCreateLabel(toplevel, "label", al, ac);
  XtManageChild((Widget)*label);

  //set fontlist resource in the label widget
  namestring = "*times*24*";
  font = XLoadQueryFont(XtDisplay((Widget)*label), namestring);
  fontlist=XmFontListCreate(font, char_set);

  ac=0;
  XtSetArg(al[ac], XmNfontList, fontlist); ac++;
  XtSetValues((Widget)*label, al, ac);

  XtRealizeWidget(toplevel);
  XtAppMainLoop(context);

  free(label);
  return(0);
}
