#include "musicplayer.h"

bool MusicPlayer::isValidStrmID(s32 strmID) {
    return strmID < MusicPlayer::NUM_MUSIC_LIST;
}


const char* MusicPlayer::getStrmNameForID(s32 strmID) {
    bool valid = MusicPlayer::isValidStrmID(strmID);
    if (!valid) {
        return 0;
    }

    const char* strName;

    bool isHurryUp = MusicPlayer::shouldHurryUp();
    if (isHurryUp) {
        strName = MusicPlayer::strmListFast[strmID];
    }

    else {
        strName = MusicPlayer::strmListNormal[strmID];
    }

    return strName;
}


const char* MusicPlayer::getSeqNameForID(s32 strmID) {
    bool valid = MusicPlayer::isValidStrmID(strmID);
    if (!valid) {
        return 0;
    }

    const char* seqName;

    bool isHurryUp = MusicPlayer::shouldHurryUp();
    if (isHurryUp) {
        seqName = MusicPlayer::seqListFast[strmID];
    }

    else {
        seqName = MusicPlayer::seqListNormal[strmID];
    }

    return seqName;
}

const char* MusicPlayer::strmListNormal[MusicPlayer::NUM_MUSIC_LIST] = {
    nullptr,
    "STRM_BGM_CHIJOU",
    "STRM_BGM_CHIKA",
    "STRM_BGM_WATER",
    "STRM_BGM_ATHLETIC",
    "STRM_BGM_OBAKE",
    "STRM_BGM_SABAKU",
    "STRM_BGM_YUKI",
    "STRM_BGM_KAZAN",
    "STRM_BGM_TORIDE",
    "STRM_BGM_SHIRO",
    "STRM_BGM_HIKOUSEN",
    "STRM_BGM_BONUS",
    "STRM_BGM_ROAD_TO_LAST",
    "STRM_BGM_TORIDE_BOSS",
    "STRM_BGM_SHIRO_BOSS",
    "STRM_BGM_MINIGAME",
    "STRM_BGM_HIKOUSEN_BOSS",
    "STRM_BGM_MORI",
    "STRM_BGM_MG_BTL",
    "STRM_BGM_SANBASHI",
    "STRM_BGM_KAZAN_TIKA",
    "STRM_BGM_SHADOW",
    "STRM_BGM_STAFF_CREDIT",
    "STRM_BGM_HIKOUSEN_ROUKA",
    "STRM_BGM_LAST_BOSS",
    "STRM_BGM_LAST_BOSS2",
    "STRM_BGM_LAST_BOSS2_HARP",
    "WSD_BGM_SHIRO_LAST",
};

const char* MusicPlayer::strmListFast[MusicPlayer::NUM_MUSIC_LIST] = {
    nullptr,
    "STRM_BGM_CHIJOU_FAST",
    "STRM_BGM_CHIKA_FAST",
    "STRM_BGM_WATER_FAST",
    "STRM_BGM_ATHLETIC_FAST",
    "STRM_BGM_OBAKE_FAST",
    "STRM_BGM_SABAKU_FAST",
    "STRM_BGM_YUKI_FAST",
    "STRM_BGM_KAZAN_FAST",
    "STRM_BGM_TORIDE_FAST",
    "STRM_BGM_SHIRO_FAST",
    "STRM_BGM_HIKOUSEN_FAST",
    "STRM_BGM_BONUS_FAST",
    "STRM_BGM_ROAD_TO_LAST_FAST",
    "STRM_BGM_TORIDE_BOSS_FAST",
    "STRM_BGM_SHIRO_BOSS_FAST",
    "STRM_BGM_MINIGAME",
    "STRM_BGM_HIKOUSEN_BOSS_FAST",
    "STRM_BGM_MORI_FAST",
    "STRM_BGM_MG_BTL",
    "STRM_BGM_SANBASHI_FAST",
    "STRM_BGM_KAZAN_TIKA_FAST",
    "STRM_BGM_SHADOW",
    "STRM_BGM_STAFF_CREDIT",
    "STRM_BGM_HIKOUSEN_ROUKA_FAST",
    "STRM_BGM_LAST_BOSS_FAST",
    "STRM_BGM_LAST_BOSS2_FAST",
    "STRM_BGM_LAST_BOSS2_HARP",
    "WSD_BGM_SHIRO_LAST_FAST",
};

const char* MusicPlayer::seqListNormal[MusicPlayer::NUM_MUSIC_LIST] = {
    nullptr,
    "SEQ_BGM_CHIJOU_V",
    "SEQ_BGM_CHIKA_V",
    "SEQ_BGM_WATER_V",
    "SEQ_BGM_ATHLETIC_V",
    "SEQ_BGM_OBAKE_V",
    "SEQ_BGM_SABAKU_V",
    "SEQ_BGM_YUKI_V",
    "SEQ_BGM_KAZAN_V",
    "SEQ_BGM_TORIDE_V",
    "SEQ_BGM_SHIRO_V",
    nullptr,
    "SEQ_BGM_BONUS_V",
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    "SEQ_BGM_MORI_V",
    nullptr,
    "SEQ_BGM_SANBASHI_V",
    "SEQ_BGM_KAZAN_TIKA_V",
    nullptr,
    "SEQ_BGM_STAFFCREDIT_V",
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
};

const char* MusicPlayer::seqListFast[MusicPlayer::NUM_MUSIC_LIST] = {
    nullptr,
    "SEQ_BGM_CHIJOU_FAST_V",
    "SEQ_BGM_CHIKA_FAST_V",
    "SEQ_BGM_WATER_FAST_V",
    "SEQ_BGM_ATHLETIC_FAST_V",
    nullptr,
    "SEQ_BGM_SABAKU_FAST_V",
    "SEQ_BGM_YUKI_FAST_V",
    "SEQ_BGM_KAZAN_FAST_V",
    "SEQ_BGM_TORIDE_FAST_V",
    "SEQ_BGM_SHIRO_FAST_V",
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    "SEQ_BGM_MORI_FAST_V",
    nullptr,
    "SEQ_BGM_SANBASHI_FAST_V",
    "SEQ_BGM_KAZAN_TIKA_FAST_V",
    nullptr,
    "SEQ_BGM_STAFFCREDIT_V",
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
};
