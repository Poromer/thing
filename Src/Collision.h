#include "pch.h"

namespace Collision
{
	bool IsPointAABB_Collision(AEVec2 point, Entity& entity);
	bool IsAABBAABB_Collision(Entity& entity1, Entity* entity2);
}