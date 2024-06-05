#include "Target.h"

Target::Target(int size, int weight, int height, std::string const& name_texture, std::string const& file_texture, int x, int y, int dx, int dy)
                : pos(x, y), is_active(true), h(height), w(weight), target{}, animator(target)
{
    koef = static_cast<float>(size) / static_cast<float>(h);
    target.setScale(koef, koef);
    goal_pos.x = x + static_cast<float>(dx) * koef;
    goal_pos.y = y + static_cast<float>(dy) * koef;
    target.setPosition(pos.x, pos.y);
    auto& targetAnimation = animator.CreateAnimation(name_texture, file_texture, seconds(1), true);
    targetAnimation.AddFrames(Vector2i(0, 0), Vector2i(w, h), 3, 2);
}

Target::~Target()
{

}

