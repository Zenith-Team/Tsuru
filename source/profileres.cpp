#include "game/profile/profile.h"

// Add archive links for unused actors without resources
PROFILE_RESOURCES(Profile::sprite(312), Profile::LoadResourcesAt::Course, "cube_kinoko");
PROFILE_RESOURCES(Profile::sprite(463), Profile::LoadResourcesAt::Course, "bowser_switch");
PROFILE_RESOURCES(Profile::sprite(199), Profile::LoadResourcesAt::Course, "block_light", "light_block");

// Additional resources
PROFILE_RESOURCES(ProfileID::Player, Profile::LoadResourcesAt::Boot, "MarioMdl", "LuigiMdl", "KinopioMdl", "MiiMdl", "CommonAnm", "LuigiAnm", "KinopioAnm", "MiiAnm", "EF_HipdropEX", /* Custom: */ "hmrpy");
