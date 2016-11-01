#include "Application.h"
#include "Drawer.h"

class Test : public Task {
public:
	static std::string getTag( ) { return "TEST"; }
	Test( ) {
		
	}

	virtual ~Test( ) {

	}

	void initialize( ) {
		DrawerPtr drawer = Drawer::getTask( );
		drawer->loadGraph( 0, "Yokai_OBJ_myCharacter.png" );
	}

	void update( ) {
		DrawerPtr drawer = Drawer::getTask( );

		Drawer::Transform trans;
		trans.sx = 0;
		trans.sy = 0;
		trans.sx2 = 32;
		trans.sy2 = 32;
		trans.tx = 0;
		trans.ty = 0;
		trans.tw = 32;
		trans.th = 32;

		Drawer::Sprite sprite;
		sprite.blend = Drawer::BLEND_NONE;
		sprite.res = 0;
		sprite.trans = trans;

		drawer->setSprite( sprite );
	}
};

void main( ) {
	TaskPtr test = TaskPtr( new Test );
	TaskPtr drawer = TaskPtr( new Drawer( "Resource" ) );

	ApplicationPtr app = Application::getInstance( );
	app->addTask( Test::getTag( ), test );
	app->addTask( Drawer::getTag( ), drawer );
}
