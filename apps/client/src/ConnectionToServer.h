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

struct _ENetHost; typedef _ENetHost ENetHost;
struct _ENetPeer; typedef _ENetPeer ENetPeer;

extern ENetHost *gClient;
extern ENetPeer *gClientPeer;
extern bool      gEnetReady;
extern int       gMyId;
extern std::unordered_map<int, Vec2> gOtherDots;

struct DotPacket
{
    int id;
    Flt x;
    Flt y;
};

void SetupEnet();
void ServiceHost(ENetHost *host);
