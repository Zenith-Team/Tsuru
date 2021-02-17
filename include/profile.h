#pragma once

#include "sead.h"
#include "preprocessor.h"
#include "profileid.h"

class Base;
struct ActorInfo;
struct ActorBuildInfo;

class Profile
{
public:
    Profile(Base* (*buildFunc)(const ActorBuildInfo*), u32 id, const sead::SafeString& name, const ActorInfo* actorInfo, u32 flags);

    static Profile* get(u32 id);

    Base* (*buildFunc)(const ActorBuildInfo*);  // 0
    u32 id;                                     // 4
    const ActorInfo* actorInfo;                 // 8
    u8 hasResourcesLoaded;                      // C
    u32 flags;                                  // 10

    static u32 spriteToProfileList[];

    static const u32 NUM_PROFILES_ORIGINAL = 913;

    static u8 hasResourcesOriginal[NUM_PROFILES_ORIGINAL];
    static u8 resourceCountOriginal[NUM_PROFILES_ORIGINAL];
    static const sead::SafeString* resourceListsOriginal[NUM_PROFILES_ORIGINAL];
};


struct ProfileResources
{
    ProfileResources(s32 id, u32 count, const sead::SafeString resources[])
    {
        if (id >= Profile::NUM_PROFILES_ORIGINAL)
            id = 0;

        else if (id < 0)
            return;

        Profile::hasResourcesOriginal[id] = count > 0;
        Profile::resourceCountOriginal[id] = count;
        Profile::resourceListsOriginal[id] = resources;
    }
};

#define PROFILE_RESOURCES_IDENT(ident, id, ...)                                                                                 \
    const sead::SafeString PP_CONCAT(profileResourceFiles, ident)[] = { __VA_ARGS__ };                                          \
    const ProfileResources PP_CONCAT(profileResources, ident)(id, PP_NARG(__VA_ARGS__), PP_CONCAT(profileResourceFiles, ident))

#define PROFILE_RESOURCES(id, ...)   \
    PROFILE_RESOURCES_IDENT(__LINE__, id, __VA_ARGS__)
