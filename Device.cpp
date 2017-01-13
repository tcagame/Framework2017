#include "Device.h"
#include "mathmatics.h"
#include "Application.h"
#include "DxLib.h"

const int JOYPADKEY[ MAX_JOYPAD_USE_NUM ] = {
	DX_INPUT_KEY_PAD1,
	DX_INPUT_PAD2,
	DX_INPUT_PAD3,
	DX_INPUT_PAD4,
	DX_INPUT_PAD5,
	DX_INPUT_PAD6,
	DX_INPUT_PAD7,
	DX_INPUT_PAD8,
	DX_INPUT_PAD9,
	DX_INPUT_PAD10,
	DX_INPUT_PAD11,
	DX_INPUT_PAD12,
	DX_INPUT_PAD13,
	DX_INPUT_PAD14,
	DX_INPUT_PAD15,
	DX_INPUT_PAD16,
};

DevicePtr Device::getTask( ) {
	ApplicationPtr fw = Application::getInstance( );
	return std::dynamic_pointer_cast< Device >( fw->getTask( Device::getTag( ) ) );
}


Device::Device( ) {
}

void Device::initialize( ) {
	for ( int i = 0; i < MAX_JOYPAD_USE_NUM; i++ ) {
		_data[ i ].x = 0;
		_data[ i ].y = 0;
		_data[ i ].button = 0;
	}

	resetup( );
}

Device::~Device( ) {
}

void Device::resetup( ) {
	ReSetupJoypad( );
	_num = GetJoypadNum( );
	if ( _num < 1 ) {
		_num = 1; // キーボード対応
	}
}

char Device::getDirX( int idx ) const {
	return _data[ idx ].x;
}

char Device::getDirY( int idx ) const {
	return _data[ idx ].y;
}

unsigned char Device::getButton( int idx ) const {
	return _data[ idx ].button;
}

void Device::update( ) {
	for ( int i = 0; i < _num; i++ ) {
		int key = GetJoypadInputState( JOYPADKEY[ i ] );
		Vector vec;
		int x = 0, y = 0;
		GetJoypadAnalogInput( &x, &y, JOYPADKEY[ i ] );
		vec.x = x;
		vec.y = y;
		vec.x += +( ( key & PAD_INPUT_RIGHT ) != 0 );
		vec.x += -( ( key & PAD_INPUT_LEFT  ) != 0 );
		vec.y += +( ( key & PAD_INPUT_DOWN  ) != 0 );
		vec.y += -( ( key & PAD_INPUT_UP    ) != 0 );
		vec = vec.normalize( ) * 100;

		_data[ i ].x = ( char )vec.x;
		_data[ i ].y = ( char )vec.y;

		_data[ i ].button = 0;
		if ( ( key & PAD_INPUT_A ) != 0 ) { 
			_data[ i ].button |= BUTTON_A;
		}
		if ( ( key & PAD_INPUT_B ) != 0 ) { 
			_data[ i ].button |= BUTTON_B;
		}
		if ( ( key & PAD_INPUT_C ) != 0 ) { 
			_data[ i ].button |= BUTTON_C;
		}
		if ( ( key & PAD_INPUT_X ) != 0 ) { 
			_data[ i ].button |= BUTTON_D;
		}
	}
}
