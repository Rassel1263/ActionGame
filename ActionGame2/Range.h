#pragma once

class Range : public Object
{
public:
    Unit* my = NULL;
    Unit* target = NULL;
    std::wstring targetName;
    D3DXVECTOR2 addPos;
    bool bHit = false;
    Range(Unit* unit, std::wstring targetName, D3DXVECTOR2 addPos, D3DXVECTOR2 min, D3DXVECTOR2 max, D3DXCOLOR color);

    virtual void Update(float deltaTime) override;
    virtual void Render() override;
    virtual void OnCollision(Collider& coll) override;
};