// dear imgui: Platform Backend for the Wii U
#pragma once
#include "imgui/imgui.h"      // IMGUI_IMPL_API

#include "types.h"

// GamePad Input
#include "sdk/vpad/functions.h"
// Controller Input
#include "sdk/padscore/functions.h"

struct ImGui_ImplWiiU_ControllerInput
{
   ImGui_ImplWiiU_ControllerInput()
      : vpad(nullptr)
   {
      kpad[0] = nullptr;
      kpad[1] = nullptr;
      kpad[2] = nullptr;
      kpad[3] = nullptr;
   }

   VPADStatus* vpad;
   KPADStatus* kpad[4];
};

enum ImGui_ImplWiiU_KeyboardOverlayType
{
   //! Draw for the DRC
   ImGui_KeyboardOverlay_DRC,
   //! Draw for the TV
   ImGui_KeyboardOverlay_TV,
   //! Draw for the controller which requested the keyboard
   ImGui_KeyboardOverlay_Auto
};

IMGUI_IMPL_API bool     ImGui_ImplWiiU_Init();
IMGUI_IMPL_API void     ImGui_ImplWiiU_Shutdown();
IMGUI_IMPL_API bool     ImGui_ImplWiiU_ProcessInput(ImGui_ImplWiiU_ControllerInput* input);
IMGUI_IMPL_API void     ImGui_ImplWiiU_DrawKeyboardOverlay(ImGui_ImplWiiU_KeyboardOverlayType type = ImGui_KeyboardOverlay_Auto);
