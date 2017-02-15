#ifndef WAVE_H
#define WAVE_H

#include <AL/al.h>
#include <string>

#include "openal.h"

namespace Audio {

class Wave
{
public:
    Wave(std::string fname);
    ~Wave();
    void load();
    void createBuffer();
    ALuint getIdBuffer() { return id_buffer; }
    unsigned char * getData() { return data; }

private:
    std::string filename;
    std::string err;

    ALuint id_buffer;
    ALenum format;
    unsigned char * data;
    int dataSize;
    ALuint frequency;
}; // class Wave

} // namespace Audio

#endif // WAVE_H
