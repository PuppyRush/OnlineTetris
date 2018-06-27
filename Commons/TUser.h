#pragma once

#include <memory>

#include "structs.h"
#include "TSocket.h"
#include "TType.h"
#include "TAtomic.h"

#undef GetUserName

class TetrisUser : private uncopyable
{
public:
	int GameBoard[25][10], FixedBoard[25][10], NextFigureBoard[4][2];
	int StateBoard[25][10];
	FIGURE FG;
	FIGURE GhostFG;

	inline bool operator< (const TetrisUser &user)
	{
		return this->m_order < user.getOrder();
	}

	inline const string getUserName() const { return m_name; }
	inline const bool getReady() const { return m_isReady; }
	inline const int getOrder() const { return m_order; }
	inline const bool getSurvive() const { return m_isSurvive; }
	inline const tetris::t_userUnique getUnique() const noexcept { return m_unique; }

	inline void setSurvive(const bool n) { m_isSurvive = n; }
	inline void setOrder(const int idx) { m_order = idx; }
	inline void setName(const string name) { m_name = name; }
	inline void setReady(const bool rdy) { m_isReady = rdy; }

protected:
	explicit TetrisUser(const tetris::t_userUnique unique, const string &name);
	explicit TetrisUser(const tetris::t_userUnique unique, const string &name, const IPString &ip, const int idx);

	TetrisUser();
	virtual ~TetrisUser() { }

private:
	tetris::t_userUnique m_unique;
	int m_order;
	string m_name;
	IPString m_ip;
	bool m_isReady;
	bool m_isSurvive;
};
