#pragma once

#include "tsuru/gtx.h"
#include "game/graphics/drawmgr.h"
#include "sead/color.h"
#include "log.h"
#include "math/easing.h"

#define ATLYS_NODE_INVALID 0xFFFFFFFF

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
            u32 animTexCount;               // Number of animated textures
        };

        struct WorldInfo {
            u32 id;                         // World ID
            char name[32];                  // World name
            sead::Color4f accent;           // Accent color
        };

        struct Node {
            enum Type {
                Type_Normal,                // Player just walks to it
                Type_Passthrough,           // Player walks through it
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
            };

            u32 id;                         // Node ID
            u32 worldID;                    // Parent world ID
            Vec2f position;                 // Position
            Type type;                      // Node type for union occupancy
            union {
                struct { // Normal
                    Connection Normal_connections[4];
                };

                struct { // Passthrough
                    Connection Passthrough_connections[2];
                };

                struct { // Level
                    Connection Level_connections[4];
                    u8 world;
                    u8 level;
                    bool unlocksWorld;
                    bool hasSecretExit;
                    u32 unlocksWorldID;
                };

                struct { // Transition
                    u32 transition;
                    u32 targetNodeID;
                };
            };
        };

        struct Layer {
            char gtxName[32];
            u32 scaleFilter;
            Vec2f position;
            f32 size;
        };

        struct Sprite {
            u32 id;
            u32 settings1;
            u32 settings2;
            Vec2f position;
        };

        struct AnimTex {
            enum AnimFlags {
                ScaleAnimation_X    = 1 << 0,
                ScaleAnimation_Y    = 1 << 1,

                PositionAnimation_X = 1 << 2,
                PositionAnimation_Y = 1 << 3,

                RotationAnimation_X = 1 << 4
            };

            char gtxName[32];
            
            bool reverseLoop; // Should we reverse the animation when it reaches the end

            AnimFlags animFlags;

            Vec2f scaleStart;
            Vec2f scaleEnd;
            Easing::EaseType scaleXEase;
            Easing::EaseType scaleYEase;
            f32 scaleSpeed;

            Vec2f positionStart;
            Vec2f positionEnd;
            Easing::EaseType positionXEase;
            Easing::EaseType positionYEase;
            f32 positionSpeed;

            f32 rotationStart;
            f32 rotationEnd;
            Easing::EaseType rotationEase;
            f32 rotationSpeed;
        };

    public:
        Data(const sead::SafeString& path);
        ~Data();

        Header* header;
        WorldInfo* worlds;
        Node* nodes;
        Layer* layers;
        Sprite* sprites;
        AnimTex* animTexs;
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

        void loadModel() {
            if (this->id == 0) {
                this->model = ModelWrapper::create("kuribo", "kuribo");
            } else if (this->type == Data::Node::Type_Level) {
                this->model = ModelWrapper::create("kuribo", "kuribo");
            }
        }

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

        void draw() {
            if (this->type != Data::Node::Type_Level)
                return;
            
            Mtx34 mtx;
            mtx.makeIdentity();
            mtx.rotateAndTranslate(Vec3u(0), Vec3f(this->position.x, 0.0f, this->position.y));
            this->model->setMtx(mtx);
            this->model->setScale(Vec3f(1.0f));
            this->model->updateModel();

            DrawMgr::instance()->drawModel(this->model);
        }

        bool unlocked;

        // Level node only
        u32 exits;
        u8 starCoins;
        bool allCompleted;
        ModelWrapper* model; // ModelWrapper*
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
            : gtx()
        { }

        ~Layer() { }

        GTX gtx;
    };

    class AnimTex : public Data::AnimTex {
    private:
        Easing::EasingFunction scaleXEaseFunc;
        Easing::EasingFunction scaleYEaseFunc;
        Easing::EasingFunction positionXEaseFunc;
        Easing::EasingFunction positionYEaseFunc;
        Easing::EasingFunction rotationEaseFunc;

        Easing scaleXEaser;
        Easing scaleYEaser;
        Easing positionXEaser;
        Easing positionYEaser;
        Easing rotationEaser;

    public:
        AnimTex()
            : scaleXEaseFunc(nullptr)
            , scaleYEaseFunc(nullptr)
            , positionXEaseFunc(nullptr)
            , positionYEaseFunc(nullptr)
            , rotationEaseFunc(nullptr)
            , scaleXEaser()
            , scaleYEaser()
            , positionXEaser()
            , positionYEaser()
            , rotationEaser()
            , gtx()
            , rewinding(false)
        { }

    private:
        void setTargetToEnd() {
            this->scaleXEaser.set(this->scaleXEaseFunc, this->scaleStart.x, this->scaleEnd.x, this->scaleSpeed);
            this->scaleYEaser.set(this->scaleYEaseFunc, this->scaleStart.y, this->scaleEnd.y, this->scaleSpeed);

            this->positionXEaser.set(this->positionXEaseFunc, this->positionStart.x, this->positionEnd.x, this->positionSpeed);
            this->positionYEaser.set(this->positionYEaseFunc, this->positionStart.y, this->positionEnd.y, this->positionSpeed);

            this->rotationEaser.set(this->rotationEaseFunc, this->rotationStart, this->rotationEnd, this->rotationSpeed);
        }

        void setTargetToStart() {
            this->scaleXEaser.set(this->scaleXEaseFunc, this->scaleEnd.x, this->scaleStart.x, this->scaleSpeed);
            this->scaleYEaser.set(this->scaleYEaseFunc, this->scaleEnd.y, this->scaleStart.y, this->scaleSpeed);

            this->positionXEaser.set(this->positionXEaseFunc, this->positionEnd.x, this->positionStart.x, this->positionSpeed);
            this->positionYEaser.set(this->positionYEaseFunc, this->positionEnd.y, this->positionStart.y, this->positionSpeed);

            this->rotationEaser.set(this->rotationEaseFunc, this->rotationEnd, this->rotationStart, this->rotationSpeed);
        }

    public:
        void init(const sead::SafeString& tex) {
            this->gtx.load(tex);
            

            this->scaleXEaseFunc = Easing::EaseTypeToEaseFunc(this->scaleXEase);
            this->scaleYEaseFunc = Easing::EaseTypeToEaseFunc(this->scaleYEase);

            this->positionXEaseFunc = Easing::EaseTypeToEaseFunc(this->positionXEase);
            this->positionYEaseFunc = Easing::EaseTypeToEaseFunc(this->positionYEase);

            this->rotationEaseFunc = Easing::EaseTypeToEaseFunc(this->rotationEase);

            this->setTargetToEnd();
        }

        void animate() {
            bool finishedScaleX = this->scaleXEaser.ease(this->scale.x);
            bool finishedScaleY = this->scaleYEaser.ease(this->scale.y);

            bool finishedPositionX = this->positionXEaser.ease(this->position.x);
            bool finishedPositionY = this->positionYEaser.ease(this->position.y);

            bool finishedRotation = this->rotationEaser.ease(this->rotation);

            if (finishedScaleX && finishedScaleY && finishedPositionX && finishedPositionY && finishedRotation) {
                if (this->reverseLoop) {
                    if (this->rewinding) {
                        this->rewinding = false;
                        this->setTargetToEnd();
                    } else {
                        this->rewinding = true;
                        this->setTargetToStart();
                    }
                } else {
                    this->setTargetToEnd();
                }
            }
        }

        GTX gtx;
        Vec2f scale;
        Vec2f position;
        f32 rotation;
        bool rewinding;
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
    AnimTex* animTexs;
};

}
