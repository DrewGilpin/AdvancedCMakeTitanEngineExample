
/******************************************************************************/
// ⚠️  ONE translation unit must *both* `#define ENET_IMPLEMENTATION` *and*
//     `#include "enet.h"` – put it right above the rest of your includes.
#define ENET_IMPLEMENTATION
#include "enet.h"          // ← Header-only ENet (third_party/enet/enet.h)
/******************************************************************************/

#if defined(__linux__)
  /* Keep a copy for later code that might really need the macros… */
  #pragma push_macro("LOCK_READ")
  #pragma push_macro("LOCK_WRITE")
  #undef  LOCK_READ
  #undef  LOCK_WRITE
#endif

/******************************************************************************/
#include "stdafx.h"
#include "@@headers.h"
#include "MyClass.h"
#include <unordered_map>
#include <vector>

#if defined(__linux__)
  /* …and restore them so any <fcntl.h>-style users still compile. */
  #pragma pop_macro("LOCK_WRITE")
  #pragma pop_macro("LOCK_READ")
#endif

/******************************************************************************/
int counter = 0;
Vec2 dot_pos(0, 0);
/******************************************************************************/

/******************************************************************************/
// ─────────────── ENet globals ───────────────
static ENetHost *gClient      = nullptr;   // connects to the server
static ENetPeer *gClientPeer  = nullptr;   // client-side handle
static bool      gEnetReady   = false;     // set true once connected

enum PacketType : U8
{
    PK_WELCOME = 1,
    PK_CHAT,
    PK_POS
};

static U16 gClientID = 0xFFFF;
static std::unordered_map<U16, Vec2> gPlayers; // other players
static std::vector<Str8> gChatLines;
static Str8 gChatInput;
/******************************************************************************/
// Local helpers
static void SetupEnet()
{
    if(enet_initialize() != 0){ LogN("ENet init failed"); return; }

    ENetAddress addr{};             // zero-initialise **all** fields
    addr.port = 12345;

    // ── create client host (no binding → will use ephemeral port) ──
    gClient = enet_host_create(nullptr, 1, 2, 0, 0);
    if(!gClient){ LogN("ENet client create failed"); return; }

    // ── connect client to server on loopback ──
    enet_address_set_host(&addr, "127.0.0.1");
    gClientPeer = enet_host_connect(gClient, &addr, 2, 0);
    LogN("ENet client setup complete, waiting for connect…");
}

static void ServiceHost(ENetHost *host)
{
    if(!host) return;
    ENetEvent e;
    while(enet_host_service(host, &e, 0) > 0)      // non-blocking pump
    {
        switch(e.type)
        {
            case ENET_EVENT_TYPE_CONNECT:
                LogN(S+"[ENet] Peer connected, ch:" + int(e.channelID));
                if(host == gClient) gEnetReady = true;
            break;

                /*
            case ENET_EVENT_TYPE_RECEIVE:
                LogN(S+"[ENet] Got pkt (“" + (char*)e.packet->data + "”)");
                enet_packet_destroy(e.packet);
            break;*/

            case ENET_EVENT_TYPE_RECEIVE:
            {
                if(e.packet->dataLength>0)
                {
                    U8 type=((U8*)e.packet->data)[0];
                    if(type==PK_WELCOME && e.packet->dataLength>=3)
                    {
                        gClientID = *(U16*)((U8*)e.packet->data+1);
                    }
                    else if(type==PK_CHAT)
                    {
                        U16 id=*(U16*)((U8*)e.packet->data+1);
                        const char8* txt=(char8*)e.packet->data+3;
                        Str8 line; line+=S+"["+id+"] "; line+=txt;
                        gChatLines.push_back(line);
                    }
                    else if(type==PK_POS && e.packet->dataLength>=3+sizeof(Flt)*2)
                    {
                        struct PosPkt{U8 t; U16 id; Flt x; Flt y;};
                        const PosPkt* pp=(PosPkt*)e.packet->data;
                        gPlayers[pp->id].set(pp->x, pp->y);
                    }
                }
                enet_packet_destroy(e.packet);
                break;
            }

            case ENET_EVENT_TYPE_DISCONNECT:
                LogN("[ENet] Peer disconnected");
                gPlayers.erase(e.peer->incomingPeerID);
            break;

            default: break;
        }
    }
}
/******************************************************************************/


void InitPre() // initialize before engine inits
{
   //App.flag=APP_ALLOW_NO_XDISPLAY|APP_ALLOW_NO_GPU;
#ifdef DEBUG
   App.flag|=APP_MEM_LEAKS|APP_BREAKPOINT_ON_ERROR;
#endif
   App.flag|=APP_WORK_IN_BACKGROUND; // keep running when unfocused
   App.background_wait=0;            // no delay when in background

   INIT(); // call auto-generated function that will set up application name, load engine and project data
   LogConsole(true);
   LogN(S+"InitPre()");
}

/******************************************************************************/
bool Init() // initialize after engine is ready
{
   LogN(S+"Init()");
    SetupEnet();    // <<< NEW
   return true;
}
/******************************************************************************/
void Shut() // shut down at exit
{
   LogN(S+"Shut()1111");
    if(gClient) enet_host_destroy(gClient);
    enet_deinitialize();
}
/******************************************************************************/
bool Update() // main updating
{
   // here you have to process each frame update
   counter = counter + 1;
   //LogN(S+"counter: " + counter);
   //if(Kb.bp(KB_ESC))return false; // exit if escape on the keyboard pressed

   Flt speed = 0.5f; // movement speed
   if(Kb.b(KB_LEFT )) dot_pos.x -= speed * Time.d();
   if(Kb.b(KB_RIGHT)) dot_pos.x += speed * Time.d();
   if(Kb.b(KB_UP   )) dot_pos.y += speed * Time.d();
   if(Kb.b(KB_DOWN )) dot_pos.y -= speed * Time.d();

    /* ── ENet pump ───────────────────────── */
    ServiceHost(gClient);

    while(Kb.k.any())
    {
        if(Kb.k.k==KB_ENTER)
        {
            if(gChatInput.is() && gClientID!=0xFFFF)
            {
                int len=gChatInput.length()+4;
                std::vector<Byte> buf(len);
                buf[0]=PK_CHAT; *(U16*)(&buf[1])=gClientID;
                memcpy(buf.data()+3, gChatInput(), gChatInput.length()+1);
                ENetPacket *p=enet_packet_create(buf.data(), len, ENET_PACKET_FLAG_RELIABLE);
                enet_peer_send(gClientPeer,0,p); enet_host_flush(gClient);
                Str8 line; line+=S+"["+gClientID+"] "; line+=gChatInput; gChatLines.push_back(line);
                gChatInput.clear();
            }
        }else if(Kb.k.k==KB_BACK){
            gChatInput.removeLast();
        }else if(Kb.k.c){
            gChatInput+=Kb.k.c;
        }
        Kb.nextKey();
    }

    if(gClientID!=0xFFFF)
    {
        struct PosPkt{U8 t; U16 id; Flt x; Flt y;} pkt{PK_POS,gClientID,dot_pos.x,dot_pos.y};
        ENetPacket *p=enet_packet_create(&pkt,sizeof(pkt),0);
        enet_peer_send(gClientPeer,0,p);
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
   for(auto &kv : gPlayers) if(kv.first!=gClientID) D.dot(RED, kv.second, 0.02f);

   Flt y=-0.4; // start below other text
   int shown=0;
   for(int i=(int)gChatLines.size()-1; i>=0 && shown<8; --i,++shown)
   {
       D.text(-0.7, y, gChatLines[i]);
       y-=0.05;
   }
   D.text(-0.7, -0.75, S+">"+gChatInput);
}
/******************************************************************************/

/******************************************************************************/
