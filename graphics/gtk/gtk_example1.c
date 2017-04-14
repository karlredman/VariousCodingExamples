//gtk_example1.c
//gcc -Wall -g gtk_example1.c -o x `gtk-config -cflags` `gtk-config -libs`

#include <gtk/gtk.h>


int main(int argc, char *argv[])
{
  GtkWidget *window;

  //Initialize gtk, handle command line parameters
  gtk_init(&argc, &argv);

  //create a window gtk -note the window is NOT visible yet
  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

  //Now, make the window visible
  gtk_widget_show(window);

  //main event loop int gtk.  We have no event handlers though!
  gtk_main();

  //exit statis code
  return 0;
}


