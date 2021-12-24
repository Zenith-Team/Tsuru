#include "tsuru/atlys/actor.h"

namespace Atlys {

class Node : public Actor {
    SEAD_RTTI_OVERRIDE_IMPL(Node, Actor)

public:
    enum NodeColor {
        NodeColor_Red,
        NodeColor_Blue
    };

public:
    Node(const ActorBuildInfo* buildInfo);
    virtual ~Node() { }

    static ::Actor* build(const ActorBuildInfo* buildInfo);

    u32 onCreate() override;
    u32 onDraw() override;

    NodeColor color; // Alignment would make it u32 anyways
};

}
