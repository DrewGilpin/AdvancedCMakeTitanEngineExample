// Minimal dummy callbacks so EsenthelEngine can link in UnitTests.
// They do absolutely nothing and immediately ask the engine to quit.
//
// Important:  NO  'extern "C"'  here – Esenthel expects normal C++ linkage.

// (Including the header is optional but guarantees the exact prototypes.)
//#include "../Engine/EsenthelEngine.h" //dont use this path, caused warning spam didn't abide by SYSTEM
#include "EsenthelEngine.h"

void  InitPre()                         {}          // prepare options
bool  Init()                            { return true; }
void  Shut()                            {}          // cleanup
bool  Update()                          { return false; }   // run 0 frames
void  Draw()                            {}          // nothing to draw
