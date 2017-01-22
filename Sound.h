#pragma once

#include "Task.h"
#include "smart_ptr.h"
#include <map>
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
	void playSE( std::string filename, bool loop = false );
	void stopSE( std::string filename );
	void playBGM( std::string filename );
private:
	const char* _directory;
	std::map< std::string, int > _se;
};

