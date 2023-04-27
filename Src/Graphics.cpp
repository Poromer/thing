/*!************************************************************************
 * \file    Graphics.cpp
 * \author  Han Wei, Dylan (100%)
 * \par     DP email: dylan.h\@digipen.edu
 * \par     GAM150
 * \date    15-01-2023
 * \brief
 *   Source code of wrapper functions that handle creating or drawing
 *		AEengine's graphic elements.
 *************************************************************************/

#include "pch.h"
#include "Graphics.h"

namespace Graphics
{
	/*!*************************************************************************
	 * \brief
	 * Draws a mesh and texture in renderable at given transform's position.
	***************************************************************************/
	void Draw(Entity& _entity)
	{
		auto _transform = _entity.GetComponent<Transform>();
		auto _renderable = _entity.GetComponent<Renderable>();

		if (!_renderable->Mesh)
			return;
		AEGfxSetBlendMode(AE_GFX_BM_BLEND);
		AEGfxSetRenderMode(AE_GFX_RM_COLOR);
		if (_renderable->Texture)
			AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
		AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
		AEGfxSetPosition(_transform->Pos.x, _transform->Pos.y);
		AEGfxTextureSet(_renderable->Texture, 0, 0);
		AEGfxSetTransparency(1.0f);
		AEGfxMeshDraw(_renderable->Mesh, _renderable->DrawMode);
	}

	/*!*************************************************************************
	 * \brief
	 * Create a quad mesh based on width, height, color and angle (in degrees).
	 * Color is defaulted to white and angle is defaulted to 0 deg.
	***************************************************************************/
	AEGfxVertexList* CreateQuadMesh(const f32& _width, const f32& _height, const u32& _color, const f32& _angle)
	{
		AEGfxVertexList* mesh = nullptr;

		AEGfxMeshStart();
		if (!_angle) {
			AEGfxTriAdd(
				-_width * 0.5f, -_height * 0.5f, _color, 0.0f, 1.0f,
				_width * 0.5f, -_height * 0.5f, _color, 1.0f, 1.0f,
				-_width * 0.5f, _height * 0.5f, _color, 0.0f, 0.0f);

			AEGfxTriAdd(
				_width * 0.5f, -_height * 0.5f, _color, 1.0f, 1.0f,
				_width * 0.5f, _height * 0.5f, _color, 1.0f, 0.0f,
				-_width * 0.5f, _height * 0.5f, _color, 0.0f, 0.0f);
		}
		else {
			AEVec2 arr[6] = {
				AEVec2{-_width * 0.5f, -_height * 0.5f},
				AEVec2{ _width * 0.5f, -_height * 0.5f},
				AEVec2{-_width * 0.5f,  _height * 0.5f},

				AEVec2{ _width * 0.5f, -_height * 0.5f},
				AEVec2{ _width * 0.5f,  _height * 0.5f},
				AEVec2{-_width * 0.5f,  _height * 0.5f}
			};
			AEMtx33 rotmtx;
			AEMtx33RotDeg(&rotmtx, _angle);
			AEMtx33MultVecArray(arr, &rotmtx, arr, 6);

			AEGfxTriAdd(
				arr[0].x, arr[0].y, _color, 0.0f, 1.0f,
				arr[1].x, arr[1].y, _color, 1.0f, 1.0f,
				arr[2].x, arr[2].y, _color, 0.0f, 0.0f);

			AEGfxTriAdd(
				arr[3].x, arr[3].y, _color, 1.0f, 1.0f,
				arr[4].x, arr[4].y, _color, 1.0f, 0.0f,
				arr[5].x, arr[5].y, _color, 0.0f, 0.0f);
		}
		mesh = AEGfxMeshEnd();
		return mesh;
	}

}