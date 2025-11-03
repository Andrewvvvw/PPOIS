#include "Advertisement.h"

Advertisement::Advertisement(const std::string& id, const std::string& content, int duration) :
    id(id), content(content), duration(duration) {}

std::string Advertisement::getId() const {
    return this->id;
}

std::string Advertisement::getContent() const {
    return this->content;
}

int Advertisement::getDuration() const {
    return this->duration;
}

bool Advertisement::operator==(const Advertisement& other) const {
    return id == other.id && content == other.content && duration == other.duration;
}

