#define ENET_IMPLEMENTATION
#include "enet.h"
#include "gtest/gtest.h"

TEST(Enet, BasicSendReceive) {
    ASSERT_EQ(enet_initialize(), 0);

    ENetAddress addr{};
    addr.host = ENET_HOST_ANY;
    addr.port = 0; // let OS choose
    ENetHost* server = enet_host_create(&addr, 1, 1, 0, 0);
    ASSERT_NE(server, nullptr);

    ENetHost* client = enet_host_create(nullptr, 1, 1, 0, 0);
    ASSERT_NE(client, nullptr);

    ENetAddress connectAddr = addr;
    enet_address_set_host(&connectAddr, "127.0.0.1");
    connectAddr.port = server->address.port;

    ENetPeer* peer = enet_host_connect(client, &connectAddr, 1, 0);
    ASSERT_NE(peer, nullptr);

    ENetEvent event;
    bool connected = false;
    for(int i=0;i<100 && !connected;i++) {
        while(enet_host_service(client, &event, 0) > 0) {
            if(event.type == ENET_EVENT_TYPE_CONNECT) {
                connected = true;
            }
        }
        while(enet_host_service(server, &event, 0) > 0) {
            // server just processes connect
        }
    }
    ASSERT_TRUE(connected);

    static const char msg[] = "ping";
    ENetPacket* p = enet_packet_create(msg, sizeof(msg), ENET_PACKET_FLAG_RELIABLE);
    enet_peer_send(peer, 0, p);
    enet_host_flush(client);

    bool received = false;
    for(int i=0;i<100 && !received;i++) {
        while(enet_host_service(server, &event, 0) > 0) {
            if(event.type == ENET_EVENT_TYPE_RECEIVE) {
                ASSERT_EQ(event.packet->dataLength, sizeof(msg));
                EXPECT_EQ(0, memcmp(event.packet->data, msg, sizeof(msg)));
                enet_packet_destroy(event.packet);
                received = true;
            }
        }
        enet_host_service(client, &event, 0);
    }
    EXPECT_TRUE(received);

    enet_host_destroy(client);
    enet_host_destroy(server);
    enet_deinitialize();
}

