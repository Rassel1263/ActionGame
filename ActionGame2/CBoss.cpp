#include "DXUT.h"
#include "CBoss.h"

CBoss::CBoss()
{
    team = L"enemy";
    ri.scale.x = -1;
    this->pos = D3DXVECTOR2(1500, 0);
    this->groundPos = pos.y;
    this->superArmor = true;

    SetRigid(1);

    colorShader = new ColorShader();
    outlineShader = new OutlineShader();

    nowScene->obm.AddObject(new BossUI(this));
    nowScene->obm.AddObject(new BossIntro());
}

void CBoss::Update(float deltaTime)
{
    UpdatePattern(deltaTime);

    if (spAmount <= 0.0f)
    {
        spHealTimer += deltaTime;

        if (spHealTimer >= 3.0f)
        {
            spAmount = spMaxAmout;
            spHealTimer = 0.0f;
            superArmor = true;
        }
    }

    if (nowState)
        nowState->UpdateState(this, deltaTime);

    Unit::Update(deltaTime);
}

void CBoss::Render()
{
    ri.pos = pos;
    GetSprite(Images::SHADOW).Render(RenderInfo{ D3DXVECTOR2(ri.pos.x, groundPos) });

    if (hit)
        colorShader->Render(colorShader, GetNowSprite(), ri, D3DXVECTOR4(1.0, 1.0, 1.0, 0.8f));
    else if (superArmor)
        outlineShader->Render(outlineShader, GetNowSprite(), ri, D3DXVECTOR4(1.0f, 0, 0, 1.0f));
    else
        GetNowSprite().Render(ri);


    Object::Render();
}

void CBoss::OnCollision(Collider& coli)
{
    if (coli.tag == L"playerbullet")
    {
        if (abs(groundPos - coli.obj->groundPos) >= 100) return;

        auto pBullet = static_cast<Bullet*>(coli.obj);
        if (pBullet->type == Bullet::Type::SNIPER)
            if (!hit) nowScene->obm.AddObject(new Effect(L"Player/Explode_sniper", pBullet->pos, D3DXVECTOR2(1.0, 1.0), D3DXVECTOR2(0.5, 0.5), 0.05f));
        Hit(pBullet->damage, pBullet->attackVector);
    }
}


void CBoss::Hit(float damage, D3DXVECTOR2 addForce)
{
    if (hit) return;

    Unit::Hit(damage, addForce);

    spAmount -= damage;
    if (spAmount <= 0.0f)
    {
        superArmor = false;
        spAmount = 0.0f;
    }

    if (nowScene->player->attackNum == -1)
    {
        nowScene->obm.AddObject(new Effect(L"Player/Hit1", pos + D3DXVECTOR2(0, 150) + nowScene->GetRandomVector(-70, 70, -100, 100), D3DXVECTOR2(0.4, 0.4), D3DXVECTOR2(0.5, 0.5), 0.5f, true));
        nowScene->obm.AddObject(new Mp(pos + D3DXVECTOR2(0, 150), nowScene->GetRandomNum(0, 360), nowScene->GetRandomNum(1, 2) * 0.1f));
    }
    if (nowScene->player->attackNum == 0)
    {
        nowScene->obm.AddObject(new Mp(pos + D3DXVECTOR2(0, 150), nowScene->GetRandomNum(0, 360), nowScene->GetRandomNum(10, 15) * 0.1f));
    }
    else if (nowScene->player->attackNum == 2)
    {
        nowScene->obm.AddObject(new Effect(L"Player/Explode_sniper", pos + D3DXVECTOR2(0, 150) + nowScene->GetRandomVector(-70, 70, -100, 100), D3DXVECTOR2(0.4, 0.4), D3DXVECTOR2(0.5, 0.5), 0.5f, true));
        nowScene->obm.AddObject(new Mp(pos + D3DXVECTOR2(0, 150), nowScene->GetRandomNum(0, 360), nowScene->GetRandomNum(1, 2) * 0.1f));
    }
    else
        nowScene->obm.AddObject(new Mp(pos + D3DXVECTOR2(0, 150), nowScene->GetRandomNum(0, 360), nowScene->GetRandomNum(3, 5) * 0.1f));

    nowScene->player->PlusCombo(1);
}

bool CBoss::Move(float deltaTime)
{
    D3DXVECTOR2 dir = { 0, 0 };
    D3DXVec2Normalize(&dir, &GetDistanceFromTarget(nowScene->player->pos));

    if (!DetectColliderTarget())
        return false;

    ri.scale.x = (dir.x > 0) ? 1 : -1;
    pos.x += dir.x * 100 * deltaTime;
    groundPos += dir.y * 50 * deltaTime;

    return true;
}

void CBoss::UpdatePattern(float deltaTime)
{
    if (!nowScene->player->fallowCamera) return;

    if (pattern == 0)
    {
        restTime += deltaTime;

        if (restTime >= 0.5f)
        {
            restTime = 0.0f;
            pattern = ChoosePattern();
        }
    }
}

int CBoss::ChoosePattern()
{
    D3DXVECTOR2 dir = { 0, 0 };
    D3DXVec2Normalize(&dir, &GetDistanceFromTarget(nowScene->player->pos));

    if (abs(dir.y) > 0.2)
        return 2;
    else
        return 1;
}

bool CBoss::DetectColliderTarget()
{
    if (detectRange == NULL)
        return false;

    if (detectRange->bHit)
    {
        detectRange->bHit = false;
        return true;
    }
    else
        return false;
}

void CBoss::SetState(CState<CBoss>* nextState)
{
    if (nowState)
        nowState->ExitState(this);

    nowState = nextState;
    nowState->EnterState(this);
}

void CBoss::ResetPattern()
{
    pattern = 0;
    onAttack = false;
    rushIndex = 0;
}
