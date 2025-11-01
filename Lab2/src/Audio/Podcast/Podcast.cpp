#include "Podcast.h"
#include "../../User/RegisteredUser/Podcaster/Podcaster.h"
#include <iostream>

Podcast::Podcast(const std::string& title, const std::string& description, Podcaster* host,
                 const std::string& category, unsigned long long coverID,unsigned long long duration)
        : Audio(duration, title, coverID),
          host(host),
          category(category)
          {}

Podcaster* Podcast::getHost() const {
    return host;
}

std::string Podcast::getCategory() const {
    return category;
}


