#pragma once

#include "types.h"
#include "sead/filedevice.h"
#include "sead/filedevicemgr.h"
#include "dynlibs/gx2/types.h"
#include "sead/heapmgr.h"
#include "log.h"
#include "sead/color.h"

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
                Type_Normal,                     // Player just walks to it
                Type_Level,                      // Level node
                Type_Transition,                 // Mode to a new node with a transition
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
            };

            u32 id;                         // Node ID
            u32 worldID;                    // Parent world ID
            Connection connections[4];      // Node IDs of the nodes connected to this one
            Vec3f position;                 // Position
            f32 speed;                      // Speed when walking to this node
            Type type;                      // Node type for union occupancy
            union {
                struct { // Normal
                    bool stop;
                };

                struct { // Level
                    u8 world;
                    u8 level;
                    bool unlocksWorld;
                    u8 unlocksWorldID;
                    bool hasSecretExit;
                };

                struct { // Transition
                    u32 transition;
                    u8 targetNode;
                };
            };
        };

        struct Layer {
            s32 index;
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
    struct Node : Data::Node {
        enum ExitFlags {
            Exit_Normal   = 1 << 0,
            Exit_Secret   = 1 << 1,
            Exits_All     = 1 << 2
        };

        enum StarCoinFlags {
            StarCoin_1    = 1 << 0,
            StarCoin_2    = 1 << 1,
            StarCoin_3    = 1 << 2,
            StarCoins_All = 1 << 3
        };

        Node()
            : exits(0)
            , starCoins(0)
            , allCompleted(false)
            , valid(true)
        { }

        void fillData(const Data::Node& data) {
            this->id = data.id;
            this->worldID = data.worldID;
            this->position = data.position;
            this->speed = data.speed;
            this->type = data.type;

            // Copy connections
            for (u32 i = 0; i < 4; i++)
                this->connections[i] = data.connections[i];

            // Copy union data

            if (data.type == Type_Normal && this->type == Type_Normal) {
                this->stop = data.stop;
            }
            
            else if (data.type == Type_Level && this->type == Type_Level) {
                this->world          = data.world;
                this->level          = data.level;
                this->unlocksWorld   = data.unlocksWorld;
                this->unlocksWorldID = data.unlocksWorldID;
                this->hasSecretExit  = data.hasSecretExit;
            }
            
            else if (data.type == Type_Transition && this->type == Type_Transition) {
                this->transition = data.transition;
                this->targetNode = data.targetNode;
            }
            
            else // If we reach this point the the nodes are of different types
                this->valid = false;
        }

        bool anyExitDone() {
            if (this->type == Data::Node::Type_Level) {
                if (this->exits & Exit_Normal)
                    return true;
                if (this->exits & Exit_Secret)
                    return true;
            }

            return false;
        }

        void checkExitCompletion() {
            if (this->type == Data::Node::Type_Level && this->exits & Exit_Normal) {
                if (!(this->hasSecretExit && (this->exits & Exit_Secret)))
                    return;
                
                this->exits |= Exits_All;
            }
        };

        void checkStarCoinCompletion() {
            if (this->type == Data::Node::Type_Level && (this->starCoins & StarCoin_1) && (this->starCoins & StarCoin_2) && (this->starCoins & StarCoin_3)) {
                this->starCoins |= StarCoins_All;
            }
        }

        void checkCompletion() {
            this->checkExitCompletion();
            this->checkStarCoinCompletion();
        
            if (this->type == Data::Node::Type_Level) {
                if ((this->exits & Exits_All) && (this->starCoins & StarCoins_All))
                    this->allCompleted = true;
                else
                    this->allCompleted = false;
            }
        }
        
        u32 exits;
        u8 starCoins;
        bool allCompleted;
        bool valid;
    };

    struct WorldInfo : Data::WorldInfo {
        WorldInfo()
            : unlocked(false)
            , allLevelsCompleted(false)
            , allExitsCompleted(false)
            , allCompleted(false)
        { }

        void fillData(const Data::WorldInfo& data) {
            this->id = data.id;
            for (u32 i = 0; i < 32; i++)
                this->name[i] = data.name[i];
            this->accent = data.accent;
        }

        void checkLevels(Node* nodes, Data::Header* header) {
            for (u32 i = 0; i < header->nodeCount; i++) {
                if (nodes[i].type == Data::Node::Type_Level && nodes[i].world == this->id) {
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
                    if (nodes[i].exits & Node::Exits_All)
                        continue;
                    else {
                        this->allExitsCompleted = false;
                        return;
                    }
                }
            }

            this->allExitsCompleted = true;
        }

        void checkAll(Node* nodes, Data::Header* header) {
            for (u32 i = 0; i < header->nodeCount; i++) {
                if (nodes[i].type == Data::Node::Type_Level && nodes[i].world == this->id) {
                    if (nodes[i].allCompleted)
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
        bool allCompleted; // All exits and star coins
    };

    struct Layer : Data::Layer {
        Layer()
            : gtx(nullptr)
        { }

        void fillData(const Data::Layer& data) {
            this->index = data.index;
            for (u32 i = 0; i < 16; i++)
                this->gtxName[i] = data.gtxName[i];
        }

        GX2Texture* gtx;
    };

public:
    Map(const sead::SafeString& path);
    ~Map();

    Data::Header* info;
    WorldInfo* worlds;
    Node* nodes;
    Layer* layers;
    Data::Sprite* sprites;
};

}
