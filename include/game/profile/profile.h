#pragma once

#include "sead.h"
#include "types.h"
#include "profileid.h"
#include "preprocessor.h"

class BaseActor;
struct ActorInfo;
struct ActorBuildInfo;

class Profile {
public:
    Profile(BaseActor* (*BuildFunc)(const ActorBuildInfo*), u32 id, const sead::SafeString& rName, const ActorInfo* pActorInfo, u32 flags);

    static Profile* get(u32 id);
    static s16 getPriority(u32 id);
    static u8 getHasResources(u32 id);
    static u8 getResourceCount(u32 id);
    static const sead::SafeString* getResourceList(u32 id);

    static u32 getNumProfiles();

    static u32 spriteToProfileList[];

    BaseActor* (*mBuildFunc)(const ActorBuildInfo*);
    u32 mID;
    const ActorInfo* mActorInfo;
    u8 mHasResourcesLoaded;
    u32 mFlags;

private:
    static const u32 NUM_PROFILES_ORIGINAL = ProfileID::NumOriginal;
    static const u32 NUM_PROFILES          = ProfileID::Num;
    static const u32 NUM_PROFILES_CUSTOM   = NUM_PROFILES - NUM_PROFILES_ORIGINAL;

    static Profile* profilesOriginal[NUM_PROFILES_ORIGINAL];
    static s16 prioritiesOriginal[NUM_PROFILES_ORIGINAL];
    static u8 hasResourcesOriginal[NUM_PROFILES_ORIGINAL];
    static u8 resourceCountOriginal[NUM_PROFILES_ORIGINAL];
    static const sead::SafeString* resourceListsOriginal[NUM_PROFILES_ORIGINAL];

    static Profile* profilesCustom[NUM_PROFILES_CUSTOM];
    static s16 prioritiesCustom[NUM_PROFILES_CUSTOM];
    static u8 hasResourcesCustom[NUM_PROFILES_CUSTOM];
    static u8 resourceCountCustom[NUM_PROFILES_CUSTOM];
    static const sead::SafeString* resourceListsCustom[NUM_PROFILES_CUSTOM];

    friend struct ProfileResources;
};

struct ProfileResources {
    ProfileResources(u32 id, u32 count, const sead::SafeString resources[]) {
        if (id < Profile::NUM_PROFILES_ORIGINAL) {
            Profile::hasResourcesOriginal[id] = count > 0;
            Profile::resourceCountOriginal[id] = count;
            Profile::resourceListsOriginal[id] = resources;
        }

        else if (id < Profile::NUM_PROFILES) {
            const u32 customID = id - Profile::NUM_PROFILES_ORIGINAL;
            Profile::hasResourcesCustom[customID] = count > 0;
            Profile::resourceCountCustom[customID] = count;
            Profile::resourceListsCustom[customID] = resources;
        }

        else {
            Profile::hasResourcesOriginal[0] = count > 0;
            Profile::resourceCountOriginal[0] = count;
            Profile::resourceListsOriginal[0] = resources;
        }
    }
};

#define PROFILE_RESOURCES_IDENT(ident, id, ...)                                                                                                           \
    static const u32 PP_CONCAT(profileResourceCount, ident) = PP_NARG(__VA_ARGS__);                                                                       \
    static_assert(PP_CONCAT(profileResourceCount, ident) <= 0xFF, "Cannot have more than 255 resources!");                                                \
    static const sead::SafeString PP_CONCAT(profileResourceFiles, ident)[] = { __VA_ARGS__ };                                                             \
    static const ProfileResources PP_CONCAT(profileResources, ident)(id, PP_CONCAT(profileResourceCount, ident), PP_CONCAT(profileResourceFiles, ident))

#define PROFILE_RESOURCES(id, ...)   \
    PROFILE_RESOURCES_IDENT(__LINE__, id, __VA_ARGS__)
