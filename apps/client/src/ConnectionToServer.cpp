/******************************************************************************/
// ⚠️  ONE translation unit must *both* `#define ENET_IMPLEMENTATION` *and*
//     `#include "enet.h"` – put it right above the rest of your includes.
#define ENET_IMPLEMENTATION
#include "enet.h"          // ← Header-only ENet (third_party/enet/enet.h)

#include <unordered_map>
#include <cfloat>
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
#include "ConnectionToServer.h"
#if defined(__linux__)
  /* …and restore them so any <fcntl.h>-style users still compile. */
  #pragma pop_macro("LOCK_WRITE")
  #pragma pop_macro("LOCK_READ")
#endif
/******************************************************************************/

ENetHost *gClient      = nullptr;   // connects to the server
ENetPeer *gClientPeer  = nullptr;   // client-side handle
bool      gEnetReady   = false;     // set true once connected
int       gMyId        = -1;        // assigned by server

std::unordered_map<int, Vec2> gOtherDots; // positions of other clients

/******************************************************************************/
// Local helpers
void SetupEnet()
{
    if(enet_initialize() != 0){ LogN("ENet init failed"); return; }

    ENetAddress addr{};             // zero-initialise **all** fields
    addr.port = 12345;

    // ── create client host (no binding → will use ephemeral port) ──
    gClient = enet_host_create(nullptr, 1, 2, 0, 0);
    if(!gClient){
        LogN("ENet client create failed");
        enet_deinitialize();
        return;
    }

    // ── connect client to server on loopback ──
    enet_address_set_host(&addr, "127.0.0.1");
    gClientPeer = enet_host_connect(gClient, &addr, 2, 0);
    LogN("ENet client setup complete, waiting for connect…");
}

void ServiceHost(ENetHost *host)
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

            case ENET_EVENT_TYPE_RECEIVE:
            {
                if(e.packet->dataLength==sizeof(DotPacket))
                {
                    DotPacket pkt; CopyFast(pkt, *(DotPacket*)e.packet->data);
                    if(gMyId<0) gMyId=pkt.id; // first packet assigns ID
                    if(pkt.x==FLT_MAX && pkt.y==FLT_MAX)
                        gOtherDots.erase(pkt.id);
                    else
                        gOtherDots[pkt.id]=Vec2(pkt.x, pkt.y);
                }else{
                    Str8 txt((char8*)e.packet->data);          // UTF-8 payload
                    LogN(S + "[ENet] Got pkt (\"" + txt + "\")");
                }
                enet_packet_destroy(e.packet);
                break;
            }

            case ENET_EVENT_TYPE_DISCONNECT:
                LogN("[ENet] Peer disconnected");
            break;

            default: break;
        }
    }
}
/******************************************************************************/
