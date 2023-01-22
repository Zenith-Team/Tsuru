#pragma once

#include "sead/safestring.h"
#include "sead/heap.h"
#include "preprocessor.h"
#include "game/profile/profileid.h"

class Actor;
struct ActorInfo;
struct ActorBuildInfo;

class Profile {
public:
    typedef Actor* (*buildFunction)(const ActorBuildInfo*);

public:
    ENUM_CLASS(Flags,
        DontRenderOffScreen = 1 << 1
    );

    ENUM_CLASS(LoadResourcesAt,
        Boot,
        Course,
        CourseSelect
    );

protected:
    Profile(buildFunction, u32 id, const sead::SafeString& name = "", const ActorInfo* actorInfo = nullptr, u32 flags = 0);

public:
    // Locates and gets a profile based on the ID
    // @param id Target profile ID
    // @return Pointer to retrieved profile
    static Profile* get(u32 id);
    static s16 getPriority(u32 id);
    static LoadResourcesAt::__type__ getResourcesLoadAt(u32 id);
    static u8 getResourceCount(u32 id);
    static const sead::SafeString* getResourceList(u32 id);
    static u32 getNumProfiles();
    static void loadProfileResources(LoadResourcesAt::__type__, sead::Heap* heap);

    static u32 spriteToProfileList[];
    static u32 sprite(u32 spriteID) {
        return spriteToProfileList[spriteID];
    }

    buildFunction buildFunc;    // Pointer to build function of the target actor
    u32 id;                     // Profile ID
    const ActorInfo* actorInfo; // Pointer to actor info to build with
    u8 hasResourcesLoaded;
    u32 flags;

private:
    static const u32 NUM_PROFILES_ORIGINAL = ProfileID::NumOriginal;
    static const u32 NUM_PROFILES          = ProfileID::Num;
    static const u32 NUM_PROFILES_CUSTOM   = NUM_PROFILES - NUM_PROFILES_ORIGINAL;

    static Profile* profilesOriginal[NUM_PROFILES_ORIGINAL];
    static s16 prioritiesOriginal[NUM_PROFILES_ORIGINAL];
    static u8 resourcesLoadAtOriginal[NUM_PROFILES_ORIGINAL];
    static u8 resourceCountOriginal[NUM_PROFILES_ORIGINAL];
    static const sead::SafeString* resourceListsOriginal[NUM_PROFILES_ORIGINAL];

    static Profile* profilesCustom[NUM_PROFILES_CUSTOM];
    static s16 prioritiesCustom[NUM_PROFILES_CUSTOM];
    static u8 resourcesLoadAtCustom[NUM_PROFILES_CUSTOM];
    static u8 resourceCountCustom[NUM_PROFILES_CUSTOM];
    static const sead::SafeString* resourceListsCustom[NUM_PROFILES_CUSTOM];

    friend struct ProfileResources;
};

template <typename T>
class RegisterProfile : Profile {
private:
    static Actor* build(const ActorBuildInfo* buildInfo) {
        return new T(buildInfo);
    }

public:
    RegisterProfile(u32 id, const sead::SafeString& name = "", const ActorInfo* actorInfo = nullptr, u32 flags = 0)
        : Profile(&RegisterProfile::build, id, name, actorInfo, flags)
    { }
};

struct ProfileResources {
    ProfileResources(u32 id, Profile::LoadResourcesAt::__type__ loadAt, u32 count, const sead::SafeString resources[]) {
        if (id < Profile::NUM_PROFILES_ORIGINAL) {
            Profile::resourcesLoadAtOriginal[id] = loadAt;
            Profile::resourceCountOriginal[id] = count;
            Profile::resourceListsOriginal[id] = resources;
        }

        else if (id < Profile::NUM_PROFILES) {
            const u32 customID = id - Profile::NUM_PROFILES_ORIGINAL;
            Profile::resourcesLoadAtCustom[customID] = loadAt;
            Profile::resourceCountCustom[customID] = count;
            Profile::resourceListsCustom[customID] = resources;
        }

        else {
            Profile::resourcesLoadAtOriginal[0] = loadAt;
            Profile::resourceCountOriginal[0] = count;
            Profile::resourceListsOriginal[0] = resources;
        }
    }
};

#define REGISTER_PROFILE(type, ...) \
    static const RegisterProfile<type> __profile_##type(__VA_ARGS__)

#define PROFILE_RESOURCES_IDENT(ident, id, loadat, ...)                                                    \
    static const u32 PP_CONCAT(profileResourceCount, ident) = PP_ARG_N(0, ## __VA_ARGS__, 64, 63, 62, 61, 60, 59, 58, 57, 56, 55, 54, 53, 52, 51, 50, 49, 48, 47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0); \
    static_assert(PP_CONCAT(profileResourceCount, ident) <= 0xFF, "Cannot have more than 255 resources!"); \
    static const sead::SafeString PP_CONCAT(profileResourceFiles, ident)[] = { __VA_ARGS__ };              \
    static const ProfileResources PP_CONCAT(profileResources, ident)(id, loadat, PP_CONCAT(profileResourceCount, ident), PP_CONCAT(profileResourceFiles, ident))

#define PROFILE_RESOURCES(id, loadat, ...) PROFILE_RESOURCES_IDENT(__LINE__, id, loadat, __VA_ARGS__)
