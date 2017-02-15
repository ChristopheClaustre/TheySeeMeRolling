#ifndef OPENAL_H
#define OPENAL_H

#include <iostream>
#include <string>

#include <AL/al.h>
#include <AL/alc.h>

#include "../utils.h"

namespace Audio {

inline void CHECK_OPEN_AL_ERRORS(std::string msg)
{
    Utils::CHECK_ERRORS(alGetError() != AL_NO_ERROR, msg);
}


class OpenAL
{
public:
    static OpenAL * getInstance();

    void initialize(ALfloat position[]);// = {0.0, 0.0, 0.0});

    ~OpenAL();

private:
    static OpenAL * instance;

    OpenAL() : device(nullptr), context(nullptr) { }

    ALCdevice * device;
    ALCcontext * context;
}; // class OpenAL

} // namespace Audio

#endif // OPENAL_H
