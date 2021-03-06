#include "DXUT.h"
#include "Object.h"

void Object::Update(float deltaTime)
{
	if (bRigid)
	{
		if (!bGround)
			force.y -= gravity * 2;

		velocity += force * 10;
		force = { 0, 0 };
		fixedPos = pos;
		pos += velocity * deltaTime;

		if (abs(velocity.x) >= 100)
			velocity.x -= (bGround ? 100 : 10) * velocity.x / abs(velocity.x) * min(abs(velocity.x), 100) * deltaTime;
		else
			velocity.x = 0;

		if (pos.y <= z)
		{
			bGround = true;
			pos.y = z;
		}
		else
			bGround = false;
	}
}

void Object::Render()
{
#ifdef _DEBUG
	if (bCollision)
	{
		for (auto body : bodies)
		{
			D3DXMATRIX matrix;
			D3DXMatrixTranslation(&matrix, pos.x, pos.y, 0.0f);

			if (body.type == Collider::Type::AABB)
			{
				Game::GetInstance().DrawLine(body.aabb.min, D3DXVECTOR2(body.aabb.max.x, body.aabb.min.y), matrix, body.color);
				Game::GetInstance().DrawLine(D3DXVECTOR2(body.aabb.max.x, body.aabb.min.y), body.aabb.max, matrix, body.color);
				Game::GetInstance().DrawLine(body.aabb.max, D3DXVECTOR2(body.aabb.min.x, body.aabb.max.y), matrix, body.color);
				Game::GetInstance().DrawLine(D3DXVECTOR2(body.aabb.min.x, body.aabb.max.y), body.aabb.min, matrix, body.color);
			}
			else if (body.type == Collider::Type::CIRCLE)
			{
				D3DXVECTOR2 pos[36];
				for (int i = 0; i < 36; ++i)
					pos[i] = D3DXVec2Rotation(D3DXVECTOR2(0.0f, body.circle.radius), i * 10.0f);
				for (int i = 0; i < 36; ++i)
					Game::GetInstance().DrawLine(pos[i], pos[(i + 1) % 36], matrix, body.color);
			}
		}
	}
#endif
}

void Object::OnCollision(Collider& coll)
{
}

ObjectManager::~ObjectManager()
{
}

void ObjectManager::AddObject(Object* addObject)
{
	addObjects.push_back(addObject);
}

void ObjectManager::Update(float deltaTime)
{
	objects.insert(objects.end(), addObjects.begin(), addObjects.end());
	addObjects.clear();

	std::sort(objects.begin(), objects.end(), [](const Object* RO, const Object* LO) -> bool { return RO->layer < LO->layer; });

	for (auto it = objects.begin(); it != objects.end();)
	{
		(*it)->Update(deltaTime);
		if ((*it)->destroy)
		{
			SAFE_DELETE(*it);
			it = objects.erase(it);
		}
		else
			++it;
	}
}

void ObjectManager::Collision()
{
	for (auto it = objects.begin(); it != objects.end(); ++it)
	{
		for (auto it2 = it + 1; it2 != objects.end(); it2++)
		{
			if (!(*it)->bCollision && !(*it2)->bCollision) continue;

			for (auto body1 : (*it)->bodies)
			{
				for (auto body2 : (*it2)->bodies)
				{
					if (IntersectCollider(body1, body2))
					{
						(*it)->OnCollision(body2);
						(*it2)->OnCollision(body1);
					}
				}
			}
		}
	}
}

void ObjectManager::Render()
{
	for (auto object : objects)
		object->Render();
}
