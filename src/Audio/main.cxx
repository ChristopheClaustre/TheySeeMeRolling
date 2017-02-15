#include <iostream>
#include <chrono>
#include <thread>

#include <AL/al.h>

#include "openal.h"
#include "wave.h"
#include "source.h"

int main(int argc, char *argv[])
{
    ALfloat listenerPos[] = {0.0, 0.0, 0.0};
    Audio::OpenAL::getInstance()->initialize(listenerPos);

    //Loading of the WAVE file
    Audio::Wave wave("TheySeeMeRolling-Short-mono.wav");
    wave.load();
    wave.createBuffer();

    Audio::Source source(wave.getIdBuffer());
    source.setGain(0.3);
    source.play();

    ALfloat position[] = {-4.0, 0.0, 1.0};

    float delta = 0.5;
    std::chrono::milliseconds timespan(int(100));
//    alSourcef(source.getIdSource(), AL_REFERENCE_DISTANCE, 1.5);
//    alSourcef(source.getIdSource(), AL_MAX_DISTANCE, 2.5);
//    alSourcei(source.getIdSource(), AL_SOURCE_TYPE, AL_STREAMING);

    for (float i = -20; i < 20; i+=delta) {
        position[0] = i;
        source.setPosition(position);
        std::this_thread::sleep_for(timespan);
    }

    while(source.getState() == AL_PLAYING) {
        std::this_thread::sleep_for(timespan);
    }

    std::cout << "Done !" << std::endl;

    delete Audio::OpenAL::getInstance();

    return EXIT_SUCCESS;
}


