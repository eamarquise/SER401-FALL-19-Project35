/*************************************************************************************
 * gtk_test.cpp
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
using namespace std::chrono;


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


  	gtk_init(&argc, &argv);
	GtkWidget *window;

  	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  	gtk_widget_show(window);
  
  	g_signal_connect(window, "destroy",
     	 G_CALLBACK(gtk_main_quit), NULL);  

  	gtk_main();
	return 0;
}
