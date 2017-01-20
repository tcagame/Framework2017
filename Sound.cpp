#include "Sound.h"
#include "Application.h"
#include "Dxlib.h"
#include <string>

SoundPtr Sound::getTask( ) {
	ApplicationPtr fw = Application::getInstance( );
	return std::dynamic_pointer_cast< Sound >( fw->getTask( Sound::getTag( ) ) );
}

Sound::Sound( const char * directory ) :
_directory( directory ){
}

void Sound::initialize( ) {
	//‚r‚d
}

void Sound::finalize( ) {
}

Sound::~Sound( ) {
	
}

void Sound::update( ) {
}

void Sound::playSE( const char * filename ) {
}

void Sound::playBGM( const char * filename ) {
	// ‘O‰ñ‚Ì‚a‚f‚l‚ğíœ
	StopMusic( );

	// V‚µ‚¢‚a‚f‚l‚ğÄ¶
	std::string path = _directory;
	path += "/";
	path +=  filename;
	if ( PlayMusic( path.c_str( ), DX_PLAYTYPE_LOOP ) != 0 ) {
		path = "../" + path;
		PlayMusic( path.c_str( ), DX_PLAYTYPE_LOOP );
	}
}
