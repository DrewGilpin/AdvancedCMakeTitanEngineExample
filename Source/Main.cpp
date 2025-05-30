/******************************************************************************/
#include "stdafx.h"
#include <enet/enet.h>
#include "@@headers.h"
#include "MyClass.h"
/******************************************************************************/
int counter = 0;
Vec2 dot_pos(0, 0);
ENetHost* server = nullptr;
ENetHost* client = nullptr;
ENetPeer* client_peer = nullptr;
ENetPeer* server_peer = nullptr;
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
   if(enet_initialize() != 0)
   {
      LogN(S+"ENet initialization failed");
      return false;
   }

   ENetAddress address; // server address
   address.host = ENET_HOST_ANY;
   address.port = 12345;
   server = enet_host_create(&address, 1, 1, 0, 0);
   if(!server)
   {
      LogN(S+"Failed to create ENet server");
      return false;
   }

   client = enet_host_create(NULL, 1, 1, 0, 0);
   if(!client)
   {
      LogN(S+"Failed to create ENet client");
      return false;
   }

   ENetAddress addr;
   enet_address_set_host(&addr, "127.0.0.1");
   addr.port = 12345;
   client_peer = enet_host_connect(client, &addr, 1, 0);
   if(!client_peer)
   {
      LogN(S+"Failed to initiate ENet connection");
   }

   return true;
}
/******************************************************************************/
void Shut() // shut down at exit
{
   LogN(S+"Shut()1111");
   if(client_peer)
      enet_peer_disconnect_now(client_peer, 0);
   if(client)
      enet_host_destroy(client);
   if(server)
      enet_host_destroy(server);
   enet_deinitialize();
}
/******************************************************************************/
bool Update() // main updating
{
   // here you have to process each frame update
   counter = counter + 1;
   LogN(S+"counter: " + counter);
   ENetEvent event;
   while(server && enet_host_service(server, &event, 0) > 0)
   {
      switch(event.type)
      {
         case ENET_EVENT_TYPE_CONNECT:
            LogN(S+"Server: client connected");
            server_peer = event.peer;
            break;
         case ENET_EVENT_TYPE_RECEIVE:
            LogN(S+"Server received: " + (const char*)event.packet->data);
            enet_packet_destroy(event.packet);
            break;
         default: break;
      }
   }

   while(client && enet_host_service(client, &event, 0) > 0)
   {
      switch(event.type)
      {
         case ENET_EVENT_TYPE_CONNECT:
            LogN(S+"Client: connected to server");
            if(client_peer)
            {
               const char msg[] = "hello";
               ENetPacket* packet = enet_packet_create(msg, sizeof(msg), ENET_PACKET_FLAG_RELIABLE);
               enet_peer_send(client_peer, 0, packet);
            }
            break;
         case ENET_EVENT_TYPE_RECEIVE:
            LogN(S+"Client received: " + (const char*)event.packet->data);
            enet_packet_destroy(event.packet);
            break;
         case ENET_EVENT_TYPE_DISCONNECT:
            LogN(S+"Client disconnected");
            client_peer = nullptr;
            break;
         default: break;
      }
   }
   //if(Kb.bp(KB_ESC))return false; // exit if escape on the keyboard pressed

   Flt speed = 0.5f; // movement speed
   if(Kb.b(KB_LEFT )) dot_pos.x -= speed * Time.d();
   if(Kb.b(KB_RIGHT)) dot_pos.x += speed * Time.d();
   if(Kb.b(KB_UP   )) dot_pos.y += speed * Time.d();
   if(Kb.b(KB_DOWN )) dot_pos.y -= speed * Time.d();

   if(!App.active())Time.wait(1);

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
