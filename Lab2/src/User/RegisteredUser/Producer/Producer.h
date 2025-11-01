#ifndef LAB2_PRODUCER_H
#define LAB2_PRODUCER_H

#include "../RegisteredUser.h"
#include <vector>
#include "../../../Audio/Album/MusicTrack/MusicTrack.h"

class Producer : public RegisteredUser{
private:
    std::string bio;
    std::vector<std::shared_ptr<MusicTrack> > tracks;
public:
    Producer(const std::string& id, const std::string& username,
             const std::string& email, const std::string& password,
             const std::string& bio);

    bool addTrack(const std::shared_ptr<MusicTrack>& track);
    bool removeTrack(const std::shared_ptr<MusicTrack>& track);
    bool hasTrack(const std::shared_ptr<MusicTrack>& track) const;

    const std::vector<std::shared_ptr<MusicTrack>>& getTracks() const { return tracks; }

};

#endif //LAB2_PRODUCER_H
