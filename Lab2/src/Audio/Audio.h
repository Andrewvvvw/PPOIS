#ifndef LAB2_AUDIO_H
#define LAB2_AUDIO_H

#include <string>
#include "../User/RegisteredUser/RegisteredUser.h"

class Audio {
private:
    unsigned long long duration;
    std::string name;
    unsigned long long coverID;
    RegisteredUser* owner;
public:
    Audio(unsigned long long duration, std::string name, unsigned long long coverID) :
        duration(duration), name(name), coverID(coverID) {};
    [[nodiscard]] virtual std::string getAuthor() const = 0;
    [[nodiscard]] const std::string& getName() const { return name; }
    [[nodiscard]] unsigned long long getCoverID() const { return coverID; }
    [[nodiscard]] unsigned long long getDuration() const { return duration; }

};

#endif //LAB2_AUDIO_H
