#include "Target.h"

Target::Target(int size, int weight, int height, std::string const& name_texture, std::string const& file_texture, int x, int y, int dx, int dy)
                : pos(x, y), is_active(true), h(height), w(weight), target{}, animator(target)
{
    koef = static_cast<float>(size) / static_cast<float>(h);
    target.setScale(koef, koef);
    delta = Vector2i(dx, dy);
    this->setGoalPosition();
    target.setPosition(x, y);
    auto& targetAnimation = animator.CreateAnimation(name_texture, file_texture, seconds(1), true);
    targetAnimation.AddFrames(Vector2i(0, 0), Vector2i(w, h), 3, 2);
}

Target::~Target()
{

}

