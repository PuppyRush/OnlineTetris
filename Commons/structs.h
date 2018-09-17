#pragma once

#include <string>
#include <cassert>

#include <ctime>
#include "TType.h"
//#include "TypeTraits.h"

#undef POINT



class IPString
{

public:
	IPString()
	{
		IPString({192,168,0,1});
	}

	explicit IPString(std::initializer_list<size_t> fields)
	{
		assert(fields.size() == 4);
		ip.reserve(16);
		for (size_t b : fields)
		{
			ip.append(std::to_string(static_cast<long>(b)));
			ip.append(".");
		}
		ip.pop_back();
	}

	const char* GetString() const
	{
		return ip.c_str();
	}

private:
	std::string ip;
};

typedef struct tPOINT
{
	long x;
	long y;
}tPOINT;


typedef struct FIGURE
{
	tPOINT FgInfo[4];		//*************************************DefineInfo.h�� �����Ǿ���� ����
	tPOINT end;				//���� ���ʾƷ��� ��ǥ�� �����Ѵ�.
	int Figure, NextFigure;
	int Height;
	int Width;
	int dir;
}FIGURE;

typedef struct UserInfo
{
public:
	tetris::t_unique userUnique;
	char name[10];

	UserInfo() {}
	explicit UserInfo(const tetris::t_unique userUnique, const char* name)
		:userUnique(userUnique)
	{
		assert(10 > strlen(name));
		strncpy(this->name, name, 10);
	}
}UserInfo;

typedef struct RoomInfo
{
	tetris::t_unique unique;
	time_t makeTime;
	size_t roomNumber;
	char roomName[10];
	size_t fullUserCount;
	size_t currentUserCount;

	RoomInfo() {}
	RoomInfo(const RoomInfo& other)
	{
		RoomInfo(other.unique, other.makeTime, other.roomName, other.roomNumber, other.fullUserCount, other.currentUserCount);
	}

	explicit RoomInfo(const tetris::t_unique unique, const time_t makeTime, const char* roomName
	,const size_t roomnumber, const size_t fullusercount, const size_t currentusercount)
		:unique(unique), makeTime(makeTime)
		, roomNumber(roomnumber), fullUserCount(fullusercount), currentUserCount(currentusercount)
	{
		assert(10 > strlen(roomName));
		strncpy(this->roomName, roomName, 10);
	}
}RoomInfo;
