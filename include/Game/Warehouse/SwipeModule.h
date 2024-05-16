#ifndef FUCK_PTSD_2024_05_16_SWIPEMODULE_H
#define FUCK_PTSD_2024_05_16_SWIPEMODULE_H

#include <functional>
#include <iostream>
#include <memory>
#include <vector>
#include "Warehouse/Swipe.h"

namespace Game::Warehouse {
class SwipeModule final {
public:
    explicit SwipeModule() = default;
    virtual ~SwipeModule() = default;

    void AddSwipe(const std::string& type);

    void Update();

private:
    std::vector<std::shared_ptr<Swipe>> m_SwipeList;
    std::vector<std::function<void()>>  m_ListenerQueue;
};
}  // namespace Game::Warehouse

#endif  // FUCK_PTSD_2024_05_16_SWIPEMODULE_H
