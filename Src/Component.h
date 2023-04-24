/*!************************************************************************
 * \file    Component.h
 * \author  Han Wei, Dylan	(50%)
 * \author  Koh Wei Jie		(50%)
 * \par     DP email: dylan.h\@digipen.edu
 * \par     DP email: wejie.koh\@digipen.edu
 * \par     GAM150
 * \date    01-02-2023
 * \brief
 *   This header file declares the Entity and Component classes.
 *	 It defines several template functions involved in getting
 *	  and setting entity/component data.
 *************************************************************************/

#pragma once
#include "pch.h"

using ComponentID = u32;
class Component;

/*!*************************************************************************
 * \brief
 * Enum of components. Aid for component Bitset.
***************************************************************************/
enum Components {
	Component_Transform = 0,
	Component_Renderable,
	Component_UI_Element,
	COMPONENTS_MAX
};

/*!*************************************************************************
 * \brief
 * Registers ID for new component
 * Returns a new id.
***************************************************************************/
inline ComponentID GetComponentID()
{
	static ComponentID lastID = 0;
	return lastID++;
}

/*!*************************************************************************
 * \brief
 * Registers ID for new component
 * Static typeID initializer is called ONCE per template type
 * Returns ID of component
***************************************************************************/
template <typename T>
inline ComponentID GetComponentTypeID() noexcept
{
	static ComponentID typeID = GetComponentID();
	return typeID;
}

/*!*************************************************************************
 * \brief
 * Is basically just a container for holding components.
 * Contains supporting functions to access said components.
***************************************************************************/
class Entity
{
private:
public:

	Entity() {}

	~Entity();

	virtual void Unload();

	/*!*************************************************************************
	 * \brief
	 * Checks component bitset if entity holds specified component T.
	 * \return
	 * true  - component exists
	 * false - component does not exist
	***************************************************************************/
	template <typename T>
	bool HasComponent()
	{
		return m_ComponentBitset[GetComponentTypeID<T>()];
	}

	/*!*************************************************************************
	 * \brief
	 * Gets specified component T if it exists.
	 * \return
	 * T*      - component exists
	 * nullptr - component does not exist
	***************************************************************************/
	template <typename T>
	T* GetComponent()
	{
		if (!HasComponent<T>())
			return nullptr;
		return static_cast<T*>(m_ComponentList[GetComponentTypeID<T>()]);
	}

	/*!*************************************************************************
	 * \brief
	 * A variadic function template.
	 * Adds component T to entity if it does not exist.
	 * \param[in] ..._args
	 * Variadic args - (n) number of arguments based on T's constructor(s).
	 * \return
	 * T* - Pointer to newly created / existing component
	***************************************************************************/
	template <typename T, typename ...Args>
	T* AddComponent(Args&&... _args)
	{
		if (HasComponent<T>())
			return GetComponent<T>();

		T* component(new T(std::forward<Args>(_args)...));
		this->m_ComponentList[GetComponentTypeID<T>()] = component;
		this->m_ComponentBitset[GetComponentTypeID<T>()] = true;
		component->pEntity = this;

		return component;
	}
private:
	// array of components, initialized to size of COMPONENTS_MAX
	std::array<Component*, COMPONENTS_MAX> m_ComponentList{ nullptr };
	// Component bitset, helps with checking if component exists within entity
	std::bitset<COMPONENTS_MAX> m_ComponentBitset{};
};

/*!*************************************************************************
 * \brief
 * The superclass of all components.
 * Use GetComponent<T>() to retrieve pointer to other component.
***************************************************************************/
class Component
{
private:
	friend class Entity;
public:
	Component(Entity* _ent = nullptr) : pEntity(_ent) {}

	inline virtual ~Component() {}

	/*!*************************************************************************
	 * \brief
	 * Call to entity's GetComponent function.
	***************************************************************************/
	template <typename T>
	T* GetComponent() const
	{
		return !pEntity ? nullptr : pEntity->GetComponent<T>();
	}

	/*!*************************************************************************
	 * \brief
	 * Get pointer to component's entity.
	***************************************************************************/
	Entity* GetEntity();
private:
	Entity* pEntity;
};

/*!*************************************************************************
 * \brief
 * Transform(f32 x, f32 y, f32 w, f32 h, f32 r)
 * Position, Width, Height and Rotation of object.
***************************************************************************/
struct Transform : public Component
{
	AEVec2 Pos = { 0.f,0.f };

	f32 Width = 0.f;
	f32 Height = 0.f;
	f32 Rotation = 0.f;

	Transform() {};
	Transform(f32 x, f32 y, f32 w, f32 h) :
		Pos({ x,y }), Width(w), Height(h) {}
	Transform(f32 x, f32 y, f32 w, f32 h, f32 r) :
		Pos({ x,y }), Width(w), Height(h), Rotation(r) {}
	
};

/*!*************************************************************************
 * \brief
 * Renderable()
 * Mesh, Texture, and DrawMode of object.
***************************************************************************/
struct Renderable : public Component
{
	AEGfxVertexList* Mesh;
	AEGfxTexture* Texture;
	AEGfxMeshDrawMode	DrawMode = AE_GFX_MDM_TRIANGLES;

	Renderable();
	Renderable(f32 _width, f32 _height, u32 _color);
	Renderable(f32 _width, f32 _height, std::string);
	Renderable(AEGfxVertexList* _mesh, AEGfxTexture* _texture = nullptr);

	~Renderable() override;
};

struct UI_Element : public Component
{
	// Transform
	// Rendarable
	//AEVec2 Pos{};
	//f32 Width{}, Height{};
	bool visible{ true };
	bool enabled{ true };
	std::vector<Entity*> childElements{}; // Wld this work? or need to be pointers of enitites
	std::vector<void(*)(Entity&)> m_OnClickListeners{};

	void RegisterOnClick(void(*)(Entity&));

	UI_Element();
	//UI_Element(AEVec2 _pos, f32 _width, f32 _height);
	//UI_Element(AEVec2 _pos, f32 _width, f32 _height, bool _visible, bool _enabled);
	UI_Element( bool _visible, bool _enabled);

};