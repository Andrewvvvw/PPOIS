#ifndef LAB2_PODCAST_H
#define LAB2_PODCAST_H

#include <string>
#include <vector>
#include "../Audio.h"

class Podcaster;

class Podcast : public Audio {
private:
    Podcaster* host;
    std::string category;

public:

    Podcast(const std::string& title, const std::string& description, Podcaster* host,
            const std::string& category, unsigned long long coverID, unsigned long long duration);

    Podcaster* getHost() const;
    std::string getCategory() const;

    std::string getAuthor() const override;

};

#endif //LAB2_PODCAST_H