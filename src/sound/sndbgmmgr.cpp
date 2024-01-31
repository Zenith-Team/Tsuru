#include "game/sound/sndbgmmgr.h"

bool SndBgmMgr::isValidStrmID(s32 strmID) {
    return strmID < MusicIndex::Num;
}

const char* SndBgmMgr::getStrmName(s32 strmID) {
    if (!this->isValidStrmID(strmID))
        return nullptr;

    const char* strmName;

    if (this->shouldHurryUp())
        strmName = strmListFast[strmID];
    else
        strmName = strmListNormal[strmID];

    return strmName;
}

const char* SndBgmMgr::getSeqName(s32 seqID) {
    if (!this->isValidStrmID(seqID))
        return nullptr;

    const char* seqName;

    if (this->shouldHurryUp())
        seqName = seqListFast[seqID];
    else
        seqName = seqListNormal[seqID];

    return seqName;
}

// Remember to add your new music to the MusicIndex enum in SndBgmMgr.h, and add it to every array below

const char* SndBgmMgr::strmListNormal[SndBgmMgr::MusicIndex::Num] = {
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

const char* SndBgmMgr::strmListFast[SndBgmMgr::MusicIndex::Num] = {
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

const char* SndBgmMgr::seqListNormal[SndBgmMgr::MusicIndex::Num] = {
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

const char* SndBgmMgr::seqListFast[SndBgmMgr::MusicIndex::Num] = {
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
