#pragma once
class LoadSprite : public Object
{
public:
    Sprite spr;
    Sprite loading;
    Sprite loadingRepeat;

    Sprite loadingBar;
    Sprite loadingFrame;

    float size = 0;
    float maxSize = 0;

    std::vector<std::thread> threads;
    std::mutex lock;

    bool oneLoad = false;

    float loadTimer = 1.0f;
    LoadSprite();
    ~LoadSprite();

    virtual void Update(float deltaTime) override;
    virtual void Render() override;
};

