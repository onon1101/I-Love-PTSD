//
// Created by 陳世昂 on 2024/4/26.
//

#include "Helper.hpp"

void Settings::Helper::Init(Dungeon::Map* dungeonMap, Player *player) {
    m_DungeonMap = dungeonMap;
    m_Player = player;
}

std::size_t Settings::Helper::GamePosToMapIdx(glm::ivec2 gamePos) {
    return m_DungeonMap->GamePostion2MapIndex(gamePos);
};

Settings::Helper::PlayerPos Settings::Helper::GetPlayerPosDM() {
    {
        const auto playerPos = m_DungeonMap->GetMapData()->GetPlayerPosition();
        const auto typeChange = static_cast<glm::ivec2>(playerPos);
        const auto mapIdx = GamePosToMapIdx(typeChange);

        return PlayerPos{playerPos, mapIdx};
    };
}

glm::ivec2 Settings::Helper::Direct2MI(Player::Direction direction) {
    switch (direction) {
    case Player::Direction::UP: return {0, -1};
    case Player::Direction::LEFT: return {-1, 0};
    case Player::Direction::DOWN: return {0, 1};
    case Player::Direction::RIGHT: return {1, 0};
    case Player::Direction::NONE:
        throw std::runtime_error("direction can not be none");
    }
}

glm::vec2 Settings::Helper::CountImgPixel(
    const std::string& filePath,
    std::size_t        widthNumber,
    std::size_t        heightNumber
) {
    const auto ImageSize = Util::Image(filePath).GetSize();

    const auto result = glm::vec2(
        ImageSize[0] / static_cast<float>(widthNumber),
        ImageSize[1] / static_cast<float>(heightNumber)
    );

    return result;
}

Players::Config::Direction Settings::Helper::DirectConvert(Player::Direction direct){
    switch(direct) {
    case Player::RIGHT: return Players::Config::Direction::RIGHT;
    case Player::LEFT: return Players::Config::Direction::LEFT;
    case Player::DOWN: return Players::Config::Direction::DOWN;
    case Player::UP: return Players::Config::Direction::UP;
    default: throw std::runtime_error("type convert error");
        }
}

Player::Direction Settings::Helper::DirectConvert(Players::Config::Direction direct){
        switch(direct) {
        case Players::Config::Direction::RIGHT: return Player::RIGHT;
        case Players::Config::Direction::LEFT: return Player::LEFT;
        case Players::Config::Direction::DOWN: return Player::DOWN;
        case Players::Config::Direction::UP: return Player::UP;
        default: throw std::runtime_error("type convert error");
        }
}

glm::ivec2 Settings::Helper::DistancePlayer2Wall(Players::Config::Direction direction) {
    const auto &&playerPos = m_DungeonMap->GetMapData()->GetPlayerPosition();
    const auto&& directionGP = Settings::Helper::Direct2MI(DirectConvert(direction));

    std::size_t posMi = 0;
    auto&& posGP = static_cast<glm::ivec2> (playerPos);

    while(!m_DungeonMap->GetMapData()->IsPositionWall(posGP + directionGP)) {
        posGP += directionGP;
    }
    return posGP;
}


Dungeon::Map* Settings::Helper::m_DungeonMap = nullptr;
Player* Settings::Helper::m_Player = nullptr;
