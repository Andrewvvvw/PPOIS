#include "FullScreenPlayer.h"

FullScreenPlayer::FullScreenPlayer()
    : isPlaying(false), isFullScreen(true), playbackProgress(0.0f), isLyricsVisible(false) {}

void FullScreenPlayer::togglePlayPause() {
    isPlaying = !isPlaying;
}

void FullScreenPlayer::toggleLyrics() {
    isLyricsVisible = !isLyricsVisible;
}

void FullScreenPlayer::seek(float position) {
    if (position >= 0.0f && position <= 1.0f) {
        playbackProgress = position;
    }
}
