/*************************************************************************************
 * gtk_test.cpp
 *
 *
 * 
 *
 */

#include <iostream>
#include <utility>
#include <array>
#include <algorithm>
#include <vector>
#include <thread>
#include <fstream>
#include <string>
#include <cstdlib>
#include <stdio.h>
#include <chrono>

#include <gtk/gtk.h>



using namespace std;

static void
print_hello (GtkWidget *widget,
             gpointer   data)
{
  g_print ("Hi Team 35\n");
}

static void
activate (GtkApplication *app,
          gpointer        user_data)
{
  GtkWidget *window;
  GtkWidget *button;
  GtkWidget *button_box;

  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "GTK test Window");
  gtk_window_set_default_size (GTK_WINDOW (window), 200, 200);

  button_box = gtk_button_box_new (GTK_ORIENTATION_HORIZONTAL);
  gtk_container_add (GTK_CONTAINER (window), button_box);

  button = gtk_button_new_with_label ("Hi Team 35");
  g_signal_connect (button, "clicked", G_CALLBACK (print_hello), NULL);
  //g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy), window);
  gtk_container_add (GTK_CONTAINER (button_box), button);

  gtk_widget_show_all (window);
}

/*************************************************************************************
 * main
 *
 * Description:
 *
 *
 *Arguments:
 *	void
 *
 *Returns:
 *	int value 0.
 */
int main(int argc, char* argv[]){

	

	cout << "Hi Team 35" << endl;

  	GtkApplication *app;
  	int status;

  	app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
  	g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
  	status = g_application_run (G_APPLICATION (app), argc, argv);
  	g_object_unref (app);

  return status;
}
