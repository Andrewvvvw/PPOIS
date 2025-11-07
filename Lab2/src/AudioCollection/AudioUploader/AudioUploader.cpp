#include "AudioUploader.h"
#include <algorithm>
#include "../../Audio/AudioFile/AudioFile.h"

AudioUploader::AudioUploader(const std::string& directory, size_t maxSizeKB,
                             const std::vector<std::string>& formats)
        : uploadDirectory(directory), maxFileSizeKB(maxSizeKB), allowedFormats(formats) {
}

bool AudioUploader::uploadAudio(AudioFile audioFile) {

    std::string filePath = audioFile.getFilePath();
    if (!validateFile(audioFile)) {
        return false;
    }
    return true;
}

bool AudioUploader::validateFile(AudioFile audioFile) const {
    std::string extension = audioFile.getFilePath().substr(audioFile.getFilePath().find_last_of('.') + 1);
    bool validExtension = std::find(allowedFormats.begin(),
                                    allowedFormats.end(),
                                    extension) != allowedFormats.end();

    if (!validExtension) {
        return false;
    }

    return audioFile.getFileSize() <= maxFileSizeKB;
}

const std::string& AudioUploader::getUploadDirectory() const {
    return uploadDirectory;
}

size_t AudioUploader::getMaxFileSizeKB() const {
    return maxFileSizeKB;
}

const std::vector<std::string>& AudioUploader::getAllowedFormats() const {
    return allowedFormats;
}
