#ifndef SOURCE_H
#define SOURCE_H

#include <AL/al.h>
#include <array>

#include "openal.h"

namespace Audio {

class Source
{
public:
    Source(ALuint id_buffer, std::array<ALfloat,3> position = {{0.0, 0.0, 0.0}}, std::array<ALfloat,3> velocity = {{0.0, 0.0, 0.0}},
            ALfloat pitch = 1.0, ALfloat gain = 1.0, ALenum looping = AL_FALSE);
    ~Source();

    void setIdBuffer(ALuint id_buffer);
    void setPosition(ALfloat position[]);
    void setVelocity(ALfloat velocity[]);
    void setPitch(ALfloat pitch);
    void setGain(ALfloat gain);
    void setLooping(ALenum looping);

    void play();
    void pause();
    void stop();

    ALuint getIdSource() { return id_source; }
    ALuint getState();

private:
    ALuint id_source;
}; // class Source

} // namespace Audio

#endif // SOURCE_H
