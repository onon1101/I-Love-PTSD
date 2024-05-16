#include "Player.h"
#include <memory>

Player::Player()
    : m_Body(std::make_shared<GameElement>()),
      m_Head(std::make_shared<GameElement>()),
      m_Player(std::make_shared<GameElement>()),
      m_Coin(std::make_unique<Coin>()),
      m_Heart(std::make_unique<Heart>()),
      m_Tool(std::make_shared<Players::Tools>()),
      m_Diamond(std::make_unique<Diamond>()),
      m_SwipeModule(std::make_unique<Game::Warehouse::SwipeModule>()),
      m_Window(std::make_shared<GameElement>()) {
    // init Animation
    m_Animation = std::make_unique<Animation>(m_Position);
    m_SwipeModule->AddSwipe("Arrow");

    Update();
}

void Player::SetBodyImage(const std::string& path) {
    BodySize = ToolBoxs::CountImagePixel(path, 4, 10);
    BodyImage = std::make_shared<SpriteSheet>(
        path,
        BodySize,
        std::vector<std::size_t>{0, 1, 2, 3},
        true,
        100,
        true,
        100
    );
    m_Body->SetDrawable(BodyImage);
    m_Body->SetPosition(m_Position);
    m_Body->SetScale({DUNGEON_SCALE, DUNGEON_SCALE});
}

void Player::SetHeadImage(const std::string& path) {
    HeadSize = ToolBoxs::CountImagePixel(path, 4, 2);
    HeadImage = std::make_shared<SpriteSheet>(
        path,
        HeadSize,
        std::vector<std::size_t>{0, 1, 2, 3},
        true,
        100,
        true,
        100
    );
    m_Head->SetDrawable(HeadImage);
    m_Head->SetPosition(m_Position);
    m_Head->SetScale({DUNGEON_SCALE, DUNGEON_SCALE});
}

void Player::SetHeadImage(std::shared_ptr<SpriteSheet> image) {
    m_Head->SetDrawable(image);
    m_Head->SetPosition(m_Position);
    m_Head->SetScale({DUNGEON_SCALE, DUNGEON_SCALE});
}

void Player::SetBodyImage(std::shared_ptr<SpriteSheet> image) {
    m_Body->SetDrawable(image);
    m_Body->SetPosition(m_Position);
    m_Body->SetScale({DUNGEON_SCALE, DUNGEON_SCALE});
}

std::shared_ptr<GameElement> Player::GetGameElement() {
    m_Player->AddChild(m_Body);
    m_Player->AddChild(m_Head);

    m_Player->SetVisible(false);
    return m_Player;
}

glm::vec2 Player::GetGamePosition() const {
    return m_GamePosition;
}

glm::vec2 Player::GetTranslation() const {
    return m_Position;
}

void Player::SetGamePosition(const glm::vec2& gamePosition) {
    m_GamePosition = gamePosition;
    m_Animation->UpdateGamePosition(gamePosition);
    SetPosition(ToolBoxs::GamePostoPos(gamePosition));
}

void Player::SetVisible(bool status) {
    m_Body->SetVisible(status);
    m_Head->SetVisible(status);
}

void Player::SetFaceTo(Direction direction) {
    m_Direction = direction;
    if (direction != RIGHT && direction != LEFT) {
        // LOG_WARN("Player::SetFaceTo: Invalid direction");
        return;
    }
    if (direction == RIGHT) {
        m_BeforeFaceTo = RIGHT;
        m_Body->SetScale({DUNGEON_SCALE, DUNGEON_SCALE});
        m_Head->SetScale({DUNGEON_SCALE, DUNGEON_SCALE});
        return;
    }
    m_BeforeFaceTo = LEFT;
    m_Body->SetScale({-DUNGEON_SCALE, DUNGEON_SCALE});
    m_Head->SetScale({-DUNGEON_SCALE, DUNGEON_SCALE});
}

void Player::Update() {
    m_Animation->UpdateAnimation(true);
    if (m_Animation->IsAnimating()) {
        m_Position = m_Animation->GetAnimationPosition();
    }
    SetZIndex(m_Animation->GetAnimationZIndex());
    SetPosition(m_Position);
    m_SwipeModule->Update();
}

void Player::SetPosition(const glm::vec2& position) {
    m_Position = position;
    m_Body->SetPosition(m_Position);
    m_Head->SetPosition(m_Position);
}

void Player::SetZIndex(float index) {
    m_ZIndex = index;
    m_Body->SetZIndex(index);
    m_Head->SetZIndex(index + float(0.25));
}

void Player::UpdateCoin(
    const unsigned long duringTimeMs,
    const glm::vec2&    destination,
    const uint16_t      direction
) {
    m_Coin->MoveByTime(duringTimeMs, destination, direction);
}

std::shared_ptr<GameElement> Player::GetWindowElement() {
    m_Window->AddChild(m_Coin->GetGameObject());
    m_Window->AddChild(m_Heart->GetGameObject());
    m_Window->AddChild(m_Diamond->GetGameObject());
    m_Window->AddChild(m_Tool->GetGameObject());
    m_Window->SetVisible(false);
    return m_Window;
}

Player::Direction Player::GetFaceTo() const {
    return m_BeforeFaceTo;
}

Player::Direction Player::GetDirection() const {
    return m_Direction;
}

float Player::GetZIndex() const {
    return m_ZIndex;
}

void Player::gainCoin(std::size_t number) {
    m_Coin->plusCoinNumber(number);
}

void Player::lostCoin(std::size_t number) {
    m_Coin->plusCoinNumber(number * -1);
}

void Player::gainDiamond(std::size_t number) {
    m_Diamond->plusDiamondNumber(number);
}

void Player::lostDiamond(std::size_t number) {
    m_Diamond->plusDiamondNumber(number * -1);
}

std::size_t Player::GetHealth() const {
    return m_Heart->GetHealth();
}

void Player::lostHP(std::size_t value) {
    m_Heart->minusHP(value);
}

void Player::gainHeart(std::size_t value) {
    m_Heart->gainHeart(value);
}

std::shared_ptr<Players::Tools> Player::GetToolMod() {
    return m_Tool;
}

// void Player::useDefaultSettingsTool() {
//     m_Tools->SetShovelType();
// }

// bool Player::IsShovelExist() {
//     return true;
// }

// bool Player::IsWeaponExist() {
//     return true;
// }

// ShovelEnum::Type Player::GetShovelType() {
//     return m_ShovelType;
// }

// WeaponEnum::Type Player::GetWeaponType() {
//     return m_WeaponType;
// }

void Player::PrepareThrowOut(bool state) {
    // m_Tools->PrepareThrowOut(state);
    return;
}

void Player::MoveByTime(
    const unsigned long duringTimeMs,
    const glm::vec2&    destination,
    const uint16_t      direction
) {
    // Update GamePosition but not draw
    m_BeforeGamePosition = m_GamePosition;
    m_GamePosition = ToolBoxs::PosToGamePos(destination);
    SetFaceTo(static_cast<Direction>(direction));
    m_Animation->MoveByTime(duringTimeMs, destination, direction);
}

void Player::RevertAnimation() {
    m_Animation->SetAnimationStop();
    m_Animation->UpdateGamePosition(m_BeforeGamePosition);
}
