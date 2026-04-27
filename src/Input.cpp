#include "Input.hpp"

Parser::Parser(int argc, char* argv[]){

	flags.isCamDecoy = false;
	flags.mouseDisabled = false;
	flags.renderLabels = false;

	char* wrongArgs[16];
	int waSize = 0;

	for(int i = 1; i < argc; i++){

		if(!strcmp(argv[i], "--nm")){

			flags.mouseDisabled = true;
		}
		else if(!strcmp(argv[i], "--decoy")){

			flags.isCamDecoy = true;
		}
		else if(!strcmp(argv[i], "--labels")){

			flags.renderLabels = true;
		}
		else{
			wrongArgs[waSize++] = argv[i];
		}
	}

	for(int i = 0; i < waSize; i++){

		std::cout << "Invalid argument: " << wrongArgs[i] << std::endl;
	}

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


