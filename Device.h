#pragma once

#include "Task.h"
#include <array>

const int MAX_JOYPAD_USE_NUM = 16;

PTR( Device );

class Device : public Task {
public:
	static std::string getTag( ) { return "DEVICE"; }
	static DevicePtr getTask( );
public:
	Device( );
	virtual ~Device( );
public:
	void initialize( );
	virtual void update( );
public:
	char getDirX( int idx = 0 ) const;
	char getDirY( int idx = 0 ) const;
	unsigned char getButton( int idx = 0 ) const;
public:
	void resetup( );
private:
	struct DATA {
		char x;
		char y;
		unsigned char button;
	};
private:
	std::array< DATA, MAX_JOYPAD_USE_NUM > _data;
	int _num;
};