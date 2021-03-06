#pragma once

#include "../../Commons/DefineInfo.h"
#include "../../Commons/TSocket.h"
#include "../../Commons/TType.h"

class TSocketImpl : public TetrisSocket
{
public:
	virtual ~TSocketImpl() {}

	virtual unsigned create(IPString ip, tetris::t_port port) { return 0; }
	virtual int listen(const unsigned port, int backlog) override;

protected:

	TSocketImpl() = delete;
	explicit TSocketImpl(const int domain, const int type, const int protocol, const IPString ip, const tetris::t_port port);
	explicit TSocketImpl(const int domain, const int type, const int protocol, tetris::t_socket socket);

	virtual volatile int _accept() override;
	virtual int _close(const unsigned _socket) override;
	virtual tetris::t_error _connect() override { return 0; };

	virtual const size_t _sendTo(const char *msg, const size_t size) override;
	virtual tetris::msgElement _recvFrom() override;
};
