#include "openal.h"

namespace Audio {

OpenAL * OpenAL::instance = nullptr;

OpenAL * OpenAL::getInstance()
{
    if (instance == nullptr)
        instance = new OpenAL();

    return instance;
}

OpenAL::~OpenAL()
{
    alcMakeContextCurrent(NULL);
    alcDestroyContext(context);
    alcCloseDevice(device);
}

void OpenAL::initialize(ALfloat listenerPos[])
{
    device = alcOpenDevice(NULL);
    Utils::CHECK_ERRORS(!device , "no sound device");  //Error during device opening

    context = alcCreateContext(device, NULL);
    alcMakeContextCurrent(context);
    Utils::CHECK_ERRORS(!context, "no sound context"); //Error during context handeling

    ALfloat velocity[] = { 0.0, 0.0, 0.0 };
    ALfloat orientation[] = { 0.0, 0.0, -1.0,  0.0, 1.0, 0.0 };

    alListenerfv(AL_POSITION,    listenerPos);  //Set position of the listener
    alListenerfv(AL_VELOCITY,    velocity);     //Set velocity of the listener
    alListenerfv(AL_ORIENTATION, orientation);  //Set orientation of the listener
}

} // namespace Audio
