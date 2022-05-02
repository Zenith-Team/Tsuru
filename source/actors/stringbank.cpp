#include "tsuru/actors/stringbank.h"
#include "game/actor/stage/stageactor.h"
#include "tsuru/strybble.h"
#include "log.h"
#include "ghs.h"

const ActorInfo StringBankActorInfo = {
    Vec2i(0, 0), Vec2i(0, 0), Vec2i(0, 0), 0, 0, 0, 0, ActorInfo::Flag_IgnoreSpawnRange
};

const Profile StringBankProfile(&StringBank::build, ProfileID::StringBank, "StringBank", &StringBankActorInfo);

StringBank::StringBank(const ActorBuildInfo* buildInfo)
    : Actor(buildInfo)
    , eventID1(buildInfo->eventID1)
    , eventID2(buildInfo->eventID2)
    , layer(buildInfo->layer)
    , bankID(this->initialStateFlag)
{ }

Actor* StringBank::build(const ActorBuildInfo* buildInfo) {
    return new StringBank(buildInfo);
}

u32 StringBank::onCreate() {
    if (this->bankID == 0) return 2;

    __memzero(this->string, 49);
    if (this->layer != StringBank::Type_Primary) {
        LOG(
            "%s(StringBank #%i) Initialized as %s bank for primary bank #%i.", LogColor::LightCyan, this->bankID,
            this->layer == StringBank::Type_Ending ? "ending" : "secondary",
            this->layer == StringBank::Type_Ending ? this->bankID - 2 : this->bankID - 1
        );
        return 1;
    }
    
    char strPrimary[17]   = { 0 };
    char strSecondary[17] = { 0 };
    char strLast[17]      = { 0 };
    StringBank::getPrimaryString(this, strPrimary);
    StringBank::getAdjacentStrings(this, strSecondary, strLast);
    StringBank::constructFullString(this->string, strPrimary, strSecondary, strLast);
    
    LOG("%s(StringBank #%i) Initialized with string: %s", LogColor::LightCyan, this->bankID, this->string);
    return 1;
}
