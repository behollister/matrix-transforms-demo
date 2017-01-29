#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec2.hpp>
#include <glm/vec4.hpp> // glm::vec4, glm::ivec4
#include <glm/mat2x2.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

#include <glm/ext.hpp>
#include <glm/gtx/string_cast.hpp>


//Using SDL and standard IO
#include <SDL.h>
#include <stdio.h>
#include <iostream>


//Using SDL, SDL_image, standard IO, math, and strings
#include <SDL.h>
#include <stdio.h>
#include <string>
#include <cmath>

//Screen dimension constants
const int SCREEN_WIDTH = 500;
const int SCREEN_HEIGHT = 500;

#define PI 3.14159265

//Starts up SDL and creates window
bool init();

//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "CPE 471 - Matrix Transforms", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

			}
		}
	}

	return success;
}

void close()
{
	//Destroy window
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}

int main( int argc, char* args[] )
{
	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{

		//Main loop flag
		bool quit = false;

		//Event handler
		SDL_Event e;

		//While application is running
		while( !quit )
		{
			//Handle events on queue
			while( SDL_PollEvent( &e ) != 0 )
			{
				//User requests quit
				if( e.type == SDL_QUIT )
				{
					quit = true;
				}
			}

			// define vertices for triangles
			glm::vec3 v1 = glm::vec3( 0, 0, 1 );
			glm::vec3 v2 = glm::vec3( 0, 150, 1 );
			glm::vec3 v3 = glm::vec3( 150, 150, 1 );
			glm::vec3 v4 = glm::vec3( 150, 0, 1 );

			// GLM api docs - https://glm.g-truc.net/0.9.4/api/a00206.html

			// set transformations
			static float angle = 10.0;
			angle += 0.0;
			glm::mat3 rot = glm::mat3( cos ( angle * PI / 180.0 ), sin ( angle * PI / 180.0 ), 0
			                         , -sin ( angle * PI / 180.0 ), cos ( angle * PI / 180.0 ) , 0
			                         , 0, 0 , 1.0  ) ;
            static float tx = 0.0;
            static float ty = 0.0;
            tx += .05; ty += 0;
			glm::mat3 translate = glm::mat3( 1.0, 0.0, 0.0
			                              , 0.0, 1.0, 0.0
			                              , tx, ty, 1.0 ) ;

			static float sx = 1.0;
			static float sy = 2.0;
			sx += .0; sy += 0.001;
			glm::mat3 scale = glm::mat3( sx, 0.0, 0.0
										  , 0.0, sy, 0.0
										  , 0, 0, 1.0 ) ;

			float ax = 20.0; // degrees tilted for x-axis
			float ay = 0.0; // degrees tilted for y-axis
			static float dx = ay * PI / 180.0;
			static float dy = ax * PI / 180.0;
			glm::mat3 shear = glm::mat3( 1.0 , dy, 0.0
									   , dx, 1.0, 0.0
									   , 0, 0, 1.0 ) ;

			// composite transformation matrix
			glm::mat3 cm;
			//cm = rot * translate;
			//cm = translate * rot;
			cm = shear;

			// apply transformations to each vertex
			v1 = cm * v1;
			v2 = cm * v2;
			v3 = cm * v3;
			v4 = cm * v4;

//			printf( glm::to_string(v1).c_str() ); printf("\n");
//			printf( glm::to_string(v2).c_str() ); printf("\n");
//			printf( glm::to_string(v3).c_str() ); printf("\n");

			//Clear screen
			SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
			SDL_RenderClear( gRenderer );

			SDL_SetRenderDrawColor( gRenderer, 0xFF, 0x00, 0x00, 0xFF );

			// draw transformed triangle
			SDL_RenderDrawLine( gRenderer, v1.x, SCREEN_HEIGHT - v1.y, v2.x, SCREEN_HEIGHT - v2.y );
			SDL_RenderDrawLine( gRenderer, v2.x, SCREEN_HEIGHT - v2.y, v3.x, SCREEN_HEIGHT - v3.y );
			SDL_RenderDrawLine( gRenderer, v3.x, SCREEN_HEIGHT - v3.y, v1.x, SCREEN_HEIGHT - v1.y );

//			SDL_SetRenderDrawColor( gRenderer, 0x00, 0xFF, 0x00, 0xFF );

			SDL_RenderDrawLine( gRenderer, v4.x, SCREEN_HEIGHT - v4.y, v3.x, SCREEN_HEIGHT - v3.y );
			SDL_RenderDrawLine( gRenderer, v3.x, SCREEN_HEIGHT - v3.y, v1.x, SCREEN_HEIGHT - v1.y );
			SDL_RenderDrawLine( gRenderer, v1.x, SCREEN_HEIGHT - v1.y, v4.x, SCREEN_HEIGHT - v4.y );

			//Update screen
			SDL_RenderPresent( gRenderer );
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}
