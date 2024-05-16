#include <memory>
#include <stdexcept>
#include "Game/Factory/SwipeFactor.h"
#include "Hash.h"
#include "Warehouse/Swipe.h"
#include "Warehouse/SwipeArrow.h"

namespace Game::Factory {
using namespace Settings::Hash;
std::shared_ptr<Warehouse::Swipe> SwipeFactor::MakeSwipe(const std::string& type
) {
    switch (Settings::Hash::HashConvert(type)) {
    case "Arrow"_hash: GenArrow(); break;
    default: throw std::runtime_error("swipe factor type error");
    }

    return m_Swipe;
}

void SwipeFactor::GenArrow() {
    m_Swipe = std::make_shared<Warehouse::SwipeArrow>();
}

}  // namespace Game::Factory
