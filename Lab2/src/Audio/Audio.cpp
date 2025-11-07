#include "Audio.h"
#include "../Exceptions/Exceptions.h"

Audio::Audio(unsigned long long duration, std::string name, unsigned long long coverID) :
       name(name), coverID(coverID) {
    if(duration > 18000)
        throw ExceptionIncorrectDuration("Incorrect audio duration");
    if(name.empty())
        throw ExceptionIncorrectAudioName("Audio name can't be empty");
    this->duration = duration;
}