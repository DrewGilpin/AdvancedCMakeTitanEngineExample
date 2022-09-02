/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Titan Engine (https://esenthel.com) header file.                           *
/******************************************************************************

   Use 'Socket' to communicate with external devices through the internet.

/******************************************************************************/
#define NULL_SOCKET -1
/******************************************************************************/
struct SockAddr // Socket Address
{
   // get/set single value
   Bool valid     ()C; // if address is valid
   Bool thisDevice()C; // if address points to this device using a local address (but not global)

   Int  port   ()C;   SockAddr& port   (Int     port); // get/set port
   UInt ip4    ()C;   SockAddr& ip4    (UInt    ip4 ); // get/set IPv4
   Str8 ip4Text()C;   Bool      ip4Text(C Str8 &ip4 ); // get/set IPv4 in text format
   Str8 ip6Text()C;   Bool      ip6Text(C Str8 &ip6 ); // get/set IPv6 in text format
   Str8 ipText ()C;   Bool      ipText (C Str8 &ip  ); // get/set IP   in text format

   // set
   SockAddr& clear       (                      ); // clear address to zero
   Bool      setFromLocal(C Socket &socket      ); // set   address from socket local                   address
   Bool      setFromDest (C Socket &socket      ); // set   address from socket target/destination/peer address
   SockAddr& setServer   (              Int port); // set   address to be used for creating a server
   SockAddr& setLocalFast(              Int port); // set   address to local host     (  fast "127.0.0.1"     IP will be used), this allows connections only within the same device
   SockAddr& setLocal    (              Int port); // set   address to local host     ( local                 IP will be used), this allows connections only within the same device and local network (connecting beyond local network depends if the local host is behind a router)
   Bool      setGlobal   (              Int port); // set   address to local host     (global/public/external IP will be used), this allows connections      within the same device,    local network and beyond (resolving global IP address requires connecting to external websites !!)
   SockAddr& setBroadcast(              Int port); // set   address to broadcast mode ("255.255.255.255"      IP will be used), this allows sending to all computers in local network, this is IPv4 only and does not support IPv6
   Bool      setHost     (C Str  &host, Int port); // set   address to host from its name, false on fail
   SockAddr& setIp4Port  (  UInt  ip4 , Int port); // set   address to direct IPv4 address                with specified port
   Bool      setIp4Port  (C Str8 &ip4 , Int port); // set   address to direct IPv4 address in text format with specified port, false on fail
   Bool      setIp6Port  (C Str8 &ip6 , Int port); // set   address to direct IPv6 address in text format with specified port, false on fail
   Bool      setIpPort   (C Str8 &ip  , Int port); // set   address to direct IP   address in text format with specified port, false on fail

   Bool setFtp (C Str &host) {return setHost(host, 21);}
   Bool setHttp(C Str &host) {return setHost(host, 80);}

   // conversions
   Str    asText(               )C; // get address as   text
   Bool fromText(C Str8 &ip_port) ; // set address from text, false on fail

   // io
   Bool save(File &f)C; // save address to   file, false on fail
   Bool load(File &f) ; // load address from file, false on fail

   SockAddr() {clear();}

private:
   UInt _data[7];
};
// compare
       Int  CompareIgnorePort(C SockAddr &a, C SockAddr &b);                           // compare and ignore port
       Int  Compare          (C SockAddr &a, C SockAddr &b);                           // compare
inline Bool operator==       (C SockAddr &a, C SockAddr &b) {return Compare(a, b)==0;} // if     equal
inline Bool operator!=       (C SockAddr &a, C SockAddr &b) {return Compare(a, b)!=0;} // if not equal
/******************************************************************************/
struct Socket
{
   enum RESULT
   {
      FAILED     , // couldn't connect
      CONNECTED  , // connected successfully
      IN_PROGRESS, // still connecting, you can verify the connection state at a later time using 'connectFailed' method
   };

   // manage
   void del      (); // delete
   Bool createTcp(Bool ipv6); // create Tcp socket, 'ipv6'=if create in IPv6 mode (IPv4 otherwise), false on fail, TCP protocol description: data is     guaranteed to reach the target, data is     always received in the same order as it was sent, sending multiple small packets may   result  in groupping them together and sending as one big packet
   Bool createUdp(Bool ipv6); // create Udp socket, 'ipv6'=if create in IPv6 mode (IPv4 otherwise), false on fail, UDP protocol description: data is not guaranteed to reach the target, data is not always received in the same order as it was sent, sending multiple small packets never results in groupping them together and sending as one big packet
   Bool createTcp(C SockAddr &addr); // this method will call 'createTcp(Bool ipv6)' with 'ipv6' parameter set based on specified 'addr' address and Dual-Stack Socket availability in the Operating System
   Bool createUdp(C SockAddr &addr); // this method will call 'createUdp(Bool ipv6)' with 'ipv6' parameter set based on specified 'addr' address and Dual-Stack Socket availability in the Operating System

   // get
   Bool     is       ()C {return _s!=NULL_SOCKET;} // if  socket is valid
   Int      portLocal()C;                          // get socket local                   port
   Int      portDest ()C;                          // get socket target/destination/peer port
   SockAddr addrLocal()C;                          // get socket local                   address
   SockAddr addrDest ()C;                          // get socket target/destination/peer address

   // set
   Bool block     (Bool on); // set blocking mode      , false on fail
   Bool tcpNoDelay(Bool on); // set TCP_NODELAY  option, false on fail
   Bool broadcast (Bool on); // set SO_BROADCAST option, false on fail !! only UDP sockets are supported !! this allows sending data to all computers in local network by using 'SockAddr.setBroadcast' as 'send' address

   // operations
   Bool   bind   (C SockAddr &addr                ); // bind    socket to specific address, false on fail
   RESULT connect(C SockAddr &addr, Int timeout=-1); // connect socket to specific address, 'timeout'=how long (in milliseconds) to wait for a connection (<0 use default value specified by the OS, for >=0 values the socket will automatically be converted into non-blocking mode)
   Bool   connectFailed(                          ); // you can use this method after getting IN_PROGRESS result from 'connect' method to test if the connection attempt has failed

   Bool listen(                                  ); // start  listening for incoming connections  , false on fail
   Bool accept(Socket &connection, SockAddr &addr); // accept incomming connection and its address, false on fail, upon success 'connection' and 'addr' will be set according to the incomming connection properties

   // io
   Int send   (                  CPtr data, Int size); // send    'data'                           , returns the size of sent     data (                    -1 on fail            )
   Int receive(                   Ptr data, Int size); // receive 'data'                           , returns the size of received data (0 on disconnection, -1 if no data awaiting)
   Int send   (C SockAddr &addr, CPtr data, Int size); // send    'data' to   'addr' socket address, returns the size of sent     data (                    -1 on fail            ), this method is available only for UDP sockets
   Int receive(  SockAddr &addr,  Ptr data, Int size); // receive 'data' from 'addr' socket address, returns the size of received data (0 on disconnection, -1 if no data awaiting), this method is available only for UDP sockets, if any data was received then 'addr' will be set to the address of the sender

   Bool wait (Int time); // wait 'time' milliseconds for data arrival                  , false on timeout
   Bool flush(Int time); // wait 'time' milliseconds until the data has been sent fully, false on timeout
   Bool any  (Int time); // wait 'time' milliseconds for any 'wait' or 'flush' event   , false on timeout

   Int available()C; // get number of bytes available for reading, -1 on fail

   Socket() {}
  ~Socket() {del();}

private:
#if WINDOWS
   UIntPtr _s=NULL_SOCKET;
#else
   Int _s=NULL_SOCKET;
#endif
   NO_COPY_CONSTRUCTOR(Socket);
};
/******************************************************************************/
struct SecureSocket : Socket
{
   enum RESULT
   {
      OK        = 0, // handshake succeeded (returned only for 'handshake')
      ERROR     =-1, // !! -1 is reserved due to system Socket.send/receive error and can't be changed !!
      NEED_WAIT =-2,
      NEED_FLUSH=-3,
      BAD_CERT  =-4, // bad certificate (returned only for 'handshake')
   };

   void del();
   void unsecure();
   Bool   secure(CChar8 *host);
   void setDefaultFunc();
   RESULT handshake();

   Int send   (CPtr data, Int size); // can return RESULT (ERROR as in 'Socket', and NEED_WAIT, NEED_FLUSH)
   Int receive( Ptr data, Int size); // can return RESULT (ERROR as in 'Socket', and NEED_WAIT, NEED_FLUSH)

   SecureSocket() {}
  ~SecureSocket() {unsecure();}

private:
   Ptr _secure=null;
   NO_COPY_CONSTRUCTOR(SecureSocket);
};
/******************************************************************************/
ULong GetMac(); // get MAC address of current device

C Str& GetComputerName(); // get name of this computer which can be used in 'GetHostAddresses' function

void GetLocalAddresses(MemPtr<SockAddr> addresses,              Int port=0); // get a list of all known addresses for local     host
void GetHostAddresses (MemPtr<SockAddr> addresses, C Str &host, Int port=0); // get a list of all known addresses for specified host

void       GetGlobalIP(Bool refresh=false); // initiate        obtaining global IP address in the background, 'refresh'=if ignore previously obtained IP address and try getting a new one in case it was changed
Bool       HasGlobalIP(                  ); // if successfully obtained  global IP address
Bool ObtainingGlobalIP(                  ); // if currently    obtaining global IP address

Bool SendMailSupported(); // check if 'SendMail' function is supported on this machine, this function should not be called before 'InitPre'
Bool SendMail(C Str &from_name, C Str &from_email, C Str &to_name, C Str &to_email, C Str &subject, C Str &message); // send e-mail using local host as SMTP server, 'from_name'=name of the sender (example "John Smith"), 'from_email'=sender e-mail address (example "user@domain.com"), 'to_name'=name of the recipent (example "Jane Smith"), 'to'=recipent e-mail address (example "user@domain.com"), 'subject'=subject, 'message'=e-mail message

Bool HandleNetworkError(); // this is needed for Nintendo Switch, if you encounter a network connection error, call this function to display system error message and try to reconnect to the internet. Returns true if message was displayed (on Nintendo Switch), and false if no action was performed (on other platforms).
Bool NetworkServiceAccountIDToken(CPtr &data, Int &size); // this is needed for Nintendo Switch, this function tries to get "Nintendo Network Service Account ID Token". On success returns true and sets 'data'=token data (doesn't need to be released), 'size'=token size in bytes, on fail returns false and sets 'data'=null, 'size'=0. This function must be called before using any network functions (connecting to any servers/other players). You can proceed with connection only if it returns true, if it returns false then you may not proceed with connections as per Nintendo guidelines. This function will always fail if Nintendo OMAS was not yet configured and approved.
/******************************************************************************/
