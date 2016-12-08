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
		drawer->loadMV1Model( 0, "enemy_goblin_attack.mv1", 1.0 );
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

		/*
		Drawer::ModelMV1 model;
		model.dir = Vector( 1, 0, 0 );
		model.motion = 0;
		model.pos = Vector( );
		model.time = 0;
		drawer->setModelMV1( model );
		
		ApplicationPtr app = Application::getInstance( );
		app->setCameraUp( Vector( 0, 0, 1 ) );
		static double length = 0.0;
		length += 0.01;
		app->setCamera( Vector( 0, 500, 0 ), Vector( ) );
		*/


		static double r = 0;
		static int time;
		time++;
		r += 0.01;
		Matrix mat = Matrix::makeTransformRotation( Vector( 0, 1, 0 ), r );
		//Matrix mat = Matrix::makeTransformTranslation( Vector( 100, 0, 0 ) );

		//Matrix
		Drawer::ModelMV1 model;
		model.matrix = mat;
		model.motion = 0;
		model.time = 0;
		drawer->setModelMV1( model );
		ApplicationPtr app = Application::getInstance( );
		app->setCameraUp( Vector( 0, 1, 0 ) );
		app->setCamera( Vector( 100, 20, 500 ), Vector( ) );
	}
};

void main( ) {
	TaskPtr test = TaskPtr( new Test );
	TaskPtr drawer = TaskPtr( new Drawer( "Resource" ) );

	ApplicationPtr app = Application::getInstance( );
	app->addTask( Test::getTag( ), test );
	app->addTask( Drawer::getTag( ), drawer );
}
