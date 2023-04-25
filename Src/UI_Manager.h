#include "pch.h"


namespace UI
{
	void InitUI_Element(Entity& entity, f32 width, f32 height, AEVec2 pos, const char* texture = ASSETS::DEBUG_NULLTEXTURE);
	void GroupUI_Element(Entity& parentEntity, Entity& childEntity);
	void UnGroupUI_Element(Entity& parentEntity, Entity& childEntity);
	bool IsCursorOnUI_Element(Entity& entity);
	void ClickDragUI_Element(Entity& entity);
}

class UI_Layer
{
public:
	UI_Layer();
	UI_Layer(std::vector<Entity*> entityList);
	UI_Layer(std::fstream file); // Read text file and init a layer // can try json file as well

	void AddElement(Entity&);
	void RemoveElement(Entity&);
	void ClickDragLayer();


private:
	std::vector<Entity*> layerElements{};
};

class UI_Manager
{
public:
	void AddLayer(UI_Layer&);
	void RemoveLayer(UI_Layer&);
	void AddEvent(UI_Event&);
	void RemoveEvent(UI_Event&);
	void ClearEvent();

private:
	std::vector<UI_Layer*> layers{};
	std::vector<UI_Event> events{};
};

/*

// Event Driven Archietecture

enum class UI_EventType
{
	BUTTON_CLICK = 0,
	EVENT_TOTAL
};

struct UI_Event 
{
	UI_EventType _event;
	AEVec2 _pos;
	u32 _key;
	std::string text;
};

// Callback Functions
using UI_EventCallback = void(*)(const UI_Event&);

// Basic UI_Element -> Childs: Btn, Text Box, Image
class UI_Element
{
public:
	virtual ~UI_Element();

	// Basics
	virtual void AddChild(UI_Element* child);
	virtual void RemoveChild(UI_Element* child);
	virtual void SetPosition(AEVec2 pos);
	virtual void SetSize(f32 width, f32 height);
	virtual void SetVisible(bool visible);
	virtual void SetEnabled(bool endabled);

	// Event Handling
	virtual void AddEventListener(UI_EventType);
	virtual void RemoveEventListener(UI_EventType type, UI_EventCallback const& callback);
	virtual void HandleEvent(UI_Event const& event);

	// Rendering
	virtual void Render();

protected:
	std::vector<UI_Element*> _childElements;
	AEVec2 _position;
	f32 _width;
	f32 _height;
	bool _visible;
	bool _enabled;
};

// Container/Layer of UI_Elements
class UI_Container 
{

};

// Class to manage the overall UI system, including layers, event handling, and rendering.
class UI_Mananger
{

};

*/
