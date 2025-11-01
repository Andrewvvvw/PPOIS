#include "AudioFile.h"
#include <iostream>

AudioFile::AudioFile(const std::string& path, unsigned long size, const std::string& fileFormat)
    : filePath(path), fileSize(size), format(fileFormat) {
}

bool AudioFile::validate() const {

    if (fileSize == 0) {
        std::cerr << "Error: File size is 0" << std::endl;
        return false;
    }

    const std::string supportedFormats[] = {"MP3", "WAV", "AAC", "FLAC"};
    bool formatSupported = false;
    for (const auto& supported : supportedFormats) {
        if (format == supported) {
            formatSupported = true;
            break;
        }
    }

    if (!formatSupported) {
        std::cerr << "Error: Unsupported audio format: " << format << std::endl;
        return false;
    }

    return true;
}
