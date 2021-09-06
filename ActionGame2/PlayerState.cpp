#include "DXUT.h"
#include "PlayerState.h"

PlayerIdle* PlayerIdle::GetInstance()
{
    static PlayerIdle instance;
    return &instance;
}

void PlayerIdle::EnterState(Player* obj)
{
    obj->SetAni(Player::Images::IDLE);
}

void PlayerIdle::UpdateState(Player* obj, float deltaTime)
{
    if (obj->Move(deltaTime))
    {
        obj->SetState(PlayerMove::GetInstance());
        return;
    }

    if (Input::GetInstance().KeyDown('C'))
    {
        obj->SetState(PlayerJump::GetInstance());
        return;
    }

    if (Input::GetInstance().KeyDown('G'))
    {
        obj->SetState(PlayerGunkata::GetInstance());
        return;
    }
}

void PlayerIdle::ExitState(Player* obj)
{
}

///////////////////////////
// Move
///////////////////////////

PlayerMove* PlayerMove::GetInstance()
{
    static PlayerMove instance;
    return &instance;
}

void PlayerMove::EnterState(Player* obj)
{
    obj->SetAni(Player::Images::MOVE);
}

void PlayerMove::UpdateState(Player* obj, float deltaTime)
{
    if (!obj->Move(deltaTime))
    {
        obj->SetState(PlayerIdle::GetInstance());
        return;
    }
}

void PlayerMove::ExitState(Player* obj)
{
}

PlayerJump* PlayerJump::GetInstance()
{
    static PlayerJump instance;
    return &instance;;
}

void PlayerJump::EnterState(Player* obj)
{
    obj->SetAni(Player::Images::JUMP);

    obj->velocity.y = 800;
}

void PlayerJump::UpdateState(Player* obj, float deltaTime)
{
   

    if (obj->bGround)
    {
        obj->SetState(PlayerIdle::GetInstance());
        return;
    }
}

void PlayerJump::ExitState(Player* obj)
{
}

PlayerFall* PlayerFall::GetInstance()
{
    static PlayerFall instance;
    return &instance;
}

void PlayerFall::EnterState(Player* obj)
{
}

void PlayerFall::UpdateState(Player* obj, float deltaTime)
{
}

void PlayerFall::ExitState(Player* obj)
{
}

PlayerSliding* PlayerSliding::GetInstance()
{
    static PlayerSliding instance;
    return &instance;
}

void PlayerSliding::EnterState(Player* obj)
{
}

void PlayerSliding::UpdateState(Player* obj, float deltaTime)
{
}

void PlayerSliding::ExitState(Player* obj)
{
}

PlayerGunkata* PlayerGunkata::GetInstance()
{
    static PlayerGunkata instance;
    return &instance;
}

void PlayerGunkata::EnterState(Player* obj)
{
    obj->SetAni(Player::Images::GUNKATA);
}

void PlayerGunkata::UpdateState(Player* obj, float deltaTime)
{
    afterImageTime += deltaTime;

    if (afterImageTime >= 0.1f)
    {
        nowScene->obm.AddObject(new AfterImage(obj->GetNowSprite(), obj->ri, obj->pos, 0.5f, D3DCOLOR_ARGB(255, 0, 0, 0)));
        afterImageTime = 0.0f;
    }

    if (!obj->GetNowSprite().bAnimation)
    {
        obj->SetState(PlayerIdle::GetInstance());
        return;
    }
}

void PlayerGunkata::ExitState(Player* obj)
{
}
