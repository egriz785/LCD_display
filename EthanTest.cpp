/* A LCD Character Display applications
* Written by Derek Molloy for the book "Exploring BeagleBone: Tools and 
* Techniques for Building with Embedded Linux" by John Wiley & Sons, 2014
* ISBN 9781118935125. Please see the file README.md in the repository root 
* directory for copyright and GNU GPLv3 license information.            */

#include <iostream>
#include <sstream>
#include <string>
#include <unistd.h>
#include <cmath>
#include "display/LCDCharacterDisplay.h"

#define delay_time 500000

using namespace std;
using namespace exploringBB;

int main(int argc, char* argv[]){
  if(argc != 3) {
    cout << "Program takes 2 arguments." << endl;
    cout << "Example invocation:" << endl;
    cout << "EthanTest str1 str2" << endl;
    return -1;
  }

   //cout << "Starting EBB LCD Character Display Example" << endl;
   //SPIDevice *busDevice = new SPIDevice(2,0); //Using second SPI bus (both loaded)
   SPIDevice *busDevice = new SPIDevice(0,0); //Using second SPI bus (both loaded)
   busDevice->setSpeed(1000000);      // Have access to SPI Device object
   ostringstream s;                   // Using this to combine text and int data
   LCDCharacterDisplay display(busDevice, 16, 2); // Construct 16x2 LCD Display
   display.clear();                   // Clear the character LCD module
   display.home();                    // Move the cursor to the (0,0) position
   
   //display.print("EBB by D. Molloy"); // String to display on the first row
   
  string top(argv[1]);
  string bottom(argv[2]);

  int top_len = top.length();
  int bot_len = bottom.length();

  // Pad the shorter string

  if(top_len > bot_len) {
    stringstream temp;
    
    for(int i = 0; i < ceil((float)(top_len-bot_len)/2); i++) {
      temp << " ";
    }
    
    temp << bottom;
    
    for(int i = 0; i < floor((float)(top_len-bot_len)/2); i++) {
      temp << " ";
    }
    
    bottom = temp.str();

  }

  else if(top_len < bot_len) {
    stringstream temp;
    
    for(int i = 0; i < ceil((float)(bot_len-top_len)/2); i++) {
      temp << " ";
    }
    
    temp << top;

    for(int i = 0; i < floor((float)(bot_len-top_len)/2); i++) {
      temp << " ";
    }

    top = temp.str();
  }

  int len = (top_len > bot_len) ? top_len : bot_len;

  display.setCursorOff(true);
  display.setCursorBlink(false);
  
  while(1) {
    for(int i = -len; i < 16; i++) {
      display.clear();
      if(i == -len) {
        // don't print anything
      }
      else if (i > -len && i < 0) {
        display.setCursorPosition(0,0);
        display.print(top.substr(-i,len));
        display.setCursorPosition(1,0);
        display.print(bottom.substr(-i,len));
      }
      else {
        display.setCursorPosition(0,i);
        display.print(top);
        display.setCursorPosition(1,i);
        display.print(bottom);
      }
      usleep(delay_time); // half second sleep
    }
  }

  // Old leftover code when I was having it "bounce" instead of scroll

  /*
  while(1) {
    for(int i = 0; i <= 16-topline.length(); i++) {
      display.clear();
      display.setCursorPosition(0,i);
      display.print(topline);
      display.setCursorPosition(1,i);
      display.print(bottomline);
      usleep(delay_time); // half second sleep
    }

    for(int i = 16-topline.length(); i > -1; i--) {
      display.clear();
      display.setCursorPosition(0,i);
      display.print(topline);
      display.setCursorPosition(1,i);
      display.print(bottomline);
      usleep(delay_time); // half second sleep
    }
  }
  */

  /*
   for(int x=0; x<=10000; x++){       // Do this 10,000 times
      s.str("");                      // clear the ostringstream object s
      display.setCursorPosition(1,3); // move the cursor to second row
      s << "X=" << x;                 // construct a string that has an int value
      display.print(s.str());         // print the string X=*** on the LCD module
   }
   cout << "End of EBB LCD Character Display Example" << endl;
  */

return 0;
}
