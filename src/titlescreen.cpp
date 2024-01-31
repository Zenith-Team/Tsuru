#include "game/level/levelinfo.h"
#include "game/savemgr.h"
#include "log.h"

void LevelInfo::setTitlescreenThemeEntrance() {
    switch (SaveMgr::getLastUsedSaveSlot().csPlayerLocation.worldNumber) {
        case 0: this->setDestEntrance(0); return; // Acorn Plains
        case 1: this->setDestEntrance(1); return; // Layer-Cake Desert
        case 2: this->setDestEntrance(2); return; // Sparkling Waters
        case 3: this->setDestEntrance(3); return; // Frosted Glacier
        case 4: this->setDestEntrance(4); return; // Soda Jungle
        case 5: this->setDestEntrance(5); return; // Rock-Candy Mines
        case 6: this->setDestEntrance(6); return; // Meringue Clouds
        case 7: this->setDestEntrance(7); return; // Peach's Castle
        case 8: this->setDestEntrance(8); return; // Superstar Road
        case 9: this->setDestEntrance(9); return; // Secret Island

        default: PRINT("Game saved in unknown world"); this->setDestEntrance(0); return;
    }
}
