/******************************************************************************/
// ⚠️  ONE translation unit must *both* `#define ENET_IMPLEMENTATION` *and*
//     `#include "enet.h"` – put it right above the rest of your includes.
#define ENET_IMPLEMENTATION
#include "enet.h"          // ← Header-only ENet (third_party/enet/enet.h)

#include <vector>
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
#include "ConnectionsToClients.h"
#if defined(__linux__)
  /* …and restore them so any <fcntl.h>-style users still compile. */
  #pragma pop_macro("LOCK_WRITE")
  #pragma pop_macro("LOCK_READ")
#endif
/******************************************************************************/

ENetHost *gServer      = nullptr;   // listens on 127.0.0.1:12345
Int       clientCount  = 0;
Int       packetsRecv  = 0;
const int SERVER_ID    = 0;         // ID used when sending server state

std::vector<ClientInfo> gClients;
static int gNextId = 1;
/******************************************************************************/
// Local helpers
void SetupEnet()
{
    if(enet_initialize() != 0){ LogN("ENet init failed"); return; }

    ENetAddress addr{};             // zero-initialise **all** fields
    addr.port = 12345;
    addr.host = ENET_HOST_ANY;      // or enet_address_set_host_ip(&addr, "::")

    gServer = enet_host_create(&addr, 32, 2, 0, 0);

    if(!gServer){
        LogN(S+"ENet server create failed.");
        LogN(S+"ENet server create failed error: " + strerror(errno));
        enet_deinitialize();
        return;
    }

    LogN("ENet server setup complete, waiting for clients...");
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
            {
                LogN(S+"[ENet] Peer connected, ch:" + int(e.channelID));
                ClientInfo ci; ci.peer=e.peer; ci.id=gNextId++; ci.pos=Vec2(0,0);
                gClients.push_back(ci);
                e.peer->data=(Ptr)(intptr_t)ci.id;
                // shorten timeouts so dropped clients are detected quickly
                enet_peer_timeout(e.peer, 2, 1000, 2000);
                ++clientCount;

                // notify existing clients about new one
                DotPacket pkt{ci.id, ci.pos.x, ci.pos.y};
                for(auto &c:gClients){
                    ENetPacket *p=enet_packet_create(&pkt,sizeof(pkt),ENET_PACKET_FLAG_RELIABLE);
                    enet_peer_send(c.peer,0,p);
                }
                enet_host_flush(host);

                // send all other clients to the new one
                for(auto &c:gClients){
                    if(c.id==ci.id) continue;
                    DotPacket p2{c.id,c.pos.x,c.pos.y};
                    ENetPacket *pkt2=enet_packet_create(&p2,sizeof(p2),ENET_PACKET_FLAG_RELIABLE);
                    enet_peer_send(ci.peer,0,pkt2);
                }
                // also send server position
                {
                    DotPacket srv{SERVER_ID, dot_pos.x, dot_pos.y};
                    ENetPacket *pkt2=enet_packet_create(&srv,sizeof(srv),ENET_PACKET_FLAG_RELIABLE);
                    enet_peer_send(ci.peer,0,pkt2);
                    enet_host_flush(host);
                }
                enet_host_flush(host);
            }break;

            case ENET_EVENT_TYPE_RECEIVE:
            {
                if(e.packet->dataLength==sizeof(DotPacket))
                {
                    DotPacket pkt; CopyFast(pkt, *(DotPacket*)e.packet->data);
                    int id=(int)(intptr_t)e.peer->data; pkt.id=id;
                    for(auto &c:gClients) if(c.id==id){c.pos.set(pkt.x,pkt.y);break;}
                    for(auto &c:gClients){
                        ENetPacket *p=enet_packet_create(&pkt,sizeof(pkt),ENET_PACKET_FLAG_UNSEQUENCED);
                        enet_peer_send(c.peer,0,p);
                    }
                    enet_host_flush(host);
                    ++packetsRecv;
                }else{
                    Str8 txt((char8*)e.packet->data);          // UTF-8 payload
                    LogN(S + "[ENet] Got pkt (\"" + txt + "\")");
                }
                enet_packet_destroy(e.packet);
                break;
            }

            case ENET_EVENT_TYPE_DISCONNECT:
            {
                LogN("[ENet] Peer disconnected");
                int id=(int)(intptr_t)e.peer->data;
                for(auto it=gClients.begin(); it!=gClients.end(); ++it) if(it->id==id){ gClients.erase(it); break; }
                DotPacket pkt{id, FLT_MAX, FLT_MAX};
                for(auto &c:gClients){
                    ENetPacket *p=enet_packet_create(&pkt,sizeof(pkt),ENET_PACKET_FLAG_RELIABLE);
                    enet_peer_send(c.peer,0,p);
                }
                enet_host_flush(host);
                --clientCount;
            }break;

            default: break;
        }
    }
}
/******************************************************************************/
