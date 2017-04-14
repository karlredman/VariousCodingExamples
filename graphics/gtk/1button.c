//1button.c

#include <gtk/gtk.h>

//the "delete_event" signal handler
gint closeAppWindow(GtkWidget *widget, gpointer gdata)
{
  //print a message to stdout
  g_print("Quitting...\n");

  //send a quit message
  gtk_main_quit();

  //ok to be closed. TRUE would prevent window 
  //from closing
  return (FALSE);
}

//event handler called when the button is clicked
void button_clicked(GtkWidget *widget, gpointer gdata)
{
  g_print("Button was clicked.\n");
  printf("%s",gdata);
}

int main(int argc, char *argv[])
{
  GtkWidget *window;		/* toplevel window */
  GtkWidget *button;		/* the one button */

  //Initialize gtk, handle command line parameters
  gtk_init(&argc, &argv);

  //create a window gtk -note the window is NOT visible yet
  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

  //call closeAppWindow when the window gets a "delete_event" signal
  gtk_signal_connect(GTK_OBJECT(window), "delete_event",
		     GTK_SIGNAL_FUNC(closeAppWindow), NULL);

  //put some breathing room around the objects in the container
  gtk_container_border_width(GTK_CONTAINER(window), 15);

  //create a button
  button = gtk_button_new_with_label("Click me");

  //give the button an event handler -it'll call the function
  gtk_signal_connect(GTK_OBJECT(button), "clicked",
		     GTK_SIGNAL_FUNC(button_clicked), NULL);

  //make the main window contain the button widget
  gtk_container_add(GTK_CONTAINER(window), button);

  //make the button visible
  gtk_widget_show(button);

  //Now, make the window visible
  gtk_widget_show(window);

  //main event loop int gtk.  We have no event handlers though!
  gtk_main();

  //exit statis code
  return 0;
}
