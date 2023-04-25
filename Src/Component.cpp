/*!************************************************************************
 * \file    Component.cpp
 * \author  Han Wei, Dylan	(50%)
 * \author  Koh Wei Jie		(50%)
 * \par     DP email: dylan.h\@digipen.edu
 * \par     DP email: wejie.koh\@digipen.edu
 * \par     GAM150
 * \date    01-02-2023
 * \brief
 *   This source file defines certain fucntions of the
 *   Entity and Component classes.
 *************************************************************************/

#include "pch.h"
#include "Component.h"

Entity* Component::GetEntity()
{
	return pEntity;
}

Entity::~Entity()
{
	Unload();
}

Renderable::Renderable()
	: Mesh(nullptr), Texture(nullptr)
{

}

Renderable::Renderable(f32 _width, f32 _height, u32 _color)
	: Mesh(Graphics::CreateQuadMesh(_width, _height, _color)),
	Texture(nullptr)
{

}

Renderable::Renderable(f32 _width, f32 _height, std::string _path)
	: Mesh(Graphics::CreateQuadMesh(_width, _height)),
	Texture(AEGfxTextureLoad(_path.c_str()))
{

}

Renderable::Renderable(AEGfxVertexList* _mesh, AEGfxTexture* _texture)
	: Mesh(_mesh), Texture(_texture)
{
}

Renderable::~Renderable()
{
	if (Mesh)
		AEGfxMeshFree(Mesh);
	if (Texture)
		AEGfxTextureUnload(Texture);
}

// UI_Element Component
UI_Element::UI_Element() 
{
	
}

void UI_Element::RegisterOnClick(void(*onClickFunc)(Entity&))
{
	m_OnClickListeners.push_back(onClickFunc);
}


void UI_Element::RegisterEvent(UI_Event const& event)
{
	m_EventListeners.push_back(event);
}


/*
UI_Element::UI_Element(AEVec2 _pos, f32 _width, f32 _height)
	: Pos(_pos), Width(_width), Height(_height)
{

}

UI_Element::UI_Element(AEVec2 _pos, f32 _width, f32 _height, bool _visible, bool _enabled)
	: Pos(_pos), Width(_width), Height(_height), visible(_visible), enabled(_enabled)
{

}
*/

UI_Element::UI_Element(bool _visible, bool _enabled)
	: visible(_visible), enabled(_enabled)
{

}

/*!*************************************************************************
 * \brief
 * Frees memory allocated to components in an entity.
***************************************************************************/
void Entity::Unload()
{
	for (Component*& c : m_ComponentList) {
		if (!c) continue;
		delete c;
		c = nullptr;
	}
	m_ComponentBitset.reset();
}

