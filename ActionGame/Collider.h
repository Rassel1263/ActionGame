#pragma once
class Collider
{
public:
	enum class Type
	{
		AABB,
		CIRCLE,
	} type;
	
	struct AABB
	{
		D3DXVECTOR2 min = { 0.0f, 0.0f }, max = { 0.0f, 0.0f };
	} aabb;

	struct Circle
	{
		float radius = 0.0f;
	} circle;

	D3DXCOLOR color;

	Collider(Object* obj, const std::wstring& tag, const AABB* aabb, const Circle* circle, D3DXCOLOR color = D3DCOLOR_ARGB(255, 255, 0, 0));

	Object* obj;
	std::wstring tag;
};

bool IntersectCollider(const Collider& coli1, const Collider& coli2);
D3DXVECTOR2 D3DXVec2Rotation(const D3DXVECTOR2& vec1, const float& rotate);
bool IntersectAABBAABB(const D3DXVECTOR2& min, const D3DXVECTOR2& max, const D3DXVECTOR2& min2, const D3DXVECTOR2& max2);
bool IntersectCircleCircle(const D3DXVECTOR2& p1, const float& r1, const D3DXVECTOR2 p2, const float& r2);

