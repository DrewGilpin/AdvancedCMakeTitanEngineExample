/******************************************************************************/
#include "stdafx.h"
#include <enet/enet.h>
#include <cstring>
#include "@@headers.h"
#include "MyClass.h"
/******************************************************************************/
int counter = 0;
Vec2 dot_pos(0, 0);

ENetHost *gServer = nullptr;
ENetHost *gClient = nullptr;
ENetPeer *gPeer   = nullptr;
bool      gConnected = false;
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

   if (enet_initialize() != 0)
   {
      LogN(S+"Enet init failed");
      return false;
   }
   atexit(enet_deinitialize);

   ENetAddress address;
   address.host = ENET_HOST_ANY;
   address.port = 12345;
   gServer = enet_host_create(&address, 1, 1, 0, 0);
   if(!gServer)
   {
      LogN(S+"Failed to create ENet server");
      return false;
   }

   gClient = enet_host_create(NULL, 1, 1, 0, 0);
   if(!gClient)
   {
      LogN(S+"Failed to create ENet client");
      return false;
   }

   enet_address_set_host(&address, (const char8*)"127.0.0.1");
   gPeer = enet_host_connect(gClient, &address, 1, 0);
   if(!gPeer)
   {
      LogN(S+"Failed to start ENet connection");
      return false;
   }

   return true;
}
/******************************************************************************/
void Shut() // shut down at exit
{
   LogN(S+"Shut()1111");
   if(gPeer)   enet_peer_disconnect(gPeer, 0);
   if(gClient) enet_host_destroy(gClient);
   if(gServer) enet_host_destroy(gServer);
}
/******************************************************************************/
bool Update() // main updating
{
   // here you have to process each frame update
   counter = counter + 1;
   LogN(S+"counter: " + counter);
   //if(Kb.bp(KB_ESC))return false; // exit if escape on the keyboard pressed

   Flt speed = 0.5f; // movement speed
   if(Kb.b(KB_LEFT )) dot_pos.x -= speed * Time.d();
   if(Kb.b(KB_RIGHT)) dot_pos.x += speed * Time.d();
   if(Kb.b(KB_UP   )) dot_pos.y += speed * Time.d();
   if(Kb.b(KB_DOWN )) dot_pos.y -= speed * Time.d();

   if(!App.active())Time.wait(1);

   ENetEvent event;
   while(gServer && enet_host_service(gServer, &event, 0) > 0)
   {
      switch(event.type)
      {
         case ENET_EVENT_TYPE_CONNECT:
            LogN(S+"Server: client connected");
            break;
         case ENET_EVENT_TYPE_RECEIVE:
            LogN(S+"Server recv: "+(char8*)event.packet->data);
            enet_packet_destroy(event.packet);
            break;
         default: break;
      }
   }

   while(gClient && enet_host_service(gClient, &event, 0) > 0)
   {
      switch(event.type)
      {
         case ENET_EVENT_TYPE_CONNECT:
            gConnected = true;
            LogN(S+"Client connected to server");
            break;
         case ENET_EVENT_TYPE_RECEIVE:
            LogN(S+"Client recv: "+(char8*)event.packet->data);
            enet_packet_destroy(event.packet);
            break;
         default: break;
      }
   }

   if(gConnected && gPeer)
   {
      const char8 *msg = (const char8*)"Hello ENet";
      ENetPacket *packet = enet_packet_create(msg, sizeof("Hello ENet"), ENET_PACKET_FLAG_RELIABLE);
      enet_peer_send(gPeer, 0, packet);
      enet_host_flush(gClient);
      gConnected = false;
   }

   return true;                   // continue
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
   D.dot(RED, dot_pos, 0.02f); // draw moving dot
}
/******************************************************************************/

/******************************************************************************/
