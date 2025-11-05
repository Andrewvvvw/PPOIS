#ifndef LAB2_DOWNLOADMANAGER_H
#define LAB2_DOWNLOADMANAGER_H

#include <string>
#include <vector>
#include <map>

class DownloadManager {
private:
    std::string downloadDirectory;
    std::map<std::string, bool> downloadQueue;
    size_t maxConcurrentDownloads;

public:
    DownloadManager(const std::string& directory, size_t maxConcurrent = 3);
    bool addToQueue(const std::string& filename);
    bool processQueue();
    bool isFileDownloaded(const std::string& filename) const;
};

#endif //LAB2_DOWNLOADMANAGER_H