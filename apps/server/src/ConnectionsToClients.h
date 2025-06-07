#pragma once
#include "enet.h"
#if defined(__linux__)
  #pragma push_macro("LOCK_READ")
  #pragma push_macro("LOCK_WRITE")
  #undef  LOCK_READ
  #undef  LOCK_WRITE
#endif
#include "stdafx.h"
#include "@@headers.h"
#if defined(__linux__)
  #pragma pop_macro("LOCK_WRITE")
  #pragma pop_macro("LOCK_READ")
#endif
#include "stdafx.h"
#include "@@headers.h"

struct _ENetHost; typedef _ENetHost ENetHost;
struct _ENetPeer; typedef _ENetPeer ENetPeer;

extern ENetHost *gServer;
extern Int       clientCount;
extern Int       packetsRecv;
extern const int SERVER_ID;

struct DotPacket
{
    int id;
    Flt x;
    Flt y;
};

struct ClientInfo
{
    ENetPeer *peer;
    int id;
    Vec2 pos;
};
extern std::vector<ClientInfo> gClients;

void SetupEnet();
void ServiceHost(ENetHost *host);
