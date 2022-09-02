/******************************************************************************/
#include "stdafx.h"
#include "@@headers.h"
/******************************************************************************/
int counter = 0;
/******************************************************************************/
void InitPre() // initialize before engine inits
{
   App.flag=APP_ALLOW_NO_XDISPLAY|APP_ALLOW_NO_GPU;
#ifdef DEBUG
   App.flag|=APP_MEM_LEAKS|APP_BREAKPOINT_ON_ERROR;
#endif

   INIT(); // call auto-generated function that will setup application name, load engine and project data
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
   LogN(S+"Shut()");
}
/******************************************************************************/
bool Update() // main updating
{
   // here you have to process each frame update
   counter = counter + 1;
   LogN(S+"counter: " + counter);
   //if(Kb.bp(KB_ESC))return false; // exit if escape on the keyboard pressed
   if(!App.active())Time.wait(1);
   if(counter < 11)
   {
      return true;                   // continue
   }
   return false;
}
/******************************************************************************/
void Draw() // main drawing
{
}
/******************************************************************************/

/******************************************************************************/
