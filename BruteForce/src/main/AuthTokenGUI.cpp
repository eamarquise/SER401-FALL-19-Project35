/*
 * AuthTokenGUI.cpp
 *
 *  Created on: Jan 31, 2020
 *      Author: myles
 */

#include "AuthTokenGUI.h"
#include "ClassSelectorGUI.h"
#include "MainWindow.h"
#include "main.h"

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <stdio.h>

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_File_Chooser.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_File_Browser.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Input_Choice.H>
#include <FL/Fl_RGB_Image.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Widget.H>
#include <FL/Fl_File_Chooser.H>


AuthTokenGUI::AuthTokenGUI(Fl_Window* win) {
	//previous window
	  prevWindow = win;
	  nextWindowFlag = false;

	//INITIALIZE COMPONENTS
	    tokenWindow = new Fl_Window(450, 250, "Authentication Token");
	    //FL_(X, Y, W, H, STRING)
	    boxHeader = new Fl_Box(20,20,400,50, "Please Select The File That Contains The Authentication Token.");
	    outputToken = new Fl_Output(20, 150, 410, 30, "");

	    findFile = new Fl_Button(50, 100, 100, 30, "Find File");
	    goBack = new Fl_Button(250, 200, 80, 30, "Go_Back");
	    Continue = new Fl_Button(350, 200, 80, 30, "Continue");

	    //callbacks
	    findFile->callback(static_FindFileClick, this);
	    goBack->callback(static_GobackClick, this);
	    Continue->callback(static_ContinueClick, this);

	    //Additions to the components


	    boxHeader->box(FL_UP_BOX);
	    boxHeader->labelfont(FL_BOLD);
	    boxHeader->labelsize(40);
	    boxHeader->labelcolor(FL_BLUE);

	    tokenWindow->show();
	    tokenWindow->end();

	    Fl::run();

}//end constructor

AuthTokenGUI::~AuthTokenGUI() {
	// TODO Auto-generated destructor stub
}




/*************************************************************************************
 * FindFileClick
 *
 * Description:
 *
 *
 *Arguments:
 *	FL_Widget* w
 *
 *Returns:
 *	nothing
 */
void AuthTokenGUI::FindFileClick(Fl_Widget* w){

 tokenChooser = new Fl_File_Chooser("/home/","*",FL_SINGLE, "Authentication Token");
// tokenChooser = new Fl_File_Chooser(".","*",FL_SINGLE, "Authentication Token");
 tokenChooser->show();

 //wait until the user selects a file.
 while(tokenChooser->shown()){
	 Fl::wait();
 }

 //if cancel was selected
 if ( tokenChooser->value() == NULL )
      {  return; }


 cout<<tokenChooser->value()<<endl;


 //read in the file

  ifstream AuthtokenFile;
  AuthtokenFile.open(tokenChooser->value());
  char output[100];
  if (AuthtokenFile.is_open()) {
  while (!AuthtokenFile.eof()) {
	 AuthtokenFile >> output;
     Authentication_Token = output;
  }
 }
  AuthtokenFile.close();

  cout<<"The Authentication Token is: "<<Authentication_Token<<endl;

  //convert the string to char*
  int length = Authentication_Token.length();
  char token_char[length+1];
  strcpy(token_char, Authentication_Token.c_str());


  outputToken->value(token_char);
}


/*************************************************************************************
 * FileSelection
 *
 * Description:
 *		This function is the callback for the File Chooser.
 *
 *
 *Arguments:
 *	FL_Widget* w
 *
 *Returns:
 *	nothing
 */
void AuthTokenGUI::FileSelection(Fl_Widget* w){

}

/*************************************************************************************
 * GobackClick
 *
 * Description:
 *		This function is the callback for the Go back button.
 *		This button returns to the previous GUI window.
 *
 *Arguments:
 *	FL_Widget* w
 *
 *Returns:
 *	nothing
 */
void AuthTokenGUI::GobackClick(Fl_Widget* w){

	tokenWindow->hide();

	prevWindow->show();


}

/*************************************************************************************
 * ContinueClick
 *
 * Description:
 *		This function is the callback for the Continue button.
 *		This button opens the next GUI window.
 *
 *Arguments:
 *	FL_Widget* w
 *
 *Returns:
 *	nothing
 */
void AuthTokenGUI::ContinueClick(Fl_Widget* w){

	tokenWindow->hide();
	 //call to next GUI window.

	    if(nextWindowFlag == false){
	    ClassSelectorGUI classGUI(tokenWindow);
	    nextWindow = classGUI.classWindow;
	    nextWindowFlag = true;

	    }else{
	    nextWindow->show();

	    }

}
