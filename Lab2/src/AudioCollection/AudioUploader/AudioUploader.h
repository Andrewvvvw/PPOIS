#ifndef LAB2_AUDIOUPLOADER_H
#define LAB2_AUDIOUPLOADER_H

#include <string>
#include <vector>

class AudioFile;

class AudioUploader {
private:
    std::string uploadDirectory;
    size_t maxFileSizeKB;
    std::vector <std::string> allowedFormats;

public:
    AudioUploader(const std::string& directory,
                  size_t maxSizeKB,
                  const std::vector<std::string>& formats);

    bool uploadAudio(AudioFile audioFile);
    bool validateFile(AudioFile audioFile) const;
};

#endif //LAB2_AUDIOUPLOADER_H