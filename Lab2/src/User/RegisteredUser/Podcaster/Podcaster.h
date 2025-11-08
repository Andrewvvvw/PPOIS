#ifndef LAB2_PODCASTER_H
#define LAB2_PODCASTER_H

#include "../RegisteredUser.h"
#include "../../../Audio/Podcast/Podcast.h"
#include <vector>
#include <string>
#include <memory>
class Podcaster : public RegisteredUser{
private:
    std::string bio;
    std::vector<std::shared_ptr<Podcast>> podcasts;
public:
    Podcaster(const std::string& id, const std::string& username,
              const std::string& email, const std::string& password);

    bool addPodcast(const std::shared_ptr<Podcast>& podcast);
    bool removePodcast(const std::shared_ptr<Podcast>& podcast);
    bool hasPodcast(const std::shared_ptr<Podcast>& podcast) const;

    const std::vector<std::shared_ptr<Podcast>>& getPodcasts() const;

};

#endif //LAB2_PODCASTER_H
