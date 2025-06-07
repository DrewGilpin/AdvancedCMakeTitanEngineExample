// clang-format off
#include "gtest/gtest.h"
#include <unordered_map>
#include <cfloat>
#include "enet.h"
#if defined(__linux__)
#pragma push_macro("LOCK_READ")
#pragma push_macro("LOCK_WRITE")
#undef LOCK_READ
#undef LOCK_WRITE
#endif
#include "stdafx.h"
#include "@@headers.h"
#if defined(__linux__)
#pragma pop_macro("LOCK_WRITE")
#pragma pop_macro("LOCK_READ")
#endif
// clang-format on

extern ENetHost *gClient;
extern ENetPeer *gClientPeer;
extern bool gEnetReady;
extern int gMyId;
extern std::unordered_map<int, Vec2> gOtherDots;

struct DotPacket {
  int id;
  Flt x;
  Flt y;
};

void ServiceHost(ENetHost *host);

TEST(ServiceHost, UpdatesDotMap) {
  ASSERT_EQ(enet_initialize(), 0);

  ENetAddress addr{};
  addr.host = ENET_HOST_ANY;
  addr.port = 0; // let OS choose
  ENetHost *server = enet_host_create(&addr, 1, 1, 0, 0);
  ASSERT_NE(server, nullptr);

  gClient = enet_host_create(nullptr, 1, 1, 0, 0);
  ASSERT_NE(gClient, nullptr);

  ENetAddress connectAddr = addr;
  enet_address_set_host(&connectAddr, "127.0.0.1");
  connectAddr.port = server->address.port;

  gClientPeer = enet_host_connect(gClient, &connectAddr, 1, 0);
  ASSERT_NE(gClientPeer, nullptr);

  ENetEvent event;
  gEnetReady = false;
  gMyId = -1;
  gOtherDots.clear();

  for (int i = 0; i < 100 && !gEnetReady; i++) {
    ServiceHost(gClient);
    while (enet_host_service(server, &event, 0) > 0) {
    }
  }
  ASSERT_TRUE(gEnetReady);

  DotPacket pkt{42, 1.0f, 2.0f};
  ENetPacket *p =
      enet_packet_create(&pkt, sizeof(pkt), ENET_PACKET_FLAG_RELIABLE);
  enet_host_broadcast(server, 0, p);
  enet_host_flush(server);

  bool received = false;
  for (int i = 0; i < 100 && !received; i++) {
    ServiceHost(gClient);
    while (enet_host_service(server, &event, 0) > 0) {
    }
    if (gOtherDots.find(42) != gOtherDots.end())
      received = true;
  }
  ASSERT_TRUE(received);
  auto it = gOtherDots.find(42);
  ASSERT_NE(it, gOtherDots.end());
  EXPECT_FLOAT_EQ(it->second.x, 1.0f);
  EXPECT_FLOAT_EQ(it->second.y, 2.0f);
  EXPECT_EQ(gMyId, 42);

  DotPacket rem{42, FLT_MAX, FLT_MAX};
  ENetPacket *p2 =
      enet_packet_create(&rem, sizeof(rem), ENET_PACKET_FLAG_RELIABLE);
  enet_host_broadcast(server, 0, p2);
  enet_host_flush(server);

  for (int i = 0; i < 100 && gOtherDots.find(42) != gOtherDots.end(); i++) {
    ServiceHost(gClient);
    while (enet_host_service(server, &event, 0) > 0) {
    }
  }
  EXPECT_EQ(gOtherDots.count(42), 0u);

  enet_peer_disconnect(gClientPeer, 0);
  for (int i = 0; i < 10; i++) {
    ServiceHost(gClient);
    while (enet_host_service(server, &event, 0) > 0) {
    }
  }

  enet_host_destroy(gClient);
  enet_host_destroy(server);
  enet_deinitialize();
}
