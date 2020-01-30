#ifndef RESULTWIDOW_H_
#define RESULTWINDOW_H_

#include <iostream>
#include <string>
#include <cstdlib>
#include <stdio.h>

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Int_Input.H>
#include <FL/Fl_RGB_Image.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Text_Display.H>


using namespace std;

class ResultWindow {


    public:

		Fl_Window *windowResult;
		//Fl_Box *boxHeader;
		Fl_Text_Display *textDisplay;
		Fl_Text_Buffer *buffer;
        ResultWindow();
        ~ResultWindow();
        void addText(string resultArray[]);

};

#endif /*SRC_MAIN_RESULTWINDOW_H_*/
