#include <iostream>
#include <chrono>
#include <thread>

#include <AL/al.h>

#include "openal.h"
#include "wave.h"
#include "source.h"

int main(int argc, char *argv[])
{
    cout << "Audio world!" << endl;

    ALfloat listenerPos[] = {0.0, 0.0, 0.0};
    Audio::OpenAL::getInstance()->initialize(listenerPos);

    //Loading of the WAVE file
    Audio::Wave wave("TheySeeMeRolling-Short-mono.wav");
    wave.load();
    wave.createBuffer();

    Audio::Source source(wave.getIdBuffer());
    source.setGain(0.5f);
    source.setRolloffFactor(1); // degré d'atténuation
    source.setMaxDistance(20.0); // distance maximal ou la source est audible
    source.setReferenceDistance(5); // distance à partir de laquelle le rolloff_factor et la max distance influt vraiment
    source.play();

    ALfloat position[] = {-20.0, 0.0, 0.0};

    std::chrono::milliseconds timespan(int(100));

    float i = -20;
    while(source.getState() == AL_PLAYING) {
        i+=0.5;
        position[0] = i;
        source.setPosition(position);
        std::this_thread::sleep_for(timespan);
    }

    std::cout << "Done !" << std::endl;

    delete Audio::OpenAL::getInstance();

    return EXIT_SUCCESS;
}


