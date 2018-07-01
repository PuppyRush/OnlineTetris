/*
 * TGameRoom.h
 *
 *  Created on: May 8, 2018
 *      Author: pi
 */

#pragma once

#include <unordered_map>
#include <mutex>

#include "TRoom.h"
#include "../../Commons/TType.h"
#include "../../Commons/TAtomic.h"

class TGameRoom : public TRoom
{
public:

	enum class errorCode : std::uint16_t
	{
		Ok,
		Duplicated = 0,
		NameLength,
		PassedTime,
		Nobody
	};

	enum class property : std::uint16_t
	{
		Size = 8
	};

	TGameRoom() {}
	explicit TGameRoom(const std::string roomname, const std::vector<std::shared_ptr<TServerUser>> userQ);
	virtual ~TGameRoom();

	inline static std::shared_ptr<TGameRoom> getRameRoom()
	{
		static auto waitingRoom = std::make_shared<TGameRoom>();
		return waitingRoom;
	}

	const errorCode insertRoom(std::shared_ptr<TGameRoom> room);

private:
	TAtomic<tetris::t_roomUnique> m_unique;
	std::unordered_map< tetris::t_roomUnique, std::shared_ptr<TGameRoom>> m_roomMap;
	const errorCode _validator(const TRoom &room) const;

};