#include "EventRecord.h"
#include <iostream>


EventRecord::EventRecord(const std::string& name,
                         const std::shared_ptr<Artist>& artistPtr,
                         const std::string& eventDate)
        : eventName(name), artist(artistPtr), date(eventDate) {}
