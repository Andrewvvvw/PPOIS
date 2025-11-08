SleepTimer 3 6 →

SortEngine 2 2 →

AudioCollection 3 2 → User AdManager Playlist

FilterEngine 5 2 → AudioCollection Playlist

AudioSettings 4 0 →

FullScreenPlayer 5 3 → Audio

PlayerHistory 4 4 → Audio

PlayerQueue 4 4 → Audio

PlayingNowPanel 5 2 → Audio

PlayStatistics 3 3 → Audio

WidgetPlayer 4 2 → Audio

AudioPlayer 6 6 → PlayerQueue PlayerHistory PlayingNowPanel AudioSettings Audio

User 4 4  → AudioCollection

RegisteredUser 6 8 → SocialFunctionsManager SubscriptionManager UserProfile User FavoriteList Audio

UserStatistics 0 1 → RegisteredUser AudioCollection

UserProfile 4 0 → RegisteredUser

SubscriptionManager 3 3 → RegisteredUser UserWallet

UserWallet 3 3 → RegisteredUser Payment

Payment 2 0 →

SongWriter 2 3 → MusicTrack

SocialFunctionsManager 4 4 → RegisteredUser Audio

RecordLabel 2 2 → Artist

RadioHost 3 2 → Radio

Producer 2 3 → MusicTrack

Podcaster 2 3 → Podcast

Lecturer 3 3 → AudioLecture

Broadcaster 4 5 → AudioBook

BookAuthor 3 5 → AudioBook

Artist 5 7 → Album MusicTrack TrackRemix

Guest 2 4 →

SearchEngine 1 2 → AudioCollection

DownloadManager 3 3 →

CollectionStatistics 3 1 → AudioCollection

AuthorizationManager 3 2 → RegisteredUser

AudioUploader 3 2 → AudioFile

AdManager 2 3 → Advertisement User

Advertisement 3 0 →

Audio 3 1 →

Radio 3 1 → RadioHost

Podcast 2 1 → Podcaster

Playlist 5 6 → Audio RegisteredUser

FavoriteList 1 2 → Audio

EventRecord 3 0 → Artist

AudioFile 3 1 →

AudioCourse 5 9 → AudioLecture

AudioLecture 5 5 → Lecturer

AudioBook 4 5 → BookAuthor Broadcaster

Album 6 5 → MusicTrack TrackRemix

MusicTrack 4 1 → SongWriter

TrackRemix 3 0 →

Классы: 50
Поля: 167
Поведения: 146
Ассоциации: 62
Исключения: 12

Исключения:

Exception 1 1 →

ExceptionIncorrectYear 0 0 →

ExceptionIncorrectDuration 0 0 →

ExceptionIncorrectPassword 0 0 →

ExceptionIncorrectEmail 0 0 →

ExceptionIncorrectUsername 0 0 →

ExceptionIncorrectAudioName 0 0 →

ExceptionIncorrectArtistName 0 0 →

ExceptionIncorrectAlbumTitle 0 0 →

ExceptionIncorrectTrack 0 0 →

ExceptionIncorrectChapterNumber 0 0 →

ExceptionIncorrectAudioBookChapters 0 0 →

ExceptionNotEnoughMoney 0 0 →