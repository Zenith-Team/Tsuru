#pragma once

#include "sead/filedevicemgr.h"
#include "agl/texturesampler.h"
#include "agl/texturedatainitializer.h"
#include "sead/color.h"
#include "log.h"

namespace Atlys {

class Map { // Represents a map file with dynamic data, can contain multiple worlds
private:
    class Data { // Static data from the file
    public:
        struct Header {
            char magic[4];                  // ATLS
            u32 version;                    // Map format version
            u32 nodeCount;                  // Number of nodes
            u32 layerCount;                 // Number of layers
            u32 spriteCount;                // Number of sprites
            u32 worldCount;                 // Number of worlds
        };

        struct WorldInfo {
            u32 id;                         // World ID
            char name[32];                  // World name
            sead::Color4f accent;           // Accent color
        };

        struct Node {
            enum Type {
                Type_Normal,                // Player just walks to it
                Type_Level,                 // Level node
                Type_Transition,            // Teleport to a new node with a transition
            };

            struct Connection {
                enum Flags {
                    Flag_AlwaysUnlocked = 1 << 0,
                    Flag_NormalExit     = 1 << 1,
                    Flag_SecretExit     = 1 << 2,
                    Flag_NoReverse      = 1 << 3
                };

                u32 node;                   // Connected node ID
                u32 flags;                  // Flags
                f32 speed;                  // Walking speed
                bool unlocked;              //! This is for dynamic data, but we put it here so it's inside Connection
            };

            u32 id;                         // Node ID
            u32 worldID;                    // Parent world ID
            Connection connections[4];      // Node IDs of the nodes connected to this one
            Vec3f position;                 // Position
            Type type;                      // Node type for union occupancy
            union {
                struct { // Normal
                    bool stop;
                };

                struct { // Level
                    u8 world;
                    u8 level;
                    bool unlocksWorld;
                    u32 unlocksWorldID;
                    bool hasSecretExit;
                };

                struct { // Transition
                    u32 transition;
                    u32 targetNodeID;
                };
            };
        };

        struct Layer {
            char gtxName[16];
        };

        struct Sprite {
            u32 id;
            u32 settings1;
            u32 settings2;
            Vec3f position;
        };

    public:
        Data(const sead::SafeString& path);
        ~Data();

        Header* header;
        WorldInfo* worlds;
        Node* nodes;
        Layer* layers;
        Sprite* sprites;
        bool loaded;
    };

public:
    class Node : public Data::Node {
    public:
        enum ExitFlags {
            Exit_Normal   = 1 << 0,
            Exit_Secret   = 1 << 1,
            Exits_All     = 1 << 2  // Does not have to be *both*, just all that are available on this node
        };

        enum StarCoinFlags {
            StarCoin_1    = 1 << 0,
            StarCoin_2    = 1 << 1,
            StarCoin_3    = 1 << 2,
            StarCoins_All = (StarCoin_1 | StarCoin_2 | StarCoin_3)
        };

    public:
        Node()
            : exits(0)
            , starCoins(0)
            , allCompleted(false)
        { }

        bool anyExitDone() {
            if (this->type == Data::Node::Type_Level) {
                if (this->exits & Exit_Normal)
                    return true;
                if (this->hasSecretExit && (this->exits & Exit_Secret))
                    return true;
            }

            return false;
        }

        bool checkExitCompletion() {
            if (this->type == Data::Node::Type_Level && (this->exits & Exit_Normal)) {
                if (!(this->hasSecretExit && (this->exits & Exit_Secret)))
                    return false;
                
                this->exits |= Exits_All;
            }

            return this->exits & Exits_All;
        };

        bool checkCompletion() {
            this->checkExitCompletion();
        
            if (this->type == Data::Node::Type_Level) {
                if ((this->exits & Exits_All) && (this->starCoins & StarCoins_All))
                    this->allCompleted = true;
                else
                    this->allCompleted = false;
            }

            return this->allCompleted;
        }
        
        // Level node only
        u32 exits;
        u8 starCoins;
        bool allCompleted;
    };

    class WorldInfo : public Data::WorldInfo {
    public:
        WorldInfo()
            : unlocked(false)
            , allLevelsCompleted(false)
            , allExitsCompleted(false)
            , allCompleted(false)
        { }

        void checkLevels(Node* nodes, Data::Header* header) {
            for (u32 i = 0; i < header->nodeCount; i++) {
                if (nodes[i].type == Data::Node::Type_Level && nodes[i].world == this->id) {
                    nodes[i].checkExitCompletion();
                    if (nodes[i].anyExitDone())
                        continue;
                    else {
                        this->allLevelsCompleted = false;
                        return;
                    }
                }
            }

            this->allLevelsCompleted = true;
        }

        void checkExits(Node* nodes, Data::Header* header) {
            for (u32 i = 0; i < header->nodeCount; i++) {
                if (nodes[i].type == Data::Node::Type_Level && nodes[i].world == this->id) {
                    if (nodes[i].checkExitCompletion())
                        continue;
                    else {
                        this->allExitsCompleted = false;
                        return;
                    }
                }
            }

            this->allExitsCompleted = true;
        }

        void checkStarCoins(Node* nodes, Data::Header* header) {
            for (u32 i = 0; i < header->nodeCount; i++) {
                if (nodes[i].type == Data::Node::Type_Level && nodes[i].world == this->id) {
                    if (nodes[i].starCoins & Node::StarCoins_All)
                        continue;
                    else {
                        this->allStarCoinsCompleted = false;
                        return;
                    }
                }
            }

            this->allStarCoinsCompleted = true;
        }

        void checkAll(Node* nodes, Data::Header* header) {
            for (u32 i = 0; i < header->nodeCount; i++) {
                if (nodes[i].type == Data::Node::Type_Level && nodes[i].world == this->id) {
                    if (nodes[i].checkCompletion())
                        continue;
                    else {
                        this->allCompleted = false;
                        return;
                    }
                }
            }

            this->allCompleted = true;
        }

        bool unlocked;

        // So we don't have to check every time
        bool allLevelsCompleted;
        bool allExitsCompleted;
        bool allStarCoinsCompleted;
        bool allCompleted; // All exits and star coins
    };

    class Layer : public Data::Layer {
    public:
        Layer()
            : textureRaw(nullptr)
        { }

        ~Layer() {
            if (this->textureRaw)
                delete[] this->textureRaw;
            
            this->textureRaw = nullptr;
        }

        bool load(const sead::SafeString& path) {
            sead::FileHandle handle;
            if (!sead::FileDeviceMgr::instance()->tryOpen(&handle, path, sead::FileDevice::FileOpenFlag_ReadOnly, 0)) {
                LOG("Layer texture at %s does not exist", path.cstr());
                return false;
            }

            u32 filesize = handle.getFileSize();

            if (filesize == 0) {
                LOG("Layer texture at %s is empty", path.cstr());
                return false;
            }

            this->textureRaw = new(nullptr, 0x2000) u8[filesize];

            u32 bytesRead = handle.read(this->textureRaw, filesize);
            if (bytesRead != filesize) {
                LOG("Failed to read layer texture at %s", path.cstr());
                return false;
            }

            agl::TextureDataInitializerGTX::initialize(&this->texture, this->textureRaw, 0);
            this->texture.invalidateGPUCache();

            this->sampler.applyTextureData(this->texture);

            return true;
        }

    private:
        agl::TextureData texture;
        u8* textureRaw;

    public:
        agl::TextureSampler sampler;
    };

public:
    Map(const sead::SafeString& path);
    ~Map();

    Node* findNodeByID(u32 id);

    Data::Header* info;
    WorldInfo* worlds;
    Node* nodes;
    Layer* layers;
    Data::Sprite* sprites;
};

}
