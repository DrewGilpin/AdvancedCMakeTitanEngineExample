#define ENET_IMPLEMENTATION
#include "enet.h"

#include <iostream>
#include <cstring>
#include <csignal>

static ENetHost *gServer = nullptr;
static bool keepRunning = true;

static void signalHandler(int) {
    keepRunning = false;
}

int main(int argc, char **argv)
{
    if(enet_initialize() != 0){
        std::cerr << "ENet init failed" << std::endl;
        return 1;
    }

    ENetAddress addr{};
    addr.host = ENET_HOST_ANY;
    addr.port = 12345;

    gServer = enet_host_create(&addr, 32, 2, 0, 0);
    if(!gServer){
        std::cerr << "ENet server create failed: " << std::strerror(errno) << std::endl;
        return 1;
    }

    std::cout << "Server listening on port " << addr.port << std::endl;
    std::signal(SIGINT, signalHandler);

    ENetEvent e;
    while(keepRunning){
        while(enet_host_service(gServer, &e, 100) > 0){
            switch(e.type){
                case ENET_EVENT_TYPE_CONNECT:
                    std::cout << "Client connected" << std::endl;
                    break;
                case ENET_EVENT_TYPE_RECEIVE:{
                    std::string txt((char*)e.packet->data, e.packet->dataLength);
                    std::cout << "Received: " << txt << std::endl;
                    enet_packet_destroy(e.packet);
                    break;}
                case ENET_EVENT_TYPE_DISCONNECT:
                    std::cout << "Client disconnected" << std::endl;
                    break;
                default: break;
            }
        }
    }

    enet_host_destroy(gServer);
    enet_deinitialize();
    std::cout << "Server shut down" << std::endl;
    return 0;
}
