#include "UnitTest++.h"
#include "../../src/AudioCollection/DownloadManager/DownloadManager.h"

SUITE(DownloadManagerTest) {
    TEST(AddToQueue_Success) {
        DownloadManager dm("test_downloads");
                CHECK(dm.addToQueue("file1.mp3"));
    }

    TEST(AddToQueue_FullQueue) {
        DownloadManager dm("test_downloads", 2);
                CHECK(dm.addToQueue("file1.mp3"));
                CHECK(dm.addToQueue("file2.mp3"));
                CHECK(!dm.addToQueue("file3.mp3"));
    }

    TEST(ProcessQueue_Empty) {
        DownloadManager dm("test_downloads");
                CHECK(!dm.processQueue());
    }

    TEST(ProcessQueue_Success) {
        DownloadManager dm("test_downloads");
        dm.addToQueue("file1.mp3");
                CHECK(dm.processQueue());
                CHECK(dm.isFileDownloaded("file1.mp3"));
    }

    TEST(ProcessQueue_MultipleFiles) {
        DownloadManager dm("test_downloads");
        dm.addToQueue("file1.mp3");
        dm.addToQueue("file2.mp3");

                CHECK(dm.processQueue());
                CHECK(dm.isFileDownloaded("file1.mp3"));

                CHECK(dm.processQueue());
                CHECK(dm.isFileDownloaded("file2.mp3"));

                CHECK(!dm.processQueue());
    }

    TEST(IsFileDownloaded_NotInQueue) {
        DownloadManager dm("test_downloads");
                CHECK(!dm.isFileDownloaded("nonexistent.mp3"));
    }

    TEST(IsFileDownloaded_InQueueNotDownloaded) {
        DownloadManager dm("test_downloads");
        dm.addToQueue("file1.mp3");
                CHECK(!dm.isFileDownloaded("file1.mp3"));
    }

    TEST(IsFileDownloaded_Downloaded) {
        DownloadManager dm("test_downloads");
        dm.addToQueue("file1.mp3");
        dm.processQueue();
                CHECK(dm.isFileDownloaded("file1.mp3"));
    }

    TEST(ConcurrentDownloadsLimit) {
        DownloadManager dm("test_downloads", 2);
                CHECK(dm.addToQueue("file1.mp3"));
                CHECK(dm.addToQueue("file2.mp3"));
                CHECK(!dm.addToQueue("file3.mp3"));

        dm.processQueue();
                CHECK(!dm.addToQueue("file3.mp3"));
    }

    TEST(ProcessQueue_AlreadyDownloaded) {
        DownloadManager dm("test_downloads");
        dm.addToQueue("file1.mp3");
        dm.processQueue();

                CHECK(!dm.processQueue());
                CHECK(dm.isFileDownloaded("file1.mp3"));
    }

}