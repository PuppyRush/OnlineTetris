/*
 * TetrisUserServer.cpp
 *
 *  Created on: May 8, 2018
 *      Author: pi
 */

#include <string>
#include <sys/socket.h>

#include "../../Commons/MessageHeader.h"
#include "../../Commons/TSocket.h"
#include "TServerUser.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

TServerUser::TServerUser(const tetris::t_userUnique unique, const std::shared_ptr<TServerSocket> socket)
	:TetrisUser(unique),
	m_serverSocket(socket),
	m_sharedPtr(std::shared_ptr<TServerUser>(this))
{
}

TServerUser::TServerUser(TServerUser* user)
	:TetrisUser(user->getUnique())
{
}

TServerUser::~TServerUser()
{
	// TODO Auto-generated destructor stub
}

const tetris::t_error TServerUser::registryMessage()
{

}

/*
const tetris::t_error TServerUser::switchingMessage(const tetris::msgElement &msg)
{
	auto realMsg = msgHelper::getMessage(msg);
	auto msgidx = Header::getMsgidx(realMsg)
	switch(msgidx)
	{
	case toUType(SERVER_MSG::ON_CONNECTION_INFO):

		break;

	}

}
*/
