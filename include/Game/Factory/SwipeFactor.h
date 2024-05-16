#ifndef FUCK_PTSD_2024_05_16_SWIPEFACTOR_H
#define FUCK_PTSD_2024_05_16_SWIPEFACTOR_H

#include <memory>
#include <string>
#include "Warehouse/Swipe.h"

namespace Game::Factory {

class SwipeFactor final {
public:
    explicit SwipeFactor() = default;

    std::shared_ptr<Warehouse::Swipe> MakeSwipe(const std::string& type);

private:
    void GenArrow();

    std::shared_ptr<Warehouse::Swipe> m_Swipe;
};
}  // namespace Game::Factory

#endif  // FUCK_PTSD_2024_05_16_SWIPEFACTOR_H
