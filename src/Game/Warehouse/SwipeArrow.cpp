#include "Game/Warehouse/SwipeArrow.h"
#include <memory>
#include "Player_config.h"
#include "SpriteSheet.hpp"
#include "Util/Logger.hpp"
#include "Util/Time.hpp"

Game::Warehouse::SwipeArrow::SwipeArrow() {
    m_Drawable = std::make_shared<SpriteSheet>(
        Players::Config::IMAGE_SWIPE_ARROW.data(),
        glm::vec2{36, 24},
        std::vector<std::size_t>{0, 1, 2, 3},
        true,
        100,
        true,
        100
    );
    SetDrawable(m_Drawable);
    SetZIndex(Players::Config::VAL_ZINDEX);
    SetScale(Players::Config::VAL_SCALE);
    SetVisible(true);
}

namespace Game::Warehouse {
void SwipeArrow::Play() {
    m_StartPlayTime = Util::Time::GetElapsedTimeMs();
    m_CurrPlayTime = Util::Time::GetElapsedTimeMs();

    SetVisible(true);
    m_Drawable->SetCurrentFrame(0);
    m_Drawable->Play();
}
void SwipeArrow::Update() {
    LOG_INFO(
        "time {} {}",
        Util::Time::GetElapsedTimeMs(),
        Util::Time::GetDeltaTimeMs()
    );

    m_CurrPlayTime += Util::Time::GetDeltaTimeMs();
    if (m_Drawable && m_StartPlayTime + 400 <= m_CurrPlayTime) {
        SetVisible(false);
        m_Drawable->Pause();
    }
}
}  // namespace Game::Warehouse
