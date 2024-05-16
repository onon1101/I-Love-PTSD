#include "Game/Warehouse/SwipeModule.h"
#include <algorithm>
#include "Factory/SwipeFactor.h"

namespace Game::Warehouse {
void SwipeModule::AddSwipe(const std::string& type) {
    Factory::SwipeFactor swipeFactor;
    const auto&          obj = swipeFactor.MakeSwipe(type);
    m_SwipeList.push_back(obj);
}

void SwipeModule::Update() {
    std::for_each(m_SwipeList.begin(), m_SwipeList.end(), [](const auto& elem) {
        elem->Update();
    });
}
}  // namespace Game::Warehouse
