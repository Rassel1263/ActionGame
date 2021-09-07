#include "DXUT.h"
#include "Object.h"

inline bool Check(Object* obj)
{
	if (obj->destroy)
		return true;
	else
		return false;
}

inline bool CheckUI(ObjectUI* obj)
{
	if (obj->destroy)
		return true;
	else
		return false;
}
      
void Object::SetRigid(float mass)
{
	gravity = 9.8f;
	this->bRigid = true;
	this->mass = mass;
}

void Object::Update(float deltaTime)
{
	if (bRigid)
	{
		if (!bGround)
			force.y -= gravity * 20 * mass * deltaTime;

		velocity += force * (1/ mass) * 10;
		force = { 0, 0 };
		fixedPos = pos;
		pos += velocity * deltaTime;

		if (abs(velocity.x) >= 100)
			velocity.x -= (bGround ? 100 : 10) * velocity.x / abs(velocity.x) * min(abs(velocity.x), 100) * deltaTime;
		else
			velocity.x = 0;

		if (pos.y <= groundPos)
		{
			bGround = true;
			pos.y = groundPos;
		}
		else
			bGround = false;
	}
}

void Object::Render()
{
#ifdef _DEBUG
	if (bCollider)
	{
		for (auto body : bodies)
		{
			D3DXMATRIX matrix;

			if (bCamera)
				D3DXMatrixTranslation(&matrix, pos.x, pos.y, 0.0f);
			else
				D3DXMatrixTranslation(&matrix, pos.x + Camera::GetInstance().cameraPos.x, pos.y + Camera::GetInstance().cameraPos.y, 0.0f);

			if (body.type == Collider::TYPE::AABB)
			{
				Game::GetInstance().DrawLine(body.aabb.min, D3DXVECTOR2(body.aabb.max.x, body.aabb.min.y), matrix, body.color);
				Game::GetInstance().DrawLine(D3DXVECTOR2(body.aabb.max.x, body.aabb.min.y), body.aabb.max, matrix, body.color);
				Game::GetInstance().DrawLine(body.aabb.max, D3DXVECTOR2(body.aabb.min.x, body.aabb.max.y), matrix, body.color);
				Game::GetInstance().DrawLine(D3DXVECTOR2(body.aabb.min.x, body.aabb.max.y), body.aabb.min, matrix, body.color);
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
	for (auto& obj : objects)
		SAFE_DELETE(obj);

	for (auto& obj : uiObjects)
		SAFE_DELETE(obj);

	for (auto& addObj : addObjects)
		SAFE_DELETE(addObj);

	for (auto& addObj : addUIObjects)
		SAFE_DELETE(addObj);
}


void ObjectManager::AddObject(Object* obj)
{
	addObjects.push_back(obj);
}

void ObjectManager::AddObject(ObjectUI* obj)
{
	addUIObjects.push_back(obj);
}

void ObjectManager::Collision()
{
	for (auto it = objects.begin(); it != objects.end(); ++it)
	{
		for (auto it2 = it + 1; it2 != objects.end(); ++it2)
		{
			if (!(*it)->bCollider || !(*it2)->bCollider) continue;

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

void ObjectManager::Update(float deltaTime)
{
	objects.insert(objects.end(), addObjects.begin(), addObjects.end());
	addObjects.clear();

	uiObjects.insert(uiObjects.end(), addUIObjects.begin(), addUIObjects.end());
	addUIObjects.clear();

	std::sort(objects.begin(), objects.end(), [](const Object* rhs, const Object* lhs) { return rhs->layer < lhs->layer; });
	std::sort(uiObjects.begin(), uiObjects.end(), [](const ObjectUI* rhs, const ObjectUI* lhs) { return rhs->layer < lhs->layer; });

	for (auto& object : objects)
		object->Update(deltaTime);

	for (auto& object : uiObjects)
		object->Update(deltaTime);

	objects.erase(std::remove_if(objects.begin(), objects.end(), Check), objects.end());
	uiObjects.erase(std::remove_if(uiObjects.begin(), uiObjects.end(), CheckUI), uiObjects.end());

}

void ObjectManager::Render()
{
	for (auto& obj : objects)
		obj->Render();
}

void ObjectManager::UIRender()
{
	for (auto& obj : uiObjects)
		obj->Render();
}

void ObjectUI::Update(float deltaTime)
{
}

void ObjectUI::Render()
{
}

void ObjectUI::OnCollision(Collider& coll)
{
}
