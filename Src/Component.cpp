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

//======== Collision Stuff

AABBCollider::AABBCollider(Transform* trans)
{
	AEVec2	entityOffset{ trans->Width / 2,trans->Height / 2 };
	minPt = trans->Pos - entityOffset;
	maxPt = trans->Pos + entityOffset;
}

// Super Inefficient but eh for now testing use



namespace algo
{
	CollisionPoints FindAABB_PointCollisionPoints(Entity& entity, AEVec2 point)
	{
		auto& aabb = *entity.GetComponent<AABBCollider>();
		
		CollisionPoints pt{};


		if ((point.x >= aabb.minPt.x && point.x <= aabb.maxPt.x) &&
			(point.y >= aabb.minPt.y && point.y <= aabb.maxPt.y))
			pt.HasCollision = true;

		// Current just changes "pt.HasCollision"
		// doesnt fill the other data of the CollisionPoints data type
		/*
			AEVec2 A{}; // Futherest point of A into B
			AEVec2 B{}; // Futherest point of B into A
			AEVec2 Normal{}; // B-A Normalised
			f32 Depth{}; // Length of B - A
		*/
		return pt;
	}

	// Could be Optimized with CSD1130 Gameplay Implementation technique stuff cuz now only handle stationary entities
	// Other suggestions would be Gilbert-Johnson-Keerthi (GJK) algorithm Expanding Polytope Algorithm (EPA).
	CollisionPoints FindAABB_AABBCollisionPoints(Entity& entity1, Entity& entity2)
	{
		auto& aabb1 = *entity1.GetComponent<AABBCollider>();
		auto& aabb2 = *entity2.GetComponent<AABBCollider>();
		auto& trans1 = *entity1.GetComponent<Transform>();
		auto& trans2 = *entity2.GetComponent<Transform>();

		CollisionPoints pt{};

		if (aabb1.minPt.x < aabb2.maxPt.x && aabb1.maxPt.x > aabb2.minPt.x &&
			aabb1.minPt.y < aabb2.maxPt.y && aabb1.maxPt.y > aabb2.minPt.y)
			pt.HasCollision = true;

		AEVec2Sub(&pt.A, &trans1.Pos, &trans2.Pos);
		AEVec2Sub(&pt.B, &trans2.Pos, &trans1.Pos);

		AEVec2Normalize(&pt.A, &pt.A);
		AEVec2Normalize(&pt.B, &pt.B);

		AEVec2Scale(&pt.A, &pt.A, trans1.Width);
		AEVec2Scale(&pt.B, &pt.B, trans1.Width); // Not sure if the pt.A and pt.B are accurate

		AEVec2Sub(&pt.Normal, &pt.B, &pt.A);
		pt.Depth = AEVec2Length(&pt.Normal);

		return pt;
	}
}

