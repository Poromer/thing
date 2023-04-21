#include "pch.h"

void UI_Element::AddChild(UI_Element* child)
{
	_childElements.push_back(child);
}

void UI_Element::RemoveChild(UI_Element* child) 
{
	// std::remove searches the vector for _entity and moves it to the end and returns a new end
	// std::earse removes elements between the new end and the current end
	_childElements.erase(std::remove(_childElements.begin(), _childElements.end(), child), _childElements.end());
}

void UI_Element::SetPosition(AEVec2 pos)
{
	_position = pos;
}

void UI_Element::SetSize(f32 width, f32 height)
{
	_width = width;
	_height - height;
}

void UI_Element::SetVisible(bool visible)
{
	_visible = visible;
}

void UI_Element::SetEnabled(bool endabled)
{
	_enabled = endabled;
}

void UI_Element::Render()
{
	for (const auto& child : _childElements)
	{
		child->Render();
	}
}