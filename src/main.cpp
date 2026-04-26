#include <iostream>
#include <vector>
#include <numbers>
#include <string>
#include <map>
#include <chrono>
#include <thread> //for fps rating not multithreading

#include "Renderer.hpp"
#include "SpaceObject.hpp"

#define SPEED 5
#define FOVSPEED 40
#define CAMSPEED 2
#define MOUSESENS 1

//a lot of code is poorly structured and shouldnt be in
//this file or at leas should be better organized

double radToDeg(double radians);
void handleInput(SDL_Event* _events, const Uint8* _kbstate, Camera &_cam, float deltaTime, bool mouseDisabled);

int main(int argc, char* argv[]){

        SDL_Window* window = nullptr;
        SDL_Renderer* renderer = nullptr;

        SDL_Init(SDL_INIT_EVERYTHING);

        SDL_CreateWindowAndRenderer(RES[0], RES[1], 0, &window, &renderer);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

			//strcmp returns 0 if true
	if(!(argc > 1 && !strcmp(argv[1], "--nm")) && SDL_SetRelativeMouseMode(SDL_TRUE) < 0){

		std::cerr << "ERR: Could not capture mouse, use --nm to disable mouse support" << std::endl;
		std::cerr << "error code: " << SDL_GetError() << std::endl;
		return 1;
	}

        textRenderer* txtRenderer = new textRenderer(renderer, "../src/Hack-Regular.ttf", 20);

	const std::chrono::duration<double> frameMaxExecTime(1.0 / 60.0);
	auto lastFrameTime = std::chrono::high_resolution_clock::now();
	float deltaTime;

	//fps counter
	int frameCount = 0;
	double fps = 0;
	auto lastFpsUpdateTime = std::chrono::high_resolution_clock::now();

	//argv flags
	bool isCamDecoy = false;
	bool mouseDisabled = false;

	//bool isCamDecoy = false;

	std::vector<Camera> cameras;
	cameras.push_back({});

	if(argc > 1 && !strcmp(argv[1], "--decoy")){
		
		std::cout << "decoy active" << std::endl;
		isCamDecoy = true;
	}
	if(argc > 1 && !strcmp(argv[1], "--nm")){
	
		mouseDisabled = true;
	}

	int cidx = 0;

	Hud hud;

	hud.stats.push_back({"cam X", &cameras[cidx].posX});
	hud.stats.push_back({"cam Y", &cameras[cidx].posY});
	hud.stats.push_back({"cam Z", &cameras[cidx].posZ});
	hud.stats.push_back({"fov", &cameras[cidx].fov});
	hud.stats.push_back({"tiltX", &cameras[cidx].tiltX});
	hud.stats.push_back({"tiltY", &cameras[cidx].tiltY});
	hud.stats.push_back({"fps", &fps});

	//SpaceObject sun(500, 500, 0, 1.989e30, 696e3);
	
	std::map<std::string, SpaceObject> astros;
	
	//the base of rotation-orbit is meant to be to the power of -7 to have them be accurat,
	
	/*
	astros.try_emplace("Sun", 0.00, 0.00, 0.00, 1.00, 50.00, 0.00, 28.7e-3);
	astros.try_emplace("Mercury", 78.00, 0.00, 0.00, 1.00, 15.00, 8.26e-3, 12.4e-3);
	astros.try_emplace("Venus", 144.00, 0.00, 0.00, 1.00, 20.00, 3.23e-3, -2.99e-3);
	astros.try_emplace("Earth", 200.00, 0.00, 0.00, 1.00, 20.00, 1.99e-3, 727.2e-3);
	astros.try_emplace("Mars", 304.00, 0.00, 0.00, 1.00, 16.00, 1.06e-3, 708.8e-3);
	astros.try_emplace("Jupiter", 1200.00, 0.00, 0.00, 1.00, 40.00, 1.67e-3, 1760.0e-3);
	astros.try_emplace("Saturn", 2180.00, 0.00, 0.00, 1.00, 35.00, 9.29e-3, 1630.0e-3);
	astros.try_emplace("Uranus", 3840.00, 0.00, 0.00, 1.00, 28.00, 2.37e-3, 1010.0e-3);
	astros.try_emplace("Neptune", 6000.00, 0.00, 0.00, 1.00, 28.00, 1.21e-3, 1080.0e-3);
	*/
	
	astros.try_emplace("Sun", 0.00, 0.00, 0.00, 1.00, 50.00, 0.00, 28.7e-4);
	astros.try_emplace("Mercury", 78.00, 0.00, 0.00, 1.00, 15.00, 8.26e-2, 12.4e-4);
	astros.try_emplace("Venus", 144.00, 0.00, 0.00, 1.00, 20.00, 3.23e-2, -2.99e-4);
	astros.try_emplace("Earth", 200.00, 0.00, 0.00, 1.00, 20.00, 1.99e-2, 727.2e-4);
	astros.try_emplace("Mars", 304.00, 0.00, 0.00, 1.00, 16.00, 1.06e-2, 708.8e-4);
	astros.try_emplace("Jupiter", 1200.00, 0.00, 0.00, 1.00, 40.00, 1.67e-2, 1760.0e-4);
	astros.try_emplace("Saturn", 2180.00, 0.00, 0.00, 1.00, 35.00, 9.29e-2, 1630.0e-4);
	astros.try_emplace("Uranus", 3840.00, 0.00, 0.00, 1.00, 28.00, 2.37e-2, 1010.0e-4);
	astros.try_emplace("Neptune", 6000.00, 0.00, 0.00, 1.00, 28.00, 1.21e-2, 1080.0e-4);


	if(isCamDecoy){

		//we set the first cam as decoy on the origin
		//and move the cidx to the next we are inserting
		cameras.push_back({});
		cidx++;
		astros.try_emplace("CAMERA", -cameras[0].posX - 5, -cameras[0].posY, cameras[0].posZ, 0, 10, 0, 0);
	}


	SDL_Event events;
	const Uint8* kbstate = SDL_GetKeyboardState(NULL);

	bool run = true;
	while(run){

		//get current time for delta time and fps management
		auto beginFrameTime = std::chrono::high_resolution_clock::now();
		std::chrono::duration<float> duration = beginFrameTime - lastFrameTime;
	
		//calculate delta time
		deltaTime = duration.count() * 60;
		if(deltaTime > 0.1f * 60) deltaTime = 0.1f * 60; //10 fps cap so lag doesnt send camera flying
		//
	
		//fps counter
		frameCount++;
		std::chrono::duration<float> fpsElapsed = beginFrameTime - lastFpsUpdateTime;

		if(fpsElapsed.count() >= 1.0f){

			fps = (float)frameCount / fpsElapsed.count();

			frameCount = 0;
			lastFpsUpdateTime = beginFrameTime;
		}

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

		if(kbstate[SDL_SCANCODE_ESCAPE]){

			run = false;
		}
	
		handleInput(&events, kbstate, cameras[cidx], deltaTime, mouseDisabled);
		
		for(auto &astro : astros){

			SpaceObject* so = &astro.second;

			so->rotateY(so->angVelocityRotation * deltaTime);
			so->orbitY(so->angVelocityOrbit * deltaTime);

			if(isCamDecoy){

				so->project(cameras[cidx], cameras[0]);
			}
			else{

				so->project(cameras[cidx]);
			}

			so->render(renderer, txtRenderer);
		}
	
		hud.renderCrossHair(renderer);
		hud.renderStats(txtRenderer);

		SDL_RenderPresent(renderer);

		lastFrameTime = beginFrameTime;
		
		auto timeFinished = std::chrono::high_resolution_clock::now();
		auto timeTaken = timeFinished - beginFrameTime;

		if(timeTaken < frameMaxExecTime){

			std::this_thread::sleep_for(frameMaxExecTime - timeTaken);
		}
	}


	return 0;
}

void handleInput(SDL_Event* _events, const Uint8* _kbstate, Camera &_cam, float deltaTime, bool mouseDisabled){

	while(SDL_PollEvent(_events)){
	
		if(!mouseDisabled){
			
			if(_events->type == SDL_MOUSEMOTION){

				if(_events->motion.yrel){
				
					double inputTiltX = _events->motion.yrel * (MOUSESENS / _cam.fov);
			
					if((_cam.tiltX - inputTiltX) < -1.57){
				
						_cam.tiltX = -1.57;
					}
					else if((_cam.tiltX - inputTiltX) > 1.57){
					
						_cam.tiltX = 1.57;
					}
					else{
						
						_cam.tiltX -= inputTiltX;
					}
				}

				if(_events->motion.xrel){

					_cam.tiltY = std::fmod(_cam.tiltY + (_events->motion.xrel * (MOUSESENS / _cam.fov)), 2 * PI);
				}
			}
		}
	}

	//_camera Z
	if(_kbstate[SDL_SCANCODE_W]){

		_cam.moveZ(SPEED, deltaTime); // negative due to inverted Y in SDL
	}
	if(_kbstate[SDL_SCANCODE_S]){

		_cam.moveZ(-SPEED, deltaTime);
	}

	//_camera X
	if(_kbstate[SDL_SCANCODE_A]){

		_cam.moveX(-SPEED, deltaTime);
	}
	if(_kbstate[SDL_SCANCODE_D]){

		_cam.moveX(SPEED, deltaTime);
	}

	//_camera Y
	if(_kbstate[SDL_SCANCODE_SPACE]){

		_cam.moveY(-SPEED, deltaTime);
	}
	if(_kbstate[SDL_SCANCODE_LSHIFT]){

		_cam.moveY(SPEED, deltaTime);
	}
	
	//camera fov
	if(_kbstate[SDL_SCANCODE_MINUS] && _cam.fov > FOVSPEED){

		_cam.fov -= FOVSPEED * deltaTime;
	}
	if(_kbstate[SDL_SCANCODE_EQUALS]){

		_cam.fov += FOVSPEED * deltaTime;
	}
	
	//camera tilt X
	if(_kbstate[SDL_SCANCODE_UP]){

		_cam.tiltX = _cam.tiltX + (CAMSPEED * deltaTime * (15 / _cam.fov)) > 1.57 ? 1.57 : _cam.tiltX + (CAMSPEED * deltaTime * (15 / _cam.fov));
	}
	if(_kbstate[SDL_SCANCODE_DOWN]){

		_cam.tiltX = _cam.tiltX - (CAMSPEED * deltaTime * (15 / _cam.fov)) < -1.57 ? -1.57 : _cam.tiltX - (CAMSPEED * deltaTime * (15 / _cam.fov));
	}

	//camera tilt Y
	//
	//value is multiplied by 1500 / fov to make it adapt on distance
	if(_kbstate[SDL_SCANCODE_LEFT]){

		_cam.tiltY = std::fmod(_cam.tiltY - (CAMSPEED * deltaTime * (15 / _cam.fov)), 2 * PI);
	}
	if(_kbstate[SDL_SCANCODE_RIGHT]){

		_cam.tiltY = std::fmod(_cam.tiltY + (CAMSPEED * deltaTime * (15 / _cam.fov)), 2 * PI);
	}
}


double radToDeg(double radians){

	return radians * 180 / PI;
}
