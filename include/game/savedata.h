#pragma once

#include <types.h>

struct SaveData {
    struct Header {
        char magic[4];
        u8 version1;
        u8 version2;
        u8 version3;
        u8 lastUsedSlot;
        bool nsluNotifSent;
        u8 controlScheme;
        u8 padding[2];
        u32 CRC32;
    };

    struct MapLocation {
        u8 worldNumber;
        u8 sectionID;
        u8 nodeID;
    };

    struct AmbushEnemy {
        MapLocation location;
        u8 _3;
        u8 _4;
    };

    struct AmbushData {
        AmbushEnemy world1Ambush[2];
        AmbushEnemy world2Ambush[3];
        AmbushEnemy world3Ambush[2];
        AmbushEnemy world4Ambush[5];
        AmbushEnemy world5Ambush[3];
        AmbushEnemy world7Ambush[3];
        u8 _5A[18];
        u8 _6C;
    };

    struct Statistics {
        u32 coinsCollected;
        u32 starcoinsCollected;
        u32 goalsReached;
        u32 timesApplauded;
        u32 boostBlockDistance;
        u32 miniBoostBlockDistance;
        u32 nabbitsCaught;
        u32 goombasStomped;
        u32 itemsCollected;
        u32 goalsReachedWithYoshi;
        u32 goalsReachedWithBabyYoshi;
        u32 livesEarnedAtGoal;
        u32 fireworksAtGoal;
        u32 lifemoonsCollected;
    };

    struct SaveSlot {
        bool saveSlotUsed;
        u8 prevPlayerNum;
        u8 coinCount;
        bool switchState;
        MapLocation mapLocation1;
        MapLocation mapLocation2;
        u8 _A;
        u8 _B;
        u8 playerLifeCount[4];
        u8 playerCharSelection[4];
        u8 playerPowerupState[4];
        u8 playerGameOverCount[4];
        u16 finishedWorldsFlags;
        u8 completionFlags;
        u8 _1F;
        Vec3f _20;
        u8 _2C;
        u8 _2D;
        u8 _2E;
        u8 _2F;
        u32 score;
        u8 _34[16];
        u16 creditsHighscore;
        MapLocation airshipLocation;
        u8 nabbitWorldNum[2];
        u8 _4B;
        u8 _4C;
        u8 _4D;
        u8 _4E;
        u8 _4F;
        u8 _50;
        u8 _51;
        u8 _52;
        u8 _53;
        u8 _54;
        u8 availableBabyYoshiFlags;
        u8 activeBabyYoshi;
        u8 _57;
        u8 _58;
        u8 _59;
        u8 balloonBabyYoshiReappearCounter;
        u8 bubbleBabyYoshiReappearCounter;
        u8 _5C[4];
        u8 ambushItems[4];
        u8 nabbitRelated[7];
        u8 levelCompletionFlags[123];
        u8 levelDeathCounter[62];
        u8 levelStarCoins[41];
        u8 inventoryItems[10];
        AmbushData ambushData;
        Statistics statistics;
        u8 caughtNabbitFlags;
        u8 padding[3];
        u32 CRC32;
    };

    struct Challenge {
        u8 completionState; // TODO: check if this is a bool
        u8 completedPlayer;
        u8 unk1[2];
        u8 miiData[0x60];   // TODO: add this struct
        u32 highscore;
        u32 replayCRC32;
    };

    struct ChallengeData {
        bool isStructValid;
        u8 medal[5];
        u8 _6;
        u8 _7;
        Challenge challenges[80];
        u8 _21C8[0x1440];
        u32 CRC32;
    };

    struct BoostRushData {
        u8 _0;
        u8 _1;
        u8 _2;
        u8 _3;
        u32 highscore[32];  // Stored in hundredths of a second
        u8 _84[32];
        u32 CRC32;
    };
    
    struct CoinEditCoin {
        u8 area;
        u8 zone;
        bool isValid;
        u8 unk1;
        u16 xPos;
        u16 yPos;
    };

    struct CoinEditStarCoin {
        u8 area;
        u8 zone;
        u8 _2;
        u8 _3;
        f32 xPos;
        f32 yPos;
    };

    struct CoinEditLevel {
        CoinEditCoin coins[300];
        CoinEditStarCoin starCoins[3];
    };

    struct CoinEditData {
        CoinEditLevel levels[10];
        u8 unlockedLevels[12];
        u32 CRC32;
    };

    struct TelemetryStatistics {
        u32 secondsPlayed;
        u32 secondsInStoryMode;
        u32 levelsPlayed;
        u32 levelsPlayedSingleplayer;
        u32 levelsPlayedTwoPlayers;
        u32 levelsPlayedThreePlayers;
        u32 levelsPlayedFourPlayers;
        u32 _1C;
        u32 nabbitsChased;
        u32 superGuidesSeen;
        u32 boostRushGamesPlayed;
        u32 boostRushGamesPlayedSingleplayer;
        u32 boostRushGamesPlayedTwoPlayers;
        u32 boostRushGamesPlayedThreePlayers;
        u32 boostRushGamesPlayedFourPlayers;
        u32 _3C;
        u32 _40;
        u32 coinBattlesPlayed;
        u32 coinBattlesPlayedSingleplayer;
        u32 coinBattlesPlayedTwoPlayers;
        u32 coinBattlesPlayedThreePlayers;
        u32 coinBattlesPlayedFourPlayers;
        u32 _58;
        u32 _5C;
        u32 editedCoinBattleLevelsPlayed;
        u32 challengesPlayed;
        u32 _68;
        u32 challengeReplaysWatched;
        u32 boostModeChallengesPlayed;
        u32 nsluLevelsPlayed;
        u32 _78;
        u32 _7C;
        u32 powerupsUsed;
        u8 _84;
        u8 _85;
        u8 _86;
        u8 _87;
        u8 _88;
        u8 _89;
        u8 goldMedalsEarned;
        u8 silverMedalsEarned;
        u8 bronzeMedalsEarned;
        u8 boostModeChallengesCompleted;
        u8 _8E;
        u8 _8F;
        u32 CRC32;
    };

    struct MiiData {
        u8 numEntries;
        u8 FFLCreateIDEntries[620];
        u8 padding[3];
        u32 CRC32;
    };

    Header header;
    SaveSlot saveSlots[3];
    SaveSlot nsluSaveSlots[3];
    SaveSlot quickSaveSlots[3];
    SaveSlot nsluQuickSaveSlots[3];
    ChallengeData challengeData;
    BoostRushData boostRushData;
    CoinEditData coinEditData;
    TelemetryStatistics telemetryStats;
    MiiData miiData;
};
