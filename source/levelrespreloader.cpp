#include "game/level/level.h"
#include "game/level/levelinfo.h"
#include "game/resource/util.h"
#include "tsuru/actors/stringbank.h"
#include "tsuru/strybble.h"
#include "ghs.h"
#include "log.h"

#define ModelLoaderSpriteID 744
#define StringBankSpriteID 745

void levelResPreloader() {
    Level::Area::Sprite* modelLoaderSpr = nullptr;
    Level::Area::Sprite* strBankSpr = nullptr;
    Level::Area* area = Level::instance()->getArea(LevelInfo::instance()->area);
    while (modelLoaderSpr = area->getSprite(ModelLoaderSpriteID, modelLoaderSpr)) {
        u8 modelFileBankID = modelLoaderSpr->settings1 >> 0x18 & 0xFF;
        u8 modelNameBankID = modelLoaderSpr->settings1 >> 0x10 & 0xFF;
        if (modelFileBankID == 0 || modelNameBankID == 0)
            continue;

        char modelFile[49] = { 0 };
        char modelName[49] = { 0 };

        while (strBankSpr = area->getSprite(StringBankSpriteID, strBankSpr)) {
            u8 strBankID = strBankSpr->initialStateFlag;

            if (strBankID == 0 || (strBankID != modelFileBankID && strBankID != modelNameBankID) || strBankSpr->layer != StringBank::Type_Primary)
                continue;

            char string[49]       = { 0 };
            char strPrimary[17]   = { 0 };
            char strSecondary[17] = { 0 };
            char strLast[17]      = { 0 };
            StringBank::getPrimaryString(strBankSpr, strPrimary);
            StringBank::getAdjacentStrings(strBankSpr, strSecondary, strLast);
            StringBank::constructFullString(string, strPrimary, strSecondary, strLast);

            if (strBankID == modelFileBankID)
                strncpy(modelFile, string, 49);
            
            if (strBankID == modelNameBankID)
                strncpy(modelName, string, 49);
        };

        if (modelFile[0] == '\0' || modelName[0] == '\0')
            continue;

        char modelFilePath[64] = { 0 };
        __os_snprintf(modelFilePath, 64, "actor/%s.szs", modelFile);
        loadResource(modelFile, modelFilePath, true, "LevelPreloader");
    };
}
