#pragma once

#include "sead/filedevicemgr.h"
#include "dynlibs/gx2/types.h"
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
                Type_Transition,            // Mode to a new node with a transition
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
            Exits_All     = 1 << 2  // Does not have to be *both*, just all that are available on this node
        };

        enum StarCoinFlags {
            StarCoin_1    = 1 << 0,
            StarCoin_2    = 1 << 1,
            StarCoin_3    = 1 << 2,
            StarCoins_All = (StarCoin_1 | StarCoin_2 | StarCoin_3)
        };

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
                    return;
                
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

    struct WorldInfo : Data::WorldInfo {
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

    struct Layer : Data::Layer {
        Layer()
            : gtx(nullptr)
        { }

        GX2Texture* gtx;
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
