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

	void DrawCollider(AABBCollider* collider)
	{
		Entity temp;
		Transform* trans = temp.AddComponent<Transform>();
		Renderable* rend = temp.AddComponent<Renderable>();
		rend->Mesh = Graphics::CreateQuadMesh(collider->maxPt.x - collider->minPt.x, collider->maxPt.y - collider->minPt.y);
		trans->Pos = { collider->minPt.x + (collider->maxPt.x - collider->minPt.x) / 2, collider->minPt.y + (collider->maxPt.y - collider->minPt.y) / 2 };

		Graphics::Draw(temp);
		temp.Unload();
	}

}

