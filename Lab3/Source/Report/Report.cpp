#include "Report.h"
#include <ctime>

Report::Report(const std::string& title, const std::string& generatedBy)
    : title(title), generatedBy(generatedBy), isFinalized(false) {
    generationTime = std::time(nullptr);
}

bool Report::validate() const {
    return !title.empty() && !generatedBy.empty();
}

std::string Report::getTitle() const {
    return title;
}

time_t Report::getGenerationTime() const {
    return generationTime;
}

bool Report::getIsFinalized() const {
    return isFinalized;
}

std::string Report::getGeneratedBy() const {
    return generatedBy;
}
