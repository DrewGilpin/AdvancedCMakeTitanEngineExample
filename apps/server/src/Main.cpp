

#include <vector>
#include <cfloat>
#include <nats.h>
#include "ConnectionsToClients.h"
#include "stdafx.h"
#include "@@headers.h"
#include "MyClass.h"

Vec2 dot_pos(0, 0);
MyClass myObject("ExampleObject", 42);
static natsConnection *gNatsConn = nullptr;
/******************************************************************************/
void InitPre()
{
    // on linux the engine has been customized to make APP_ALLOW_NO_XDISPLAY force no x display/be headless
    //App.flag=APP_ALLOW_NO_XDISPLAY|APP_ALLOW_NO_GPU;
#ifdef DEBUG
    App.flag|=APP_MEM_LEAKS|APP_BREAKPOINT_ON_ERROR;
#endif
    App.flag|=APP_WORK_IN_BACKGROUND; // keep running when unfocused
    App.background_wait=0;            // no delay when in background

    App.name("Server");
    LogName("log_server.txt");
    INIT();
    LogConsole(true);
    LogN(S+"InitPre()");
}
/******************************************************************************/
bool Init()
{
    LogN(S+"Init()");
    SetupEnet();
    natsStatus s = natsConnection_ConnectTo(&gNatsConn, NATS_DEFAULT_URL);
    if(s == NATS_OK)
    {
        natsConnection_PublishString(gNatsConn, "server.started", "Hello from server");
        natsConnection_FlushTimeout(gNatsConn, 1000);
    }
    else
    {
        LogN(S+"NATS connect failed: " + natsStatus_GetText(s));
    }
    return true;
}
/******************************************************************************/
void Shut()
{
    LogN(S+"Shut()");
    if(gServer) enet_host_destroy(gServer);
    if(gNatsConn)
    {
        natsConnection_Destroy(gNatsConn);
        nats_Close();
    }
    enet_deinitialize();
}
/******************************************************************************/
bool Update()
{
    // here you have to process each frame update
    if(Kb.bp(KB_ESC))return false;

    Flt speed = 0.5f; // movement speed
    if(Kb.b(KB_LEFT )) dot_pos.x -= speed * Time.d();
    if(Kb.b(KB_RIGHT)) dot_pos.x += speed * Time.d();
    if(Kb.b(KB_UP   )) dot_pos.y += speed * Time.d();
    if(Kb.b(KB_DOWN )) dot_pos.y -= speed * Time.d();

    /* ── ENet pump ───────────────────────── */
    ServiceHost(gServer);

    // broadcast server dot position to all clients
    if(gServer && !gClients.empty())
    {
        DotPacket pkt{SERVER_ID, dot_pos.x, dot_pos.y};
        for(auto &c : gClients)
        {
            ENetPacket *p = enet_packet_create(&pkt, sizeof(pkt), ENET_PACKET_FLAG_UNSEQUENCED);
            enet_peer_send(c.peer, 0, p);
        }
        enet_host_flush(gServer);
    }

    return true;
}
/******************************************************************************/
void Draw()
{
    D.clear(BLACK);
    D.text (0, 0, "Hello to " ENGINE_NAME " Engine !");
    D.text (0, -0.1, S+ "FPS: " + Time.fps());
    D.text (0, -0.2, S+ " Arrow keys to move dot, Esc to Exit");
    D.text (0, -0.3, S+ "Clients: " + clientCount);
    D.text (0, -0.4, S+ "Packets: " + packetsRecv);
    myObject.print();
    D.dot(BLUE, dot_pos, 0.02f); // draw moving dot controlled by server
    for(const auto &c : gClients)
        D.dot(RED, c.pos, 0.02f); // draw client dots
}
/******************************************************************************/
