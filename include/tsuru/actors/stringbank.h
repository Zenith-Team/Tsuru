#pragma once

#include "game/actor/actor.h"
#include "game/actor/actormgr.h"
#include "game/level/level.h"
#include "game/level/levelinfo.h"
#include "tsuru/strybble.h"
#include "log.h"
#include "ghs.h"

class StringBank : public Actor {
    SEAD_RTTI_OVERRIDE_IMPL(StringBank, Actor);

public:
    ENUM_CLASS(Type,
        Primary,
        Secondary,
        Ending
    );

    StringBank(const ActorBuildInfo* buildInfo);
    virtual ~StringBank() { }

    u32 onCreate() override;

    // Extracts the actor's nybbles array into the provided buffer.
    static void getNybbles(StringBank* self, u8 out[12]) {
        u8 nybbles[12] = {
            self->eventID1,
            self->eventID2,
            self->settings1 >> 24 & 0xFF,
            self->settings1 >> 16 & 0xFF,
            self->settings1 >> 8 & 0xFF,
            self->settings1 & 0xFF,
            self->settings2 >> 24 & 0xFF,
            self->settings2 >> 16 & 0xFF,
            self->settings2 >> 8 & 0xFF,
            self->settings2 & 0xFF,
            self->movementID,
            self->linkID
        };
        __memzero(out, 12);
        for (u8 i = 0; i < 12; i++) out[i] = nybbles[i];
    }

    static void getPrimaryString(StringBank* self, char strPrimary[17]) {
        __memzero(strPrimary, 17);
        u8 nybbles[12]; StringBank::getNybbles(self, nybbles);
        strybble::loadFromNybbles(nybbles, 16, strPrimary);
        strybble::decode(strPrimary, 16);
    };

    static void getPrimaryString(Level::Area::Sprite* self, char strPrimary[17]) {
        __memzero(strPrimary, 17);
        strybble::loadFromNybbles(self, 16, strPrimary);
        strybble::decode(strPrimary, 16);
    };

    static void getAdjacentStrings(StringBank* self, char strSecondary[17], char strLast[17]) {
        __memzero(strSecondary, 17);
        __memzero(strLast, 17);
        ActorBuffer* actors = &ActorMgr::instance()->actors;
        for (u32 i = 0; i < actors->start.size; i++) {
            StringBank* strBank = sead::DynamicCast<StringBank, Actor>(actors->start[i]);
            if (strBank == self || !strBank) continue;
            u8 nybbles[12]; StringBank::getNybbles(strBank, nybbles);

            if (strBank->layer == StringBank::Type::Secondary && strBank->bankID == self->bankID + 1) {
                strybble::loadFromNybbles(nybbles, 16, strSecondary);
                strybble::decode(strSecondary, 16);
                strBank->isDeleted = true;
            }
            if (strBank->layer == StringBank::Type::Ending && strBank->bankID == self->bankID + 2) {
                strybble::loadFromNybbles(nybbles, 16, strLast);
                strybble::decode(strLast, 16);
                strBank->isDeleted = true;
            }
        }
    };

    static void getAdjacentStrings(Level::Area::Sprite* self, char strSecondary[17], char strLast[17]) {
        __memzero(strSecondary, 17);
        __memzero(strLast, 17);
        Level::Area::Sprite* strBankSpr = nullptr;
        Level::Area* area = Level::instance()->getArea(LevelInfo::instance()->area);
        while (strBankSpr = area->getSprite(745, strBankSpr)) {
            u8 strBankID = strBankSpr->initialStateFlag;
            if (strBankSpr == self) continue;

            if (strBankSpr->layer == StringBank::Type::Secondary && strBankID == self->initialStateFlag + 1) {
                strybble::loadFromNybbles(strBankSpr, 16, strSecondary);
                strybble::decode(strSecondary, 16);
            }
            if (strBankSpr->layer == StringBank::Type::Ending && strBankID == self->initialStateFlag + 2) {
                strybble::loadFromNybbles(strBankSpr, 16, strLast);
                strybble::decode(strLast, 16);
            }
        }
    };

    static void constructFullString(char out[49], char strPrimary[17], char strSecondary[17], char strLast[17]) {
        __memzero(out, 49);
        if (strSecondary[0] != '\0' && strLast[0] != '\0') __os_snprintf(out, 49, "%s%s%s", strPrimary, strSecondary, strLast);
        else if (strSecondary[0] != '\0') __os_snprintf(out, 49, "%s%s", strPrimary, strSecondary);
        else if (strLast[0] != '\0') __os_snprintf(out, 49, "%s%s", strPrimary, strLast);
        else __os_snprintf(out, 49, "%s", strPrimary);
    };

public:
    u8 eventID1;
    u8 eventID2;
    u8 layer;
    u8 bankID;
    char string[49];
};
