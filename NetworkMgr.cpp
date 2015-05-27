#include "NetworkMgr.h"

#include <RakPeerInterface.h>
#include <MessageIdentifiers.h>
#include <RakVoice.h>

#define SERVER_PORT 0
#define MAX_CLIENTS 60000


NetworkMgr::NetworkMgr()
{
	RakNet::RakPeerInterface *peer = RakNet::RakPeerInterface::GetInstance();

	RakNet::SocketDescriptor socketDscrp(SERVER_PORT,0);
	RakNet::Packet *pPacket;

	peer->Startup(MAX_CLIENTS, &socketDscrp, 1);
	peer->SetMaximumIncomingConnections(MAX_CLIENTS);

	/*RakNet::RakVoice voice;
	voice.Init(16000u, 2*16000u);*/
	

	RakNet::RakPeerInterface::DestroyInstance(peer);
}


NetworkMgr::~NetworkMgr()
{
}
