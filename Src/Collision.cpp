#include "pch.h"
#include "Collision.h"

namespace Collision
{
	bool IsPointAABB_Collision(AEVec2 point, Entity& entity)
	{
		Transform* trans = entity.GetComponent<Transform>();
		AEVec2 entity1Offset{ trans->Width / 2,trans->Height / 2 };
		AEVec2 minPt{ trans->Pos - entity1Offset }, maxPt{ trans->Pos + entity1Offset };

		if ((point.x >= minPt.x && point.x <= maxPt.x) && (point.y >= minPt.y && point.y <= maxPt.y))
			return true;
		return false;
	}

	bool IsAABBAABB_Collision(Entity& entity1, Entity& entity2)
	{
		Transform* trans1 = entity1.GetComponent<Transform>();
		Transform* trans2 = entity2.GetComponent<Transform>();

		AEVec2 entity1Offset{ trans1->Width / 2,trans1->Height / 2 };
		AEVec2 entity2Offset{ trans1->Width / 2,trans2->Height / 2 };

		AEVec2 entity1MinPt{ trans1->Pos - entity1Offset }, entity1MaxPt{ trans1->Pos + entity1Offset };
		AEVec2 entity2MinPt{ trans2->Pos - entity2Offset }, entity2MaxPt{ trans2->Pos + entity2Offset };



		return true;
	}
}