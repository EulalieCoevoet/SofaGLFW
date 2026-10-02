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
#pragma once

#include <SofaImGui/models/BaseBlock.h>
#include <SofaImGui/config.h>

#include <imgui.h>
#include <imgui_internal.h>

namespace sofaimgui::models {
class Track;
}

namespace sofaimgui::models {

class Group: public std::enable_shared_from_this< Group >, public BaseBlock
{
    typedef sofa::defaulttype::RigidCoord<3, double> RigidCoord;

public:

    typedef std::shared_ptr<Group> SPtr;

    using BaseBlock::m_duration;

    Group(const double& duration):
        BaseBlock(duration)
    {
    }

    virtual ~Group() = default;

    void setLength(const double &length) {m_length=length;}
    double getLength() {return m_length;}

protected:
    float m_length;

    class GroupView: public BaseBlockView
    {
    };
    GroupView view;

public :

    GroupView* getView() override {return &view;}
};

} // namespace


