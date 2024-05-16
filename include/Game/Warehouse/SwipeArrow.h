#ifndef FUCK_PTSD_2024_05_16_SWIPEARROW_H
#define FUCK_PTSD_2024_05_16_SWIPEARROW_H

#include <memory>
#include "Core/Drawable.hpp"
#include "SpriteSheet.hpp"
#include "Warehouse/Swipe.h"
namespace Game::Warehouse {
class SwipeArrow final : public Swipe {
public:
    explicit SwipeArrow();
    virtual ~SwipeArrow() = default;

    void Play() override;

    void Update() override;

private:
    std::size_t m_StartPlayTime = 0;
    std::size_t m_CurrPlayTime = 0;

    std::shared_ptr<SpriteSheet> m_Drawable;
};
}  // namespace Game::Warehouse

#endif  // FUCK_PTSD_2024_05_16_SWIPEARROW_H
