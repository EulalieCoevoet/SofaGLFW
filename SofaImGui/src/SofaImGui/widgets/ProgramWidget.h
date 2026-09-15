#pragma once
#include <imgui.h>
#include <imgui_internal.h>
#include <string>

namespace sofaimgui::widgets
{

/// Draws a colored block with a title area.
void Block(const char* label, const ImRect &bb, const ImVec4 &color, const bool &isSelected);

/// Draws a draggable area within the specified bounding box.
void Drag(const char* label, const ImRect &bb, double *value);

/// Begin drawing a program block
void BeginBlock(const std::string &label, const ImVec2 &size, const ImVec4 &color, const bool & isSelected = false);
void EndBlock(const std::string &label, const ImVec2& size);

void BlockHeader(const char *icon, char* label, bool& hasValuesChanged);

void BeginBlockLine(const char* label);
bool BeginBlockLockLine(const char* label);
void EndBlockLine();

void BlockNewLine();
}
