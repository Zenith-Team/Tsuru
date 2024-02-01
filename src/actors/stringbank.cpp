#include "tsuru/actor/stringbank.h"
#include "game/actor/stage/stageactor.h"
#include "tsuru/strybble.h"
#include "tsuru/log.h"

const ActorInfo StringBankActorInfo = {
    sead::Vector2i(0, 0), sead::Vector2i(0, 0), sead::Vector2i(0, 0), 0, 0, 0, 0, ActorInfo::Flags::IgnoreSpawnRange
};

REGISTER_PROFILE(StringBank, ProfileID::StringBank, "StringBank", &StringBankActorInfo);

StringBank::StringBank(const ActorBuildInfo* buildInfo)
    : Actor(buildInfo)
    , eventID1(buildInfo->eventID1)
    , eventID2(buildInfo->eventID2)
    , layer(buildInfo->layer)
    , bankID(this->initialStateFlag)
{ }

u32 StringBank::onCreate() {
    if (this->bankID == 0) return 2;

    OSBlockSet(this->string, 0, 49);
    if (this->layer != StringBank::Type::Primary) {
        PRINT(LogColor::LightCyan, "(StringBank #", this->bankID, ") Initialized as ", this->layer == StringBank::Type::Ending ? "ending" : "secondary", " bank for primary bank #", this->layer == StringBank::Type::Ending ? this->bankID - 2 : this->bankID - 1);
        return 1;
    }

    char strPrimary[17]   = { 0 };
    char strSecondary[17] = { 0 };
    char strLast[17]      = { 0 };
    StringBank::getPrimaryString(this, strPrimary);
    StringBank::getAdjacentStrings(this, strSecondary, strLast);
    StringBank::constructFullString(this->string, strPrimary, strSecondary, strLast);

    PRINT(LogColor::LightCyan, "(StringBank #", this->bankID, ") Initialized with string: ", this->string);

    return 1;
}
