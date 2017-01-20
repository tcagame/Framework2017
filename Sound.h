#pragma once

#include "Task.h"
#include "smart_ptr.h"
#include <array>
#include <string>

PTR( Sound );

class Sound : public Task {
public:
	static std::string getTag( ) { return "SOUND"; }
	static SoundPtr getTask( );
public:
	Sound( const char* directory );
	virtual ~Sound( );
public:
	void initialize( );
	void finalize( );
public:
	void update( );
	void playSE( const char * filename );
	void playBGM( const char * filename );
private:
	const char* _directory;
};

