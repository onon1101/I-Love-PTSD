#ifndef MAP_H
#define MAP_H

#include "Util/GameObject.hpp"

#include "Camera.h"
#include "Dungeon/Enemy.h"
#include "Dungeon/Level.h"
#include "Dungeon/MapData.h"
#include "Dungeon/Tile.h"
#include "Player.h"
#include "Player/Player.h"

namespace Dungeon {
class Map final : public Util::GameObject {
public:
    Map(const std::shared_ptr<Player> mainCharacter, const std::string &path,
        const size_t levelNum = 1);

    size_t GamePostion2MapIndex(const glm::ivec2 &position) const;

    std::shared_ptr<MapData> GetMapData() const;

    void RemoveEnemy(const size_t position);
    void RemoveWall(const size_t position);
    void OpenDoor(const size_t position);

    void CameraUpdate();
    void TempoUpdate();

    void Update();

private:
    const size_t ALLOW_EXTRA_DRAW = 4;
    bool CheckShowPosition(const glm::vec2 &position1,
                           const glm::vec2 &position2);
    bool isVaildPosition(const glm::ivec2 &position);
    bool isVaildMove(const glm::ivec2 &position);
    const std::size_t HalfColNumber = DUNGEON_COL_NUMBER / 2;
    const std::size_t HalfRowNumber = DUNGEON_ROW_NUMBER / 2;
    std::unique_ptr<Level> m_Level;
    glm::ivec2 m_Size;
    std::shared_ptr<MapData> m_MapData; // Use map index to store MapDate
    std::shared_ptr<Player> m_MainCharacter;
};

} // namespace Dungeon
#endif // MAP_H
