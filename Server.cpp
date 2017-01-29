#include "Server.h"
#include "Application.h"
#include "Network.h"

const int SETTING_NUM = 10;
const int PLAYER_START_HP = 1000;

ServerPtr Server::getTask( ) {
	ApplicationPtr fw = Application::getInstance( );
	return std::dynamic_pointer_cast< Server >( fw->getTask( Server::getTag( ) ) );
}

Server::Server( ) {
	for ( int i = 0; i < MAX_MACHINE; i++ ) {
		_machine[ i ] = -1;
	}
	_network_state_time = 0;
	_send_network_condition_num = 0;

	PreparationListenNetWork( TCP_PORT_NUM );
	_udp_handle = MakeUDPSocket( -1 );

	for ( int i = 0; i < PLAYER_NUM; i++ ) {
		_data.player[ i ].hp = PLAYER_START_HP;
		_data.player[ i ].x = 0;
		_data.player[ i ].y = 0;
		_data.player[ i ].action = ACTION_NONE;
	}
}

Server::~Server( ) {
	DeleteUDPSocket( _udp_handle );
	StopListenNetWork( );
}

void Server::update( ) {
	listenForAcceptNewClient( );
	listenForPackets( );
	updateData( );
	sendCondition( );
}

std::string Server::getMachineIPStr( int index ) {
	std::string str;
	if ( _machine[ index ] >= 0 ) {
		IPDATA ip;
		GetNetWorkIP( _machine[ index ], &ip );
		str += std::to_string( ( _ULonglong  )ip.d1 );
		str += ".";
		str += std::to_string( ( _ULonglong )ip.d2 );
		str += ".";
		str += std::to_string( ( _ULonglong )ip.d3 );
		str += ".";
		str += std::to_string( ( _ULonglong )ip.d4 );
	}
	return str;
}

void Server::listenForAcceptNewClient( ) {
	int handle = GetNewAcceptNetWork( );
	if ( handle == -1 ) {
		return;
	}
	
	for ( int i = 0; i < MAX_MACHINE; i++ ) {
		if ( _machine[ i ] == -1 ) {
			_machine[ i ] = handle;
			break;
		}
	}
}

void Server::listenForPackets( ) {
	int handle = GetLostNetWork( );
	for ( int i = 0; i < MAX_MACHINE; i++ ) {
		if ( _machine[ i ] == -1 ) {
			continue;
		}

		if ( handle == _machine[ i ] ) {
			CloseNetWork( _machine[ i ] );
			_machine[ i ] = -1;
			continue;
		}

		if ( GetNetWorkDataLength( _machine[ i ] ) <= 0 ) {
			continue;
		}

		// ��M
		SERVERDATA data;
		if ( NetWorkRecv( _machine[ i ], &data, sizeof( data ) ) == 0 ) {
			// �f�[�^�ɂ��킹�ď���
			executeNetData( data );
		}
	}
}

void Server::executeNetData( const SERVERDATA& data ) {
	switch ( data.command ) {
	case COMMAND_DUMMY:
		break;
	case COMMAND_CONDITION:
		break;
	}
}

void Server::saveIP( ) {
	IPDATA data;
	GetMyIPAddress( &data );

	FILE* fp;
	fopen_s( &fp, "IP.ini", "wb" );
	fwrite( &data, sizeof( IPDATA ), 1, fp );
	fclose( fp );
}

void Server::sendStatus( const CLIENTDATA& data ) {
	for ( int i = 0; i < MAX_MACHINE; i++ ) {
		if ( _machine[ i ] < 0 ) {
			continue;
		}
		IPDATA ip;
		GetNetWorkIP( _machine[ i ], &ip );
		_data.player[ i ].x = data.player[ i ].x;
		_data.player[ i ].y = data.player[ i ].y;
		_data.player[ i ].action = data.player[ i ].action;

		NetWorkSendUDP( _udp_handle, ip, UDP_PORT_NUM, &_data, sizeof( CLIENTDATA ) ) ;
	}
}

void Server::sendCondition( ) {
	// ��莞��
	_network_state_time++;
	if ( _network_state_time < NETWORK_STATE_TIME ) {
		return;
	}
	_network_state_time = 0;

	// ���M
	for ( int i = 0; i < MAX_MACHINE; i++ ) {
		if ( _machine[ i ] < 0 ) {
			continue;
		}

		SERVERDATA data;
		data.command = COMMAND_CONDITION;
		if ( NetWorkSend( _machine[ i ], &data, sizeof( SERVERDATA ) ) < 0 ) {
			CloseNetWork( _machine[ i ] );
			_machine[ i ] = -1;
		}
	}
}

CLIENTDATA Server::getData( ) {
	return _data;
}


void Server::updateData( ) {
	
}