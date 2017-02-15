#include "source.h"

namespace Audio {

Source::Source(ALuint id_buffer, std::array<ALfloat,3> position, std::array<ALfloat,3> velocity,
               ALfloat pitch, ALfloat gain, ALenum looping)
{
    alGenSources(1, &id_source);
    CHECK_OPEN_AL_ERRORS("Error GenSource");

    setIdBuffer(id_buffer);
    setPosition(position.data());
    setVelocity(velocity.data());
    setPitch(pitch);
    setGain(gain);
    setLooping(looping);
}

Source::~Source()
{
    alDeleteSources(1, &id_source);
}

void Source::setIdBuffer(ALuint id_buffer) {
    alSourcei(id_source, AL_BUFFER, id_buffer);
}

void Source::setPosition(ALfloat position[]) {
    alSourcefv(id_source, AL_POSITION, position);
}

void Source::setVelocity(ALfloat velocity[]) {
    alSourcefv(id_source, AL_VELOCITY, velocity);
}

void Source::setPitch(ALfloat pitch) {
    alSourcef(id_source, AL_PITCH, pitch);
}

void Source::setGain(ALfloat gain) {
    alSourcef(id_source, AL_GAIN, gain);
}

void Source::setLooping(ALenum looping) {
    Utils::CHECK_ERRORS(looping != AL_FALSE && looping != AL_TRUE, "incorrect value for looping attribute");
    alSourcei(id_source, AL_LOOPING, looping);
}

void Source::play() {
    alSourcePlay(id_source);
}

void Source::pause() {
    alSourcePause(id_source);
}

void Source::stop() {
    alSourceStop(id_source);
}

} // namespace Audio
