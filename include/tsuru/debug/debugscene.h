#pragma once

#include "sead/task.h"
#include "agl/lyr/renderinfo.h"
#include "agl/lyr/drawmethod.h"
#include "tsuru/gtx.h"
#include "tsuru/font.h"
#include "game/states.h"
#include "tsuru/inputcontrollers.h"

class DebugScene : public sead::CalculateTask {
    SEAD_RTTI_OVERRIDE_IMPL(DebugScene, sead::CalculateTask);
    SEAD_SINGLETON_TASK(DebugScene);

public:
    DebugScene(const sead::TaskConstructArg& arg);
    virtual ~DebugScene();

    static sead::TaskBase* construct(const sead::TaskConstructArg& arg);

    void prepare() override;
    void enter() override;
    void calc() override;

    void draw(const agl::lyr::RenderInfo& renderInfo);

    BitmapFont font;
    struct TextBuffer {
        struct Entry {
            Entry() : text(nullptr), position(0, 0) { }
            Entry(char* text, const Vec2f& position) : text(text), position(position) { }

            char* text;
            Vec2f position;
        }* entries;

        void append(const Entry& entry)  {
            for (u32 i = 0; i < 0x100; i++) {
                if (this->entries[i].text == nullptr) {
                    this->entries[i] = entry;
                    break;
                }
            }
        }

        void clear() {
            for (u32 i = 0; i < 0x100; i++) {
                this->entries[i].text = nullptr;
                this->entries[i].position = Vec2f(0, 0);
            }
        }
    } buffer;
    InputControllers controllers;
    MultiStateWrapper<DebugScene> states;
    u32 cursor;
    u8 world, level;
    bool pressed;

    DECLARE_STATE(DebugScene, MainMenu);
    DECLARE_STATE(DebugScene, LevelSelect);
    DECLARE_STATE(DebugScene, Settings);
};
