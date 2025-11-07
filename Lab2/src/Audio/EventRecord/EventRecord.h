#ifndef EVENT_RECORD_H
#define EVENT_RECORD_H

#include <string>
#include <memory>

class Artist;

class EventRecord {
private:
    std::string eventName;
    std::shared_ptr<Artist> artist;
    std::string date;

public:
    EventRecord(const std::string& name,
                const std::shared_ptr<Artist>& artistPtr,
                const std::string& eventDate);

    std::string getEventName() const;
    std::shared_ptr<Artist> getArtist() const;
    std::string getDate() const;

};

#endif // EVENT_RECORD_H