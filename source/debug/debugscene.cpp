#include "tsuru/debug/debugscene.h"
#include "agl/lyr/renderer.h"
#include "agl/utl/devtools.h"
#include "sead/graphicscontext.h"
#include "tsuru/fonts.h"
#include "game/task/taskmgr.h"
#include "tsuru/save/managers/tsurusavemgr.h"

SEAD_SINGLETON_TASK_IMPL(DebugScene);

CREATE_STATE(DebugScene, MainMenu);
CREATE_STATE(DebugScene, LevelSelect);
CREATE_STATE(DebugScene, Settings);

#define PrintText(text, x, y) this->buffer.append(DebugScene::TextBuffer::Entry(text, Vec2f(x, y)))

static const f32 xleft = -560;
static const f32 xtop = 200;

static bool die = false;

DebugScene::DebugScene(const sead::TaskConstructArg& arg)
    : sead::CalculateTask(arg, "DebugScene")
    , states(this)
{
    DebugScene::setInstance(this);
}

DebugScene::~DebugScene() {
    delete[] this->buffer.entries;
}

sead::TaskBase* DebugScene::construct(const sead::TaskConstructArg& arg) {
    return new(arg.heapArray->heaps[arg.heapArray->primaryIndex], 4) DebugScene(arg);
}

void DebugScene::prepare() {
    this->font.load("tsuru/font.gtx", 10, 24, 40, Fonts::TestFont);
    this->buffer.entries = new(this->heapArray.heaps[this->heapArray.primaryIndex], 4) TextBuffer::Entry[0x100];
    this->buffer.clear();
    this->adjustHeapAll();
}

void DebugScene::enter() {
    die = false;

    static agl::lyr::DrawMethod drawMethod;
    void (DebugScene::*drawFunc)(const agl::lyr::RenderInfo&) = &DebugScene::draw;
    BIND_DRAW_METHOD(drawMethod, "DebugMain", *((agl::lyr::DrawMethod::PTMF*)&drawFunc), 0xE, this);

    this->controllers.init();

    this->states.changeState(&DebugScene::StateID_MainMenu);
}

void DebugScene::calc() {
    this->states.execute();
}

void DebugScene::draw(const agl::lyr::RenderInfo& renderInfo) {
    if (die) {
        return;
    }

    renderInfo.frameBuffer->clear(1, sead::Color4f(0x000000FF), 1, 0);

    Mtx44 vp;
    sead::Matrix44CalcCommon<f32>::multiply(vp, renderInfo.projection->getDeviceProjectionMatrix(), renderInfo.camera->matrix);

    for (u32 i = 0; i < 0x100; i++) {
        if (this->buffer.entries[i].text != nullptr) {
            this->font.renderText(vp, this->buffer.entries[i].text, this->buffer.entries[i].position);
        }
    }

    this->buffer.clear();
}

/** STATE: MainMenu */

void DebugScene::beginState_MainMenu() {
    this->cursor = 0;
}

void DebugScene::executeState_MainMenu() {
    PrintText("Debug Menu - Main", -(((f32)font.charW() * 17.0f) / 2.0f), 310);

    PrintText("Level Select", xleft, xtop);
    PrintText("Settings", xleft, xtop - 50);
    PrintText(">", xleft - 50, xtop - (50 * this->cursor));

    if (!this->controllers.buttonUp(InputControllers::ControllerID::Gamepad) && !this->controllers.buttonDown(InputControllers::ControllerID::Gamepad)) {
        this->pressed = false;
    } else if (!this->pressed) {
        if (this->controllers.buttonUp(InputControllers::ControllerID::Gamepad) && this->cursor > 0) {
            this->cursor--;
            this->pressed = true;
        }
        if (this->controllers.buttonDown(InputControllers::ControllerID::Gamepad) && this->cursor < 1) {
            this->cursor++;
            this->pressed = true;
        }
    }

    if (this->controllers.buttonA(InputControllers::ControllerID::Gamepad)) {
        switch (this->cursor) {
            case 0:
                this->states.changeState(&DebugScene::StateID_LevelSelect);
                break;
            case 1:
                this->states.changeState(&DebugScene::StateID_Settings);
                break;
        }
    }
}

void DebugScene::endState_MainMenu() { }

/** STATE: LevelSelect */

void DebugScene::beginState_LevelSelect() {
    this->cursor = 0;
    this->world = 1;
    this->level = 1;
}

void DebugScene::executeState_LevelSelect() {
    PrintText("Debug Menu - Level Select", -(((f32)font.charW() * 25.0f) / 2.0f), 310);

    PrintText("World:", xleft, xtop);
    PrintText("Level:", xleft, xtop - 50);

    PrintText(">", xleft - 50, xtop - (50 * this->cursor));

    static char worldText[3] = { '0', '0', '\0' };
    static char levelText[3] = { '0', '0', '\0' };

    worldText[0] = this->world / 10 == 0 ? ' ' : '0' + this->world / 10;
    worldText[1] = '0' + (this->world % 10);

    levelText[0] = this->level / 10 == 0 ? ' ' : '0' + this->level / 10;
    levelText[1] = '0' + (this->level % 10);

    PrintText(worldText, xleft + 164, xtop);
    PrintText(levelText, xleft + 164, xtop - 50);

    if (
        !this->controllers.buttonUp(InputControllers::ControllerID::Gamepad) &&
        !this->controllers.buttonDown(InputControllers::ControllerID::Gamepad) &&
        !this->controllers.buttonLeft(InputControllers::ControllerID::Gamepad) &&
        !this->controllers.buttonRight(InputControllers::ControllerID::Gamepad)
    ) {
        this->pressed = false;
    } else if (!this->pressed) {
        if (this->controllers.buttonUp(InputControllers::ControllerID::Gamepad) && this->cursor > 0) {
            this->cursor--;
            this->pressed = true;
        }
        if (this->controllers.buttonDown(InputControllers::ControllerID::Gamepad) && this->cursor < 1) {
            this->cursor++;
            this->pressed = true;
        }

        if (this->cursor == 0) {
            if (this->controllers.buttonLeft(InputControllers::ControllerID::Gamepad) && this->world > 1) {
                this->world--;
                this->pressed = true;
            }
            if (this->controllers.buttonRight(InputControllers::ControllerID::Gamepad)) {
                this->world++;
                this->pressed = true;
            }
        } else if (this->cursor == 1) {
            if (this->controllers.buttonLeft(InputControllers::ControllerID::Gamepad) && this->level > 1) {
                this->level--;
                this->pressed = true;
            }
            if (this->controllers.buttonRight(InputControllers::ControllerID::Gamepad)) {
                this->level++;
                this->pressed = true;
            }
        }

        if (this->controllers.buttonB(InputControllers::ControllerID::Gamepad)) {
            this->states.changeState(&DebugScene::StateID_MainMenu);
        }
    }

    if (this->controllers.buttonB(InputControllers::ControllerID::Gamepad)) {
        this->states.changeState(&DebugScene::StateID_MainMenu);
    }

    if (this->controllers.buttonPlus(InputControllers::ControllerID::Gamepad)) {
        die = true;
        TaskMgr::instance()->startLevel(this, this->world - 1, this->level - 1);
    }
}

void DebugScene::endState_LevelSelect() { }

/** STATE: Settings */

void DebugScene::beginState_Settings() {
    this->cursor = 0;
}

void DebugScene::executeState_Settings() {
    PrintText("Debug Menu - Settings", -(((f32)font.charW() * 21.0f) / 2.0f), 310);

    PrintText("Collision Viewer: ", xleft, xtop);
    PrintText("Invincibility: ", xleft, xtop - 50);
    PrintText("NoClip: ", xleft, xtop - 100);

    PrintText(">", xleft - 50, xtop - (50 * this->cursor));

    static char trues[] = "true";
    static char falses[] = "false";

    PrintText(TsuruSaveMgr::sSaveData.collisionViewerEnabled ? trues : falses, xleft + 464, xtop);
    PrintText(TsuruSaveMgr::sSaveData.invincibilityEnabled ? trues : falses, xleft + 464, xtop - 50);
    PrintText(TsuruSaveMgr::sSaveData.noClipEnabled ? trues : falses, xleft + 464, xtop - 100);

    if (this->controllers.buttonB(InputControllers::ControllerID::Gamepad)) {
        this->states.changeState(&DebugScene::StateID_MainMenu);
    }

    if (
        !this->controllers.buttonUp(InputControllers::ControllerID::Gamepad) &&
        !this->controllers.buttonDown(InputControllers::ControllerID::Gamepad) &&
        !this->controllers.buttonLeft(InputControllers::ControllerID::Gamepad) &&
        !this->controllers.buttonRight(InputControllers::ControllerID::Gamepad)
    ) {
        this->pressed = false;
    } else if (!this->pressed) {
        if (this->controllers.buttonUp(InputControllers::ControllerID::Gamepad) && this->cursor > 0) {
            this->cursor--;
            this->pressed = true;
        }
        if (this->controllers.buttonDown(InputControllers::ControllerID::Gamepad) && this->cursor < 2) {
            this->cursor++;
            this->pressed = true;
        }

        if (this->cursor == 0) {
            if (this->controllers.buttonLeft(InputControllers::ControllerID::Gamepad)) {
                TsuruSaveMgr::sSaveData.collisionViewerEnabled = false;
                this->pressed = true;
            }
            if (this->controllers.buttonRight(InputControllers::ControllerID::Gamepad)) {
                TsuruSaveMgr::sSaveData.collisionViewerEnabled = true;
                this->pressed = true;
            }
        } else if (this->cursor == 1) {
            if (this->controllers.buttonLeft(InputControllers::ControllerID::Gamepad)) {
                TsuruSaveMgr::sSaveData.invincibilityEnabled = false;
                this->pressed = true;
            }
            if (this->controllers.buttonRight(InputControllers::ControllerID::Gamepad)) {
                TsuruSaveMgr::sSaveData.invincibilityEnabled = true;
                this->pressed = true;
            }
        } else if (this->cursor == 2) {
            if (this->controllers.buttonLeft(InputControllers::ControllerID::Gamepad)) {
                TsuruSaveMgr::sSaveData.noClipEnabled = false;
                this->pressed = true;
            }
            if (this->controllers.buttonRight(InputControllers::ControllerID::Gamepad)) {
                TsuruSaveMgr::sSaveData.noClipEnabled = true;
                this->pressed = true;
            }
        }
    }
}

void DebugScene::endState_Settings() { }
