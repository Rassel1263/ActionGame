#pragma once

class Collider;
class Object
{
public:
	int layer = 0;
	bool destroy = false;
	bool bCollision = false;

	std::vector<Collider> bodies;
	D3DXVECTOR2 pos = { 0, 0 };
	float z = 0;

	bool bGround = true;
	float gravity = 1;
	float groundPosY = 0;
	D3DXVECTOR2 velocity = { 0, 0 };
	D3DXVECTOR2 force = { 0, 0 };
	D3DXVECTOR2 fixedPos;

	virtual void Update(float deltaTime);
	virtual void Render();
	virtual void OnCollision(Collider& obj);
};

class ObjectManager
{
	std::vector<Object*> objects;
	std::vector<Object*> addObjects;

public:
	virtual ~ObjectManager();

	void AddObject(Object* obj);
	void Update(float deltaTime);
	void Collision();
	void Render();
};

