//gtk_sig1.c

#include <gtk/gtk.h>

//the "delete_event" signal handler
gint destroyapp(GtkWidget *widget, gpointer gdata)
{
  //print a message to stdout
  g_print("Quitting...\n");

  //send a quit message
  gtk_main_quit();

  //ok to be closed. TRUE would prevent window 
  //from closing
  return (FALSE);
}

int main(int argc, char *argv[])
{
  GtkWidget *window;		/* toplevel window */

  //Initialize gtk, handle command line parameters
  gtk_init(&argc, &argv);

  //create a window gtk -note the window is NOT visible yet
  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

  //call destroyapp when the window gets a "delete_event" signal
  gtk_signal_connect(GTK_OBJECT(window), "delete_event",
		     GTK_SIGNAL_FUNC(destroyapp), NULL);

  //Now, make the window visible
  gtk_widget_show(window);

  //main event loop int gtk.  We have no event handlers though!
  gtk_main();

  //exit statis code
  return 0;
}
