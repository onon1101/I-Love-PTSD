#ifndef FUCK_PTSD_2024_05_16_SWIPE_H
#define FUCK_PTSD_2024_05_16_SWIPE_H

#include "UGameElement.h"

namespace Game::Warehouse {
class Swipe : public Util::GameElement {
public:
    Swipe() = default;
    virtual ~Swipe() = default;

    virtual void Play(const glm::ivec2& player2ThrowPos, std::pair<int, int> direct) = 0;
    virtual void Update() = 0;
};
}  // namespace Game::Warehouse

#endif  // FUCK_PTSD_2024_05_16_SWIPE_H
