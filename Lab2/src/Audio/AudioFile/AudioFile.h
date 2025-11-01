#ifndef AUDIO_FILE_H
#define AUDIO_FILE_H

#include <string>
#include <memory>

class AudioFile {
private:
    std::string filePath;
    unsigned long fileSize;
    std::string format;

public:
    AudioFile(const std::string& path, unsigned long size, const std::string& fileFormat);

    const std::string& getFilePath() const { return filePath; }
    unsigned long getFileSize() const { return fileSize; }
    const std::string& getFormat() const { return format; }

    bool validate() const;
};

#endif // AUDIO_FILE_H
