#pragma once

#include "game/actor/stage/blockbase.h"

class BlockWrapper : public BlockBase {
    SEAD_RTTI_OVERRIDE(BlockWrapper, BlockBase);

private:
    BlockBase::init;

public:
    BlockWrapper(const ActorBuildInfo* buildInfo)
        : BlockBase(buildInfo)
    { }

    bool init() {
        this->_1CB4 = 0.0f;
        this->_1CB8 = 0.0f;
        this->_1AB4 = 0;
        this->_1AEC = 0;
        this->_1CC0 = 0;
        this->collisionMask = 1;

        this->stateType = StateType::QuestionBlock;
        this->rectCollider.setType(ColliderBase::Type::QuestionBlock);

        if (!BlockBase::init(true, true)) {
            return false;
        }

        this->_1CAC = 0.0f;
        this->content = Content::Nothing;
        this->visibleAreaSize.set(2048.0f, 1024.0f);

        this->registerColliderActiveInfo();

        this->doStateChange(&StateID_Active);

        return true;
    }
};
