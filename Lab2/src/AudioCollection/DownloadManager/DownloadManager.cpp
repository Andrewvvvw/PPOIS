#include "DownloadManager.h"

DownloadManager::DownloadManager(const std::string& directory, size_t maxConcurrent)
        : downloadDirectory(directory), maxConcurrentDownloads(maxConcurrent) {
}

bool DownloadManager::addToQueue(const std::string& filename) {
    if (downloadQueue.size() >= maxConcurrentDownloads) {
        return false;
    }
    downloadQueue[filename] = false;
    return true;
}

bool DownloadManager::processQueue() {
    if (downloadQueue.empty()) {
        return false;
    }

    for (auto& [filename, isDownloaded] : downloadQueue) {
        if (!isDownloaded) {
            isDownloaded = true;
            return true;
        }
    }
    return false;
}

bool DownloadManager::isFileDownloaded(const std::string& filename) const {
    auto it = downloadQueue.find(filename);
    return it != downloadQueue.end() && it->second;
}