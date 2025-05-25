/******************************************************************************/
#include "stdafx.h"
#include "@@headers.h"
#include "MyClass.h"
/******************************************************************************/
int counter = 0;
/******************************************************************************/
void InitPre() // initialize before engine inits
{
   //App.flag=APP_ALLOW_NO_XDISPLAY|APP_ALLOW_NO_GPU;
#ifdef DEBUG
   App.flag|=APP_MEM_LEAKS|APP_BREAKPOINT_ON_ERROR;
#endif

   INIT(); // call auto-generated function that will set up application name, load engine and project data
   LogConsole(true);
   LogN(S+"InitPre()");
}

/******************************************************************************/
bool Init() // initialize after engine is ready
{
   LogN(S+"Init()");
   return true;
}
/******************************************************************************/
void Shut() // shut down at exit
{
   LogN(S+"Shut()1111");
}
/******************************************************************************/
bool Update() // main updating
{
   // here you have to process each frame update
   counter = counter + 1;
   LogN(S+"counter: " + counter);
   //if(Kb.bp(KB_ESC))return false; // exit if escape on the keyboard pressed
   if(!App.active())Time.wait(1);
   //if(counter < 11)
   //{
      return true;                   // continue
   //}
   //return false;
}
/******************************************************************************/
MyClass myObject("ExampleObject", 42); // Create an instance of MyClass

void Draw() // main drawing
{
   D.clear(AZURE); // clear screen to azure color
   D.text (0, 0, "Hello to " ENGINE_NAME " Engine !"); // display text at (0, 0) screen coordinates
   D.text (0, -0.1, S+ "FPS: " + Time.fps()); // display FPS below the "Hello to..." text
   D.text (0, -0.2, S+ "Counter: " + counter); // display Counter below the FPS
   myObject.print(); // Display MyClass details
}
/******************************************************************************/

/******************************************************************************/
