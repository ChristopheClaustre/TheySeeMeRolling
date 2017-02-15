#include <iostream>

//#include <AL/al.h>
//#include <AL/alc.h>

#include "openal.h"
#include "wave.h"
#include "source.h"

int main(int argc, char *argv[])
{
    ALfloat listenerPos[] = {0.0, 0.0, 0.0};
    Audio::OpenAL::getInstance()->initialize(listenerPos);

    //Loading of the WAVE file
    Audio::Wave wave("TheySeeMeRolling-Short.wav");
    wave.load();
    wave.createBuffer();

    Audio::Source source(wave.getIdBuffer());
    source.play();

    int truc;
    std::cin >> truc;

    delete Audio::OpenAL::getInstance();

    return EXIT_SUCCESS;
}


