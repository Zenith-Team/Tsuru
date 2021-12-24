#include "game/profile/profile.h"

// Add archive links for unused actors without resources
PROFILE_RESOURCES(Profile::spriteToProfileList[312], Profile::LoadResourcesAt_Course, "cube_kinoko");
PROFILE_RESOURCES(Profile::spriteToProfileList[463], Profile::LoadResourcesAt_Course, "bowser_switch");
PROFILE_RESOURCES(Profile::spriteToProfileList[199], Profile::LoadResourcesAt_Course, "block_light", "light_block");

// Additional resources for existing actors
PROFILE_RESOURCES(Profile::spriteToProfileList[229], Profile::LoadResourcesAt_Course, "huhu", "huhd");
