#include "sead/safestring.h"
#include "log.h"

class AchievementManager {
public:
    struct trackers_t {
        bool tripleMoonCollected;
    }
    
    static trackers;

    // Achievements
    static void achieveGet3Up();

    static void renderAchieveBox(const sead::SafeString& panePath);
};

AchievementManager::trackers_t AchievementManager::trackers = {
    false
};

void AchievementManager::achieveGet3Up() {
    if (trackers.tripleMoonCollected) {
        return;
    }

    trackers.tripleMoonCollected = true;
    LOG("Achievement unlocked: 3 Up!");
}
