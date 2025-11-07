SleepTimer 3 8 → 

SortEngine 2 2 →

AudioCollection 3 3 → User AdManager Playlist

FilterEngine 5 4 → AudioCollection Playlist

AudioSettings 4 8 → 

FullScreenPlayer 5 3 → Audio

PlayerHistory 4 4 → Audio

PlayerQueue 4 10 → Audio

PlayingNowPanel 5 7 → Audio

PlayStatistics 3 4 → Audio

WidgetPlayer 4 8 → Audio

AudioPlayer 6 8 → PlayerQueue PlayerHistory PlayingNowPanel AudioSettings Audio

User 4 10 → AudioCollection

RegisteredUser 6 13 → SocialFunctionsManager SubscriptionManager UserProfile User FavoriteList Audio

UserStatistics 0 1 → RegisteredUser AudioCollection

UserProfile 4 6 → RegisteredUser 

SubscriptionManager 3 3 → RegisteredUser UserWallet

UserWallet 3 6 → RegisteredUser Payment

Payment 2 0 → 

SongWriter 2 4 → MusicTrack

SocialFunctionsManager 4 7 → RegisteredUser Audio 

RecordLabel 2 3 → Artist

RadioHost 3 7 → Radio

Producer 2 4 → MusicTrack

Podcaster 2 4 → Podcast

Lecturer 3 6 → AudioLecture

Broadcaster 4 11 → AudioBook

BookAuthor 3 10 → AudioBook

Artist 5 12 → Album MusicTrack TrackRemix

Guest 2 7 →  

SearchEngine 1 2 → AudioCollection

DownloadManager 3 3 → 

CollectionStatistics 3 3 → AudioCollection

AuthorizationManager 3 2 → RegisteredUser

AudioUploader 3 5 → AudioFile

AdManager 2 4 → Advertisement User

Advertisement 3 4 → 

Audio 3 5 →

Radio 3 8 → RadioHost

Podcast 2 3 → Podcaster

Playlist 5 11 → Audio RegisteredUser

FavoriteList 1 3 → Audio

EventRecord 3 3 → Artist

AudioFile 3 4 → 

AudioCourse 5 14 → AudioLecture 

AudioLecture 5 10 → Lecturer

AudioBook 4 10 → BookAuthor Broadcaster

Album 6 10 → MusicTrack TrackRemix

MusicTrack 4 6 → SongWriter 

TrackRemix 3 4 → 

Классы: 50
Поля: 167
Поведения: 297
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