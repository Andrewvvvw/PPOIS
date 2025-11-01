#include "PlayingNowPanel.h"
#include <iomanip>
#include <sstream>

PlayingNowPanel::PlayingNowPanel()
    : coverID(0), progress(0) {}

void PlayingNowPanel::updateTrackInfo(const Audio& audio) {
    currentAudio = &audio;
    trackName = audio.getName();
    artistName = audio.getAuthor();
    coverID = audio.getCoverID();
}

const Audio& PlayingNowPanel::getCurrentTrack() const {
    if (!currentAudio) {
        throw std::runtime_error("No audio track is currently set");
    }
    return *currentAudio;
}

void PlayingNowPanel::setProgress(float newProgress) {
    if (newProgress >= 0.0f && newProgress <= 1.0f) {
        progress = newProgress;
    }
}

std::string PlayingNowPanel::getFormattedProgress() const {
    unsigned int currentPos = static_cast<unsigned int>(progress * currentAudio->getDuration());
    unsigned int totalDuration = currentAudio->getDuration();

    auto formatTime = [](unsigned int seconds) -> std::string {
        unsigned int minutes = seconds / 60;
        seconds %= 60;
        std::ostringstream ss;
        ss << std::setw(2) << std::setfill('0') << minutes <<
              ":" << std::setw(2) << std::setfill('0') << seconds;
        return ss.str();
    };

    return formatTime(currentPos) + " / " + formatTime(totalDuration);
}
