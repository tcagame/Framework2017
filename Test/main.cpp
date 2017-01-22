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

	enum MV {
		MV_MESH,
		MV_ANIME_01,
		MV_ANIME_02,
		MV_SAMPLE,
	};
	void initialize( ) {
		DrawerPtr drawer = Drawer::getTask( );
		drawer->loadMV1Model( MV_MESH, "player_01.mv1" );
		drawer->loadMV1Model( MV_ANIME_01, "player_move.mv1" );
		drawer->loadMV1Model( MV_ANIME_02, "player_idle.mv1" );
		drawer->loadMV1Model( MV_SAMPLE, "sample.mv1" );

	}

	void update( ) {
		DrawerPtr drawer = Drawer::getTask( );

		static double r = 0;
		//r += 0.01;
		Matrix mat = Matrix::makeTransformRotation( Vector( 0, 1, 0 ), PI / 2 + r );
		Matrix mat_trans = Matrix::makeTransformTranslation( Vector( 0, 0, 0 ) );
		mat = mat * mat_trans;

		static MV mv_anime = MV_ANIME_01;
		KeyboardPtr keyboard = Keyboard::getTask( );
	

		

		static double time = 0;
		time += 0.9;

		if ( keyboard->isPushKey( "ARROW_LEFT" ) ) {
			mv_anime = MV_ANIME_01;
			time = 0;
		}
		if ( keyboard->isPushKey( "ARROW_RIGHT" ) ) {
			mv_anime = MV_ANIME_02;
			time = 0;
		}
		//Matrix
		Drawer::ModelMV1 model;
		model.matrix = mat;
		model.mesh = MV_MESH;
		model.anime = mv_anime;
		model.time = time;
		drawer->setModelMV1( model );
		ApplicationPtr app = Application::getInstance( );
		app->setCameraUp( Vector( 0, 1, 0 ) );

		static double length = 500;

		Vector vec( 100, 20, 500 );
		vec = vec.normalize( ) * length;
		app->setCamera( vec, Vector( ) );
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
