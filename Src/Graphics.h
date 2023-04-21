/*!************************************************************************
 * \file    Graphics.h
 * \author  Han Wei, Dylan (100%)
 * \par     DP email: dylan.h\@digipen.edu
 * \par     GAM150
 * \date    15-01-2023
 * \brief
 *   Defines wrapper functions that handle creating or drawing
 *		AEengine's graphic elements.
 *************************************************************************/

#pragma once
#include "pch.h"

namespace Graphics
{

	void Draw(Entity& _entity);

	AEGfxVertexList* CreateQuadMesh(const f32& _width, const f32& _height, const u32& _color = Color_White, const f32& _angle = 0.f);

}