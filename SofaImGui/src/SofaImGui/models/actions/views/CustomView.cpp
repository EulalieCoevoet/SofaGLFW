/******************************************************************************
 *                 SOFA, Simulation Open-Framework Architecture                *
 *                    (c) 2006 INRIA, USTL, UJF, CNRS, MGH                     *
 *                                                                             *
 * This program is free software; you can redistribute it and/or modify it     *
 * under the terms of the GNU General Public License as published by the Free  *
 * Software Foundation; either version 2 of the License, or (at your option)   *
 * any later version.                                                          *
 *                                                                             *
 * This program is distributed in the hope that it will be useful, but WITHOUT *
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or       *
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for    *
 * more details.                                                               *
 *                                                                             *
 * You should have received a copy of the GNU General Public License along     *
 * with this program. If not, see <http://www.gnu.org/licenses/>.              *
 *******************************************************************************
 * Authors: The SOFA Team and external contributors (see Authors.txt)          *
 *                                                                             *
 * Contact information: contact@sofa-framework.org                             *
 ******************************************************************************/

#include "GUIColors.h"
#include "IconsFontAwesome6.h"
#include <SofaImGui/models/actions/Custom.h>
#include <imgui.h>
#include <imgui_internal.h>
#include <misc/cpp/imgui_stdlib.h>
#include <ProgramStyle.h>
#include <SofaImGui/widgets/Widgets.h>


namespace sofaimgui::models::actions {

bool Custom::CustomView::showBlock(const std::string &label, const ImVec2 &size)
{
    bool hasValuesChanged = false;
    ImGuiWindow* window = ImGui::GetCurrentWindow();
    ImDrawList* drawList = ImGui::GetWindowDrawList();

    float x = window->DC.CursorPos.x ;
    float y = window->DC.CursorPos.y ;

    ImVec2 padding(ImGui::GetStyle().FramePadding);
    ImVec2 spacing(ImGui::GetStyle().ItemSpacing);
    ImRect bb(ImVec2(x, y), ImVec2(x + size.x, y + size.y));
    ImVec2 topRight = ImVec2(x + size.x, y);

    ImGui::ActionBlock(label.c_str(), bb, ProgramColors().CustomBlockBg);

    auto rectMin = ImGui::GetItemRectMin();
    auto rectMax = ImGui::GetItemRectMax();
    rectMax.x -= padding.x;
    ImGui::PushClipRect(rectMin, rectMax, true);

    ImGui::PushStyleColor(ImGuiCol_Text, ProgramColors().Text);
    { // Custom
        x += padding.y;
        y += padding.y;

        window->DC.CursorPos.x = x;
        window->DC.CursorPos.y = y;

        auto rectMin = ImGui::GetItemRectMin();
        auto rectMax = ImGui::GetItemRectMax();
        rectMax.x -= padding.x * 2 + ImGui::GetFrameHeight(); // leave space for option button
        ImGui::PushClipRect(rectMin, rectMax, true);

        std::string id = "##comment" + std::to_string(window->DC.CursorPos.x);
        ImGui::PushStyleColor(ImGuiCol_FrameBg, COLOR_TRANSPARENT);

        ImGui::Text("  " ICON_FA_SLIDERS);
        ImGui::SameLine();
        ImGui::AlignTextToFramePadding();
        window->DC.CursorPos.y = y;

        if(ImGui::InputText(id.c_str(), custom.getComment(), models::actions::Action::COMMENTSIZE))
        {
            hasValuesChanged = true;
        }
        ImGui::PopStyleColor();

        ImGui::PopClipRect();
    }
    ImGui::PopStyleColor();

    std::string text = "duration";
    ImVec2 textSize = ImGui::CalcTextSize(text.c_str());
    y += textSize.y + padding.y * 3;

    { // Duration
        bb.Min = ImVec2(x, y);
        bb.Max = ImVec2(x + textSize.x + padding.x * 2,
                        y + textSize.y + padding.y * 2);

        ImGui::PushStyleColor(ImGuiCol_Text, ProgramColors().Text);
        drawList->AddText(ImVec2(x + padding.x,
                                 y + padding.y),
                          ImGui::GetColorU32(ImGuiCol_Text), text.c_str());
        ImGui::PopStyleColor();

        window->DC.CursorPos.x = x + ProgramSizes().AlignWidth;
        window->DC.CursorPos.y = y;

        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, padding);
        ImGui::PushItemWidth(ProgramSizes().InputWidth);
        std::string id = "##duration" + std::to_string(window->DC.CursorPos.x);
        ImGui::PushStyleColor(ImGuiCol_FrameBg, ProgramColors().FrameBg);
        ImGui::PushStyleColor(ImGuiCol_Text, ProgramColors().FrameText);
        double duration = custom.getDuration();
        if (ImGui::InputDouble(id.c_str(), &duration, 0, 0, "%0.2f", ImGuiInputTextFlags_CharsNoBlank))
        {
            hasValuesChanged = true;
            custom.setDuration(duration);
        }
        ImGui::PopStyleColor(2);
        ImGui::SameLine();
        ImGui::PopItemWidth();
        ImGui::PopStyleVar();
    }

    text = "speed";
    textSize = ImGui::CalcTextSize(text.c_str());
    double nx = x + ProgramSizes().AlignWidth + ProgramSizes().InputWidth + spacing.x * 4;

    { // Speed
        bb.Min = ImVec2(nx, y);
        bb.Max = ImVec2(nx + textSize.x + padding.x * 2,
                        y + textSize.y + padding.y * 2);

        ImGui::PushStyleColor(ImGuiCol_Text, ProgramColors().Text);
        drawList->AddText(ImVec2(nx + padding.x,
                                 y + padding.y),
                          ImGui::GetColorU32(ImGuiCol_Text), text.c_str());
        ImGui::PopStyleColor();

        window->DC.CursorPos.x = nx + ProgramSizes().AlignWidth;
        window->DC.CursorPos.y = y;

        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, padding);
        ImGui::PushItemWidth(ProgramSizes().InputWidth);
        std::string id = "##speed" + std::to_string(window->DC.CursorPos.x);
        ImGui::PushStyleColor(ImGuiCol_FrameBg, ProgramColors().FrameBg);
        ImGui::PushStyleColor(ImGuiCol_Text, ProgramColors().FrameText);
        double speed = custom.getSpeed();
        if (ImGui::InputDouble(id.c_str(), &speed, 0, 0, "%0.2f", ImGuiInputTextFlags_CharsNoBlank))
        {
            hasValuesChanged = true;
            custom.setSpeed(speed);
        }
        ImGui::PopStyleColor(2);
        ImGui::SameLine();
        ImGui::PopItemWidth();
        ImGui::PopStyleVar();
    }

    text = "start-end";
    textSize = ImGui::CalcTextSize(text.c_str());
    y += textSize.y + padding.y * 3;

    { // Values
        bb.Min = ImVec2(x, y);
        bb.Max = ImVec2(x + textSize.x + padding.x * 2,
                        y + textSize.y + padding.y * 2);

        ImGui::PushStyleColor(ImGuiCol_Text, ProgramColors().Text);
        drawList->AddText(ImVec2(x + padding.x,
                                 y + padding.y),
                          ImGui::GetColorU32(ImGuiCol_Text), text.c_str());
        ImGui::PopStyleColor();

        window->DC.CursorPos.x = x + ProgramSizes().AlignWidth;
        window->DC.CursorPos.y = y;

        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, padding);
        ImGui::PushItemWidth(ProgramSizes().InputWidth * 1.5);
        std::string idStart = "##startValue" + std::to_string(window->DC.CursorPos.x);
        ImGui::PushStyleColor(ImGuiCol_FrameBg, ProgramColors().FrameBg);
        ImGui::PushStyleColor(ImGuiCol_Text, ProgramColors().FrameText);

        if (ImGui::InputDouble(idStart.c_str(), &custom.m_startValue, 0, 0, "%0.4f", ImGuiInputTextFlags_CharsNoBlank))
        {
            custom.computeSpeed();
            hasValuesChanged = true;
        }
        ImGui::SetItemTooltip("Start value");

        ImGui::SameLine();
        window->DC.CursorPos.y = y;

        ImGui::PushStyleColor(ImGuiCol_Text, ProgramColors().Text);
        ImGui::Text("-");
        ImGui::PopStyleColor();

        ImGui::SameLine();
        window->DC.CursorPos.y = y;

        std::string idEnd = "##endValue" + std::to_string(window->DC.CursorPos.x);
        if (ImGui::InputDouble(idEnd.c_str(), &custom.m_endValue, 0, 0, "%0.4f", ImGuiInputTextFlags_CharsNoBlank))
        {
            custom.computeSpeed();
            hasValuesChanged = true;
        }
        ImGui::SetItemTooltip("End Value");

        ImGui::PopStyleColor(2);
        ImGui::SameLine();
        ImGui::PopItemWidth();
        ImGui::PopStyleVar();
    }

    text = "data";
    textSize = ImGui::CalcTextSize(text.c_str());
    y += textSize.y + padding.y * 3;

    { // Data
        bb.Min = ImVec2(x, y);
        bb.Max = ImVec2(x + textSize.x + padding.x * 2,
                        y + textSize.y + padding.y * 2);

        ImGui::PushStyleColor(ImGuiCol_Text, ProgramColors().Text);
        drawList->AddText(ImVec2(x + padding.x,
                                 y + padding.y),
                          ImGui::GetColorU32(ImGuiCol_Text), text.c_str());
        ImGui::PopStyleColor();

        window->DC.CursorPos.x = x + ProgramSizes().AlignWidth;
        window->DC.CursorPos.y = y;

        auto data = custom.m_data;
        std::string label = (data && data->isValid())? data->getLabel(): "drop a data here";
        std::string tooltip = (data && data->isValid())? data->getData()->getPathName(): "Data";

        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, padding);
        ImGui::PushItemWidth(ImGui::CalcTextSize(label.c_str()).x + padding.x * 2);
        ImGui::PushStyleColor(ImGuiCol_FrameBg, ProgramColors().FrameBg);
        ImGui::PushStyleColor(ImGuiCol_Text, ProgramColors().FrameText);

        ImGui::BeginDisabled();
        ImGui::InputText("##data", &label);
        ImGui::EndDisabled();
        ImGui::SetItemTooltip("%s", tooltip.c_str());

        if (ImGui::BeginDragDropTarget())
        {
            if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("_DATAWIDGET"))
            {
                sofa::core::objectmodel::BaseData* dropedData = static_cast<sofa::core::objectmodel::BaseData*>(payload->Data);
                if (dropedData)
                {
                    custom.m_data = std::make_shared<guidata::GUIData>(std::make_shared<guidata::OwnedBaseData>(dropedData, false),
                                                                      std::make_shared<guidata::OwnedBaseData>(nullptr, false),
                                                                      std::make_shared<guidata::OwnedBaseData>(nullptr, false),
                                                                      dropedData->getName(),
                                                                      guidata::GUIData::DEFAULTGROUP,
                                                                      "");
                }
            }
            ImGui::EndDragDropTarget();
        }

        ImGui::PopStyleColor(2);
        ImGui::SameLine();
        ImGui::PopItemWidth();
        ImGui::PopStyleVar();
    }

    window->DC.CursorPosPrevLine.x = topRight.x;
    window->DC.CursorPosPrevLine.y = topRight.y;

    ImGui::PopClipRect();
    return hasValuesChanged;
}

} // namespace


