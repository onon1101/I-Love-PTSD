#include "Game/Warehouse/SwipeModule.h"
#include <algorithm>
#include "Factory/SwipeFactor.h"

namespace Game::Warehouse {
SwipeModule::SwipeModule():
      m_GameObject(std::make_shared<Util::GameObject>()) {}

void SwipeModule::AddSwipe(const std::string& type){
    Factory::SwipeFactor swipeFactor;
    const auto&          obj = swipeFactor.MakeSwipe(type);
    m_GameObject->AddChild(obj);
    m_SwipeList.push_back(obj);
}

void SwipeModule::PlayAnimation(std::size_t idx) {
    std::for_each(m_SwipeList.begin(), m_SwipeList.end(), [](const auto& elem) {
        elem->Play({2, 0}, {1 ,0});
    });
//    m_SwipeList[0]->Play();
}

void SwipeModule::Update() {
    std::for_each(m_SwipeList.begin(), m_SwipeList.end(), [](const auto& elem) {
        elem->Update();
    });
}
std::shared_ptr<Util::GameObject> SwipeModule::GetGameObject() {
    return m_GameObject;
}
}  // namespace Game::Warehouse
