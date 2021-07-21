#include "DXUT.h"
#include "Collider.h"

Collider::Collider(Object* obj, const std::wstring& tag, const AABB* aabb, const Circle* circle, D3DXCOLOR color)
{
    if (circle)
    {
        type = Type::CIRCLE;
        this->circle = *circle;
    }
    else if (aabb)
    {
        type = Type::AABB;
        this->aabb = *aabb;
    }

    this->tag = tag;
    this->obj = obj;
    this->color = color;
    obj->bCollision = true;
}

bool IntersectCollider(const Collider& coli1, const Collider& coli2)
{
    if (coli1.type == Collider::Type::AABB && coli2.type == Collider::Type::AABB)
    {
        return IntersectAABBAABB(coli1.obj->pos + coli1.aabb.min, coli1.obj->pos + coli1.aabb.max,
            coli2.obj->pos + coli2.aabb.min, coli2.obj->pos + coli2.aabb.max);
    }
    else if (coli1.type == Collider::Type::CIRCLE && coli2.type == Collider::Type::CIRCLE)
    {
        return IntersectCircleCircle(coli1.obj->pos, coli2.circle.radius, coli2.obj->pos, coli2.circle.radius);
    }
}

D3DXVECTOR2 D3DXVec2Rotation(const D3DXVECTOR2& vec1, const float& rotate)
{
    if (vec1 == D3DXVECTOR2(0.0f, 0.0f))
        return D3DXVECTOR2(0.0f, 0.0f);

    float radian = D3DXToRadian(-rotate);
    float sin = sinf(radian);
    float cos = cosf(radian);

    return D3DXVECTOR2(cos* vec1.x - sin * vec1.y, sin* vec1.x + cos * vec1.y);
}

bool IntersectAABBAABB(const D3DXVECTOR2& min, const D3DXVECTOR2& max, const D3DXVECTOR2& min2, const D3DXVECTOR2& max2)
{
    return (min.x < max2.x) && (max.x > min2.x) && (min.y < max2.y) && (max.y > min2.y);
}

bool IntersectCircleCircle(const D3DXVECTOR2& p1, const float& r1, const D3DXVECTOR2 p2, const float& r2)
{
    D3DXVECTOR2 p = D3DXVECTOR2(p2.x - p1.x, p2.y - p1.y);
    return p.x * p.x + p.y * p.y < (r1 + r2)* (r1 + r2);
}

