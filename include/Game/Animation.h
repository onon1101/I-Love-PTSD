#ifndef ANIMATION_H
#define ANIMATION_H

#include "Dungeon/Elements.h"
#include "ToolBoxs.h"
#include "Util/Time.hpp"

class Animation {
public:
    virtual void MoveByTime(const unsigned long &duringTimeMs,
                            const glm::vec2 &destination,
                            const uint16_t &direction);

protected:
    void UpdateAnimation();
    const std::vector<glm::vec2> m_MoveAnimation = {
        {0, Dungeon::DUNGEON_TILE_WIDTH},
        {Dungeon::DUNGEON_TILE_WIDTH / 2, Dungeon::DUNGEON_TILE_WIDTH},
        {-Dungeon::DUNGEON_TILE_WIDTH / 4, Dungeon::DUNGEON_TILE_WIDTH},
        {-Dungeon::DUNGEON_TILE_WIDTH / 2, Dungeon::DUNGEON_TILE_WIDTH},
        {0, 0}};

    bool m_IsAnimating = false;
    unsigned long m_AnimationStartMs = 0;
    unsigned long m_AnimationDuringTimeMs;
    glm::vec2 m_AnimationDestination = {1e9, 1e9};
    uint16_t m_AnimationDirection;
    glm::vec2 m_AnimationPosition = {-1e9, -1e9};
};

#endif
