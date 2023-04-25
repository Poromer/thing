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

UI_Element::UI_Element(bool _visible, bool _enabled)
	: visible(_visible), enabled(_enabled)
{

}

// Overloaded operator== to remove userdefined type of "UI_Event" from 'events' member in UI_Manager
// Need the operator== to be overload to do a comparisim to find the event to remove, since the vector is
// holding the value and not the address to said values thus a overload is needed for comparing
bool UI_Event::operator==(UI_Event const& rhs) // Jank AF but eh
{
	if (
		(this->eventType == rhs.eventType) &&
		(this->eventCall == rhs.eventCall) &&
		(this->entity == rhs.entity)&&
		(this->key == rhs.key)&&
		(this->currsorPos == rhs.currsorPos)&&
		(this->text == rhs.text)
		)
	{
		return true;
	}
	return false;
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

