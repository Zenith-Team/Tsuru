#pragma once

#include <log.h>
#include "ffl.h"

struct SaveData { // Size: 0xB134
public:
    enum GameCompletionFlag {
        GameCompletionFlag_Unknown1                     = 0x1,
        GameCompletionFlag_AllLevels                    = 0x2,
        GameCompletionFlag_Unknown2                     = 0x4,
        GameCompletionFlag_AllStarCoins                 = 0x8,
        GameCompletionFlag_AllExits                     = 0x10
    };

    enum WorldCompletionFlag {
        WorldCompletionFlag_OpeningCutscenePlayed       = 0x1,
        WorldCompletionFlag_World1Complete              = 0x2,
        WorldCompletionFlag_World2Complete              = 0x4,
        WorldCompletionFlag_World3Complete              = 0x8,
        WorldCompletionFlag_World4Complete              = 0x10,
        WorldCompletionFlag_World5Complete              = 0x20,
        WorldCompletionFlag_World6Complete              = 0x40,
        WorldCompletionFlag_World7Complete              = 0x80,
        WorldCompletionFlag_World8Complete              = 0x100,
        WorldCompletionFlag_AllWorldsComplete           = 0x1FF
    };

    enum BabyYoshisAvailableFlag {
        BabyYoshisAvailableFlag_World1PinkBabyYoshi     = 0x1,
        BabyYoshisAvailableFlag_World3PinkBabyYoshi     = 0x2,
        BabyYoshisAvailableFlag_World4BlueBabyYoshi     = 0x4,
        BabyYoshisAvailableFlag_World6BlueBabyYoshi     = 0x8,
        BabyYoshisAvailableFlag_AllBabyYoshis           = 0xF
    };

    enum ActiveBabyYoshi {
        ActiveBabyYoshi_World1PinkBabyYoshi             = 0,
        ActiveBabyYoshi_World3PinkBabyYoshi             = 1,
        ActiveBabyYoshi_World4BlueBabyYoshi             = 2,
        ActiveBabyYoshi_World6BlueBabyYoshi             = 3,
        ActiveBabyYoshi_NoBabyYoshi                     = 4
    };

    enum LevelCompletionFlag { // TODO: More research, not all values are here, some are incomplete
        LevelCompletionFlag_Locked                      = 0x0,
        LevelCompletionFlag_Unlocked                    = 0x1,
        LevelCompletionFlag_PlayedOnce                  = 0x2,
        LevelCompletionFlag_ForeverUnlockedToadHouse    = 0x3,
        LevelCompletionFlag_AmbushCleared               = 0x42,
        LevelCompletionFlag_ClearedOrUsedToadHouse      = 0x43,
        LevelCompletionFlag_ClearedOrSecretExitCleared  = 0xC3,
    };

    enum LevelStarCoinsCollected { // TODO: More research, not all values are here
        LevelStarCoinsCollected_None                    = 0x0,
        LevelStarCoinsCollected_All                     = 0x77
    };

    enum InventoryItem { //? The missing 0x4 entry is not a mistake, it doesn't seem to be anything.
        InventoryItem_Mushroom                          = 0x0,
        InventoryItem_FireFlower                        = 0x1,
        InventoryItem_SuperStar                         = 0x2,
        InventoryItem_IceFlower                         = 0x3,

        InventoryItem_Propeller                         = 0x5,
        InventoryItem_Mini                              = 0x6,
        InventoryItem_Penguin                           = 0x7,
        InventoryItem_Acorn                             = 0x8,
        InventoryItem_PAcorn                            = 0x9,
        InventoryItem_NoItem                            = 0xE
    };

public:
    struct Header {
        char magic[4];          // RPSD
        u8 versionMajor;        // Always 1
        u8 versionMinor;        // Always 0
        u8 versionPatch;        // Always 2 on NSMBU 1.3, always 0 on NSMBU 1.0
        u8 lastSessionSaveSlot; // 0-indexed, not limited to 0-2, meaning of higher values need more research
        bool nsluNotifSent;     // Field exclusive to NSMBU 1.3
        u8 buttonScheme;        // 0: Controls 1 (YX/AB), 1: Controls 2 (YB/AX)
        u8 padding[2];
        u32 CRC32;
    };

    static_assert(sizeof(SaveData::Header) == 0x10, "SaveData::Header size mismatch");

    struct CSLocation {
        u8 worldNumber;         // 0-indexed
        u8 sectionID;           // Per-world worldmap sections. Used for W5 Haunted section, W8 and W9.
        u8 pathNodeID;          // 0-indexed, does not follow the visible order of paths in-game at all.
    };

    static_assert(sizeof(SaveData::CSLocation) == 0x3, "SaveData::CSLocation size mismatch");

    struct AmbushEnemy {
        CSLocation location;
        u8 _3;
        u8 _4;
    };

    static_assert(sizeof(SaveData::AmbushEnemy) == 0x5, "SaveData::AmbushEnemy size mismatch");

    struct AmbushData { // TODO: Figure out which specific ambush each entry is
        AmbushEnemy world1Ambush[2];
        AmbushEnemy world2Ambush[3];
        AmbushEnemy world3Ambush[2];
        AmbushEnemy world4Ambush[5];
        AmbushEnemy world5Ambush[3];
        AmbushEnemy world7Ambush[3];
        u8 _5A[18];
        u8 _6C;
    };

    static_assert(sizeof(SaveData::AmbushData) == 0x6D, "SaveData::AmbushData size mismatch");

    struct Statistics {
        u32 coinsCollected;
        u32 starCoinsCollected;
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
        u32 lifeMoonsCollected;
    };

    static_assert(sizeof(SaveData::Statistics) == 0x38, "SaveData::Statistics size mismatch");

    struct SaveSlot {
        bool isNotEmpty;
        u8 lastSessionPlayerCount;
        u8 coinCount;
        u8 csActiveW6Switch;                // 0: Red Active, 1: Blue Active
        CSLocation csPlayerLocation;
        CSLocation csUnknownLocation;       // TODO: Unknown purpose
        u8 _A;
        u8 _B;
        u8 playerLifeCount[4];              // Order: Mario, Luigi, Blue Toad, Yellow Toad
        u8 playerCharacterSelection[4];     // TODO: Verify order
        u8 playerPowerupState[4];           // Order: Mario, Luigi, Blue Toad, Yellow Toad //* enum = PowerupBase::PowerupState
        u8 playerGameOverCount[4];          // Order: Mario, Luigi, Blue Toad, Yellow Toad
        u16 worldCompletionFlag;            //* enum = SaveData::WorldCompletionFlag
        u8 gameCompletionFlag;              //* enum = SaveData::GameCompletionFlag
        u8 _1F;
        Vec3f _20;
        u8 _2C;
        u8 _2D;
        u8 _2E;
        u8 _2F;
        u32 score;
        u8 _34[16];
        u16 creditsCoinHighscore;
        CSLocation csAirshipLocation;
        u8 nabbitWorldID[2];
        u8 _4B;
        u8 _4C;
        u8 _4D;
        u8 _4E; // babyYoshiItem (?)
        u8 _4F;
        u8 _50;
        u8 _51;
        u8 _52;
        u8 _53;
        u8 _54;
        u8 babyYoshisAvailableFlag;         //* enum = SaveData::BabyYoshisAvailableFlag
        u8 activeBabyYoshi;                 //* enum = SaveData::ActiveBabyYoshi
        u8 _57;
        u8 _58;
        u8 _59;
        u8 pinkBabyYoshiReappearCounter;
        u8 blueBabyYoshiReappearCounter;
        u8 ambushItemReappearCounter[4];    // TODO: Map out order*
        u8 ambushItems[4];                  // TODO: Figure out values, maybe PowerupStates but untested
        u8 remainingNabbitAttempts[7];      // TODO: Map out order*
        u8 levelCompletionFlag[123];        //* enum = SaveData::LevelCompletionFlag
        u8 levelDeathCounter[62];
        u8 levelStarCoinsCollected[41];     //* enum = SaveData::LevelStarCoinsCollected
        u8 inventoryItem[10];               //* enum = SaveData::InventoryItem
        AmbushData ambushData;
        Statistics statistics;
        u8 caughtNabbitFlags;               // TODO: Figure out flags
        u8 padding[3];
        u32 CRC32;
    };

    static_assert(sizeof(SaveData::SaveSlot) == 0x204, "SaveData::SaveSlot size mismatch");

    struct Challenge {
        u8 completionState;                 // TODO: check if this is a bool
        u8 completionPlayerUsed;            // TODO: Check which player each value is
        u16 _2;
        FFL::StoreData completionMiiUsed;
        u32 highscore;
        u32 replayCRC32;
    };

    static_assert(sizeof(SaveData::Challenge) == 0x6C, "SaveData::Challenge size mismatch");

    struct ChallengeData {
        bool exists;
        u8 categoryMedalsCount[5];          // TODO: Figure out categories
        u8 _6;
        u8 _7;
        Challenge challenges[80];           // TODO: Map out challenges
        u8 _21C8[0x1440];
        u32 CRC32;
    };

    static_assert(sizeof(SaveData::ChallengeData) == 0x360C, "SaveData::ChallengeData size mismatch");
    
    struct BoostRushData {
        u8 _0;
        u8 _1;
        u8 _2;
        u8 _3;
        u32 highscores[32];                 // Stored in hundredths of a second
        u8 _84[32];
        u32 CRC32;                          // _A4
    };

    static_assert(sizeof(SaveData::BoostRushData) == 0xA8, "SaveData::BoostRushData size mismatch");

    struct CoinEditCoin {
        u8 area;
        u8 zone;
        bool exists;
        u8 _3;
        u16 xPos;
        u16 yPos;
    };

    static_assert(sizeof(SaveData::CoinEditCoin) == 0x8, "SaveData::CoinEditCoin size mismatch");

    struct CoinEditStarCoin {
        u8 area;
        u8 zone;
        u8 _2;                              // Possibly "bool exists;" like in CoinEditCoin?
        u8 _3;
        f32 xPos;
        f32 yPos;
    };

    static_assert(sizeof(SaveData::CoinEditStarCoin) == 0xC, "SaveData::CoinEditStarCoin size mismatch");

    struct CoinEditLevel {
        CoinEditCoin coins[300];
        CoinEditStarCoin starCoins[3];
    };

    static_assert(sizeof(SaveData::CoinEditLevel) == 0x984, "SaveData::CoinEditLevel size mismatch");

    struct CoinEditData {
        CoinEditLevel levels[10];
        u8 unlockedLevels[12];
        u32 CRC32;
    };

    static_assert(sizeof(SaveData::CoinEditData) == 0x5F38, "SaveData::CoinEditData size mismatch");

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

    static_assert(sizeof(SaveData::TelemetryStatistics) == 0x94, "SaveData::TelemetryStatistics size mismatch");

    struct MiiData {
        u8 entriesCount;                // _0
        FFL::CreateID miiIDList[62];    // _1    (Total size: 0x26C)
        u8 padding[3];                  // _26D
        u32 CRC32;                      // _270
    } packed aligned(1);

    static_assert(sizeof(SaveData::MiiData) == 0x274, "SaveData::MiiData size mismatch");

public:
    Header header;                      // _0
    SaveSlot saveSlots[3];              // _10
    SaveSlot nsluSaveSlots[3];          // _61C
    SaveSlot quickSaveSlots[3];         // _C28
    SaveSlot nsluQuickSaveSlots[3];     // _1234
    ChallengeData challengeData;        // _1840
    BoostRushData boostRushData;        // _4E4C
    CoinEditData coinEditData;          // _4EF4
    TelemetryStatistics telemetryStats; // _AE2C
    MiiData miiData;                    // _AEC0
};

static_assert(sizeof(SaveData) == 0xB134, "SaveData size mismatch");
