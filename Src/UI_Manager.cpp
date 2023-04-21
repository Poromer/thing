#include "pch.h"


namespace UI
{
	void InitUI_Element(Entity& entity, f32 width, f32 height, AEVec2 pos, const char* texture)
	{
		/*
		assert(_entity.GetComponent<Transform>() == nullptr);
			tprint("UI Element has no transform");
		assert(_entity.GetComponent<Renderable>() == nullptr);
			tprint("UI Element has no rendarable");
		*/

		// OR [Fail Loudly vs Fail Silently]


		if (entity.GetComponent<Transform>() == nullptr)
			entity.AddComponent<Transform>(pos.x, pos.y, width, height);
		if (entity.GetComponent<Renderable>() == nullptr)
			entity.AddComponent<Renderable>(width, height, texture);

		entity.AddComponent<UI_Element>();
	}

	void GroupUI_Element(Entity& parentEntity, Entity& childEntity)
	{
		UI_Element* parentUI = parentEntity.GetComponent<UI_Element>();
		parentUI->childElements.push_back(&childEntity);
	}

	void UnGroupUI_Element(Entity& parentEntity, Entity& childEntity)
	{
		UI_Element* parentUI = parentEntity.GetComponent<UI_Element>();
		parentUI->childElements.erase(std::remove(parentUI->childElements.begin(), parentUI->childElements.end(), &childEntity));
	}

	void ClickDragUI_Element(Entity& entity)
	{
		Transform* trans = entity.GetComponent<Transform>();
		UI_Element* ui = entity.GetComponent<UI_Element>();
		AEVec2 shiftChild{ Input::GetCursorPositionDelta() };
		shiftChild.x = -shiftChild.x;

		trans->Pos = Input::GetCursorPosition();

		tprint(Input::IsCursorPositionChange());

		if (ui->childElements.empty())
			return;

		for (Entity* child : ui->childElements)
		{
			Transform* child_trans = child->GetComponent<Transform>();
			child_trans->Pos = child_trans->Pos - shiftChild;
		}
		
	}

}
/*
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
*/