#ifndef LAB2_AUDIO_H
#define LAB2_AUDIO_H

#include <string>

class RegisteredUser;

class Audio {
private:
    unsigned long long duration;
    std::string name;
    unsigned long long coverID;
public:
    Audio(unsigned long long duration, std::string name, unsigned long long coverID);
    [[nodiscard]] virtual std::string getAuthor() const = 0;
    [[nodiscard]] const std::string& getName() const;
    [[nodiscard]] unsigned long long getCoverID() const;
    [[nodiscard]] unsigned long long getDuration() const;
    virtual ~Audio() = default;
};

#endif //LAB2_AUDIO_H
