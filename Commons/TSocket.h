#pragma once

#include <functional>
#include <string>
#include <queue>
#include <cstdint>
#include <thread>
#include <mutex>
#include <limits>
//#include <assert.h>

#include "DefineInfo.h"
#include "Logger.h"
#include "MessageHeader.h"
#include "TType.h"
#include "TypeTraits.h"

#undef min
#undef max

using namespace std;


class TetrisSocket
{
public:

	struct msgComp
	{
		bool operator()(tetris::msgElement &lhs, tetris::msgElement &rhs)
		{
			return msgHelper::getPriority(lhs) > msgHelper::getPriority(rhs);
		}
	};

	virtual ~TetrisSocket();

	virtual unsigned create(IPString ip, tetris::t_port port) = 0;
	virtual int listen(unsigned port, int backlog) = 0;

	static char* getBuffer();

	template <class T>
	inline	void pushMessage(T *msg)
	{
		const size_t len = sizeof(T);
		assert(PACKET_LEN > len);

		char *dest = getBuffer();
		memcpy(dest, msg, PACKET_LEN);

		tetris::t_priority priority = msg->priority;

		const auto val = make_tuple(priority, static_cast<const char*>(dest), len);
		m_sendQ.emplace(val);
	}
	inline unsigned popSocket()
	{
		while(true)
		{
			if(!m_acceptedSocketQ.empty())
			{
				const unsigned socket = m_acceptedSocketQ.front();
				m_acceptedSocketQ.pop();
				return socket;
			}
		}
	}

	unsigned connect();
	int accept();
	void send();
	void recv();
	unsigned close();

	void SetIP(IPString &ip);
	void SetPort(tetris::t_port port);

protected:
	const int m_domain;
	const int m_type;
	const int m_protocol;
	IPString m_ip;
	tetris::t_port m_port;

	queue<unsigned> m_acceptedSocketQ;
	bool m_closeSocket;

	TetrisSocket() = delete;
	explicit TetrisSocket(const int domain, const int type, const int protocol, const IPString ip, const tetris::t_port port);
	explicit TetrisSocket(const int domain, const int type, const int protocol, tetris::t_socket socket);

	virtual int _accept() = 0;
	virtual unsigned _connect() = 0;
	virtual int _close(const unsigned _socket) = 0;
	virtual const size_t _sendTo(const char *msg,const size_t size) = 0;
	virtual tetris::msgElement _recvFrom() = 0;

	void _acceptSocket();


	inline void setSocket(tetris::t_socket socket) { m_socket = socket;	}
	inline const tetris::t_socket getSocket() {	return m_socket;}

private:
	tetris::t_socket m_socket;

	shared_ptr<thread> m_acceptThread;

	priority_queue<tetris::msgElement,vector<tetris::msgElement>,msgComp> m_recvQ;
	priority_queue<tetris::msgElement,vector<tetris::msgElement>,msgComp> m_sendQ;
	
	void _runAcception();
	void _end();
};
