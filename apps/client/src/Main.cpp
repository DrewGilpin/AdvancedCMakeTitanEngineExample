#include <unordered_map>
#include <cfloat>
#include "ConnectionToServer.h"
#include "stdafx.h"
#include "@@headers.h"
#include "MyClass.h"

/******************************************************************************/
Vec2 dot_pos(0, 0);
/******************************************************************************/

/******************************************************************************/
// ─────────────── Images ───────────────
static ImagePtr gLogo;           // smart-pointer managed by Esenthel
/******************************************************************************/




void InitPre() // initialize before engine inits
{
   //App.flag=APP_ALLOW_NO_XDISPLAY|APP_ALLOW_NO_GPU;
#ifdef DEBUG
   App.flag|=APP_MEM_LEAKS|APP_BREAKPOINT_ON_ERROR;
#endif
   App.flag|=APP_WORK_IN_BACKGROUND; // keep running when unfocused
   App.background_wait=0;            // no delay when in background

    App.name("Client");
    LogName("log_client.txt");

   INIT(); // call auto-generated function that will set up application name, load engine and project data
   LogConsole(true);
   LogN(S+"InitPre()");
}

/******************************************************************************/
bool Init() // initialize after engine is ready
{
    LogN(S+"Init()");
    SetupEnet();    // <<< NEW

    // ── grab the texture from the asset cache ──
    gLogo = ASSET_LOGO;
    if(!gLogo) LogN("Logo image failed to load!");

    return true;
}
/******************************************************************************/
void Shut() // shut down at exit
{
   LogN(S+"Shut()");
    if(gClientPeer && gClientPeer->state == ENET_PEER_STATE_CONNECTED)
    {
        enet_peer_disconnect(gClientPeer, 0);

        ENetEvent e;
        // Pump until disconnect confirmation or timeout
        for(int i=0; i<10 && enet_host_service(gClient, &e, 100) > 0; )
        {
            if(e.type == ENET_EVENT_TYPE_DISCONNECT)
                break;
            if(e.type == ENET_EVENT_TYPE_RECEIVE)
                enet_packet_destroy(e.packet);
            // continue servicing until timeout occurs or disconnect event handled
        }
        enet_host_flush(gClient);
    }
    if(gClient) enet_host_destroy(gClient);
    enet_deinitialize();
}
/******************************************************************************/
bool Update() // main updating
{
   // here you have to process each frame update
   if(Kb.bp(KB_ESC))return false; // exit if escape on the keyboard pressed

   Flt speed = 0.5f; // movement speed
   if(Kb.b(KB_LEFT )) dot_pos.x -= speed * Time.d();
   if(Kb.b(KB_RIGHT)) dot_pos.x += speed * Time.d();
   if(Kb.b(KB_UP   )) dot_pos.y += speed * Time.d();
   if(Kb.b(KB_DOWN )) dot_pos.y -= speed * Time.d();

    /* ── ENet pump ───────────────────────── */
    ServiceHost(gClient);

    if(gMyId>=0)
    {
        DotPacket pkt{gMyId, dot_pos.x, dot_pos.y};
        ENetPacket *p = enet_packet_create(&pkt, sizeof(pkt), ENET_PACKET_FLAG_UNSEQUENCED);
        enet_peer_send(gClientPeer, 0, p);
        enet_host_flush(gClient);
    }

    // send one test packet right after connection succeeds
    if(gEnetReady)
    {
        gEnetReady = false;                // only once
        static const char8 msg[] = "Hello ENet!";           // was: const char
        ENetPacket *p = enet_packet_create(msg, sizeof(msg),
                                           ENET_PACKET_FLAG_RELIABLE);
        enet_peer_send(gClientPeer, 0, p);
        enet_host_flush(gClient);          // push immediately
    }

   return true;                   // continue
}
/******************************************************************************/
MyClass myObject("ExampleObject", 42); // Create an instance of MyClass

void Draw() // main drawing
{
    D.clear(AZURE); // clear screen to azure color

    // ── draw the logo ───────────────────────────────
    if(gLogo) {
        gLogo->draw(Rect_C(0.0f, 0.5f, 0.3f, 0.3f));
    }

    D.text (0, 0, "Hello to " ENGINE_NAME " Engine !");
    D.text (0, -0.1, S+ "FPS: " + Time.fps());
    D.text (0, -0.2, S+ " Arrow keys to move dot, Esc to Exit");
    myObject.print(); // Display MyClass details
    D.dot(BLUE, dot_pos, 0.02f); // draw moving dot

   for(const auto &p : gOtherDots)
       if(p.first!=gMyId) D.dot(RED, p.second, 0.02f);
}
/******************************************************************************/
