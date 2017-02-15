#include "wave.h"

namespace Audio {

Wave::Wave(std::string fname) : filename("../misc/WAVE/"+fname)
{
}

Wave::~Wave()
{
    delete[] data;
    alDeleteBuffers(1, &id_buffer);
}

void Wave::load()
{
    //Loading of the WAVE file
    FILE *fp = fopen(filename.c_str(), "rb");
    Utils::CHECK_ERRORS(!fp, "Failed to open file");

    //Variables to store info about the WAVE file (all of them is not needed for OpenAL)
    char type[4];
    int size,chunkSize;
    short formatType,channels;
    int avgBytesPerSec;
    short bytesPerSample,bitsPerSample;

    //Check that the WAVE file is OK
    fread(type,sizeof(char),4,fp);
    Utils::CHECK_ERRORS(type[0]!='R' || type[1]!='I' || type[2]!='F' || type[3]!='F', "not RIFF");

    fread(&size, sizeof(int),1,fp);
    fread(type, sizeof(char),4,fp);
    Utils::CHECK_ERRORS(type[0]!='W' || type[1]!='A' || type[2]!='V' || type[3]!='E', "not WAVE");

    fread(type,sizeof(char),4,fp);
    Utils::CHECK_ERRORS(type[0]!='f' || type[1]!='m' || type[2]!='t' || type[3]!=' ', "not fmt ");

    fread(&chunkSize,sizeof(int),1,fp);
    fread(&formatType,sizeof(short),1,fp);
    fread(&channels,sizeof(short),1,fp);
    fread(&frequency,sizeof(int),1,fp);
    fread(&avgBytesPerSec,sizeof(int),1,fp);
    fread(&bytesPerSample,sizeof(short),1,fp);
    fread(&bitsPerSample,sizeof(short),1,fp);

    fread(type,sizeof(char),4,fp);
    Utils::CHECK_ERRORS(type[0]!='d' || type[1]!='a' || type[2]!='t' || type[3]!='a', "not data");

    //The size of the sound data is read
    fread(&dataSize,sizeof(int),1,fp);

    //Allocate memory for the sound data
    data = new unsigned char[dataSize];
    int nbytes = fread(data,sizeof(int),dataSize,fp);
//    CHECK_ERRORS(nbytes != dataSize, "number of bytes incoherent");

    //Figure out the format of the WAVE file
    format = 0;
    if(bitsPerSample == 8)
    {
        if(channels == 1)
            format = AL_FORMAT_MONO8;
        else if(channels == 2)
            format = AL_FORMAT_STEREO8;
    }
    else if(bitsPerSample == 16)
    {
        if(channels == 1)
            format = AL_FORMAT_MONO16;
        else if(channels == 2)
            format = AL_FORMAT_STEREO16;
    }
    Utils::CHECK_ERRORS(!format, "Wrong BitPerSample");

    fclose(fp);
}

void Wave::createBuffer()
{
    alGenBuffers(1, &id_buffer);
    CHECK_OPEN_AL_ERRORS("Error GenBuffer");

    alBufferData(id_buffer, format, data, dataSize, frequency);
    CHECK_OPEN_AL_ERRORS("Error loading ALBuffer");
}

} // namespace Audio
