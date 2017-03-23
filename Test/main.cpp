#include "Application.h"
#include "Drawer.h"
#include "Keyboard.h"

class Test : public Task {
public:
	static std::string getTag( ) { return "TEST"; }
	Test( ) {
		
	}

	virtual ~Test( ) {

	}

	enum GRAPH {
		GRAPH_SAMPLE,
		GRAPH_SCREEN,
	};

	void initialize( ) {
		DrawerPtr drawer = Drawer::getTask( );
		drawer->loadGraph( GRAPH_SAMPLE, "sample.png" );
		drawer->createGraph( GRAPH_SCREEN, 1024, 1024 );
	}

	void update( ) {
		DrawerPtr drawer = Drawer::getTask( );

		{
			Drawer::Transform trans( 0, 0 );
			Drawer::Sprite sprite( trans, GRAPH_SAMPLE);
			drawer->drawSpriteToGraph( GRAPH_SCREEN, sprite );
		}

		{
			Drawer::Transform trans( 100, 0 );
			Drawer::Sprite sprite( trans, GRAPH_SCREEN);
			drawer->setSprite( sprite );
		}
	}
};

void main( ) {
	TaskPtr test = TaskPtr( new Test );
	TaskPtr drawer = TaskPtr( new Drawer( "Resource" ) );
	TaskPtr keyboard = TaskPtr( new Keyboard( ) );

	ApplicationPtr app = Application::getInstance( );
	app->addTask( Test::getTag( ), test );
	app->addTask( Drawer::getTag( ), drawer );
	app->addTask( Keyboard::getTag( ), keyboard );
}
