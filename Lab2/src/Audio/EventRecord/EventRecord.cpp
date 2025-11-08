#include "EventRecord.h"
#include <iostream>
#include <memory>

EventRecord::EventRecord(const std::string& name,
                         const std::shared_ptr<Artist>& artistPtr,
                         const std::string& eventDate)
        : eventName(name), artist(artistPtr), date(eventDate) {}

std::string EventRecord::getEventName() const {
    return eventName;
}

std::shared_ptr<Artist> EventRecord::getArtist() const {
    return artist;
}

std::string EventRecord::getDate() const {
    return date;
}