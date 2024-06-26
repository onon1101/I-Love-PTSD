#include "Dungeon/Tile.h"
#include <memory>

#include "Settings/SpriteSheet.hpp"
#include "Settings/Window.hpp"
#include "ToolBoxs.h"

namespace Dungeon {

Tile::Tile(const s_Tile& u_Tile)
    : m_Tile(u_Tile) {
    if (u_Tile.type >= 1e6) {
        m_Filepath = (ASSETS_DIR "/items/")
                     + (DUNGEON_TOOLTYPE.find(u_Tile.type)->second) + (".png");
    } else {
        m_Filepath = (ASSETS_DIR "/level/") + DUNGEON_TILETYPES.at(m_Tile.type)
                     + ".png";
    }
    Initialize();
}

Tile::Tile(const s_Tile& u_Tile, const std::string& filepath)
    : m_Tile(u_Tile),
      m_Filepath(filepath) {
    Initialize();
}

void Tile::Initialize() {
    m_ZIndex = m_Tile.y;
    m_SpriteSheet = std::make_shared<Util::SpriteSheet>(m_Filepath);

    if (m_Tile.type >= 1e6) {
        m_TileSize = DUNGEON_TOOLSIZES.find(m_Tile.type)->second;
    } else {
        m_TileSize = DUNGEON_TILESIZES.at(m_Tile.type);
    }
    m_ImgSize =
        ToolBoxs::CountImagePixel(m_Filepath, m_TileSize.x, m_TileSize.y);
    m_Drawable = m_SpriteSheet;
    m_SpriteSheet->SetColorMod({0, 0, 0, 255});
    SetTorch(m_Tile.torch == 1);
}

void Tile::SetIndex(std::size_t index) {
    m_Index = index;
    UpdateDrawable();
}

void Tile::SetCloseDisplayB24(bool closeDisplayb24) {
    if (IsWall()) {
        m_CloseDisplayb24 = closeDisplayb24;
    } else {
        LOG_ERROR("Only wall type can be closeDisplayb24");
    }

    UpdateDrawable();
}

void Tile::SetRotation(float rotation) {
    m_Transform.rotation = rotation;
}

void Tile::SetOverlay(bool visible) {
    if (!m_Seen) {
        if (!visible) {
            m_Seen = !visible;
        } else {
            return;
        }
    }
    if (GetOverlay() == visible) {
        return;
    }
    m_IsOverlay = visible;
    SDL_Color color =
        (visible == true ? SDL_Color({100, 100, 100, 255})
                         : SDL_Color({255, 255, 255, 255}));
    m_SpriteSheet->SetColorMod(color);
    if (m_Torch) {
        m_TorchAnimation->SetColorMod(color);
    }
}
std::size_t Tile::GetIndex() {
    return m_Index;
}

s_Tile Tile::GetTile() {
    return m_Tile;
}

bool Tile::GetOverlay() {
    return m_IsOverlay;
}

void Tile::UpdateScale() {
    m_Transform.scale = {DUNGEON_SCALE, DUNGEON_SCALE};
}

void Tile::UpdateTranslation() {
    m_Transform.translation = {
      (m_Tile.x * DUNGEON_TILE_WIDTH * DUNGEON_SCALE),
      -DUNGEON_TILE_WIDTH - (m_Tile.y * DUNGEON_TILE_WIDTH * DUNGEON_SCALE)
          + (m_MagicNumber / 2.0 * DUNGEON_SCALE)};
}

void Tile::UpdateDrawable() {
    UpdateScale();
    UpdateTranslation();

    if (m_ImgSize.x > DUNGEON_TILE_WIDTH) {
        m_SpriteSheet->SetDrawRect(
            {static_cast<int>(
                 m_ImgSize.x * (m_Index % static_cast<int>(m_TileSize.x))
                 + (m_ImgSize.x - DUNGEON_TILE_WIDTH) / 2
             ),
             static_cast<int>(
                 m_ImgSize.y * static_cast<int>(m_Index / m_TileSize.x)
                 + (m_ImgSize.y - DUNGEON_TILE_WIDTH) / 2
             ),
             static_cast<int>(DUNGEON_TILE_WIDTH),
             static_cast<int>(DUNGEON_TILE_WIDTH - m_OffSetY)}
        );
    } else {
        m_SpriteSheet->SetDrawRect(
            {static_cast<int>(
                 m_ImgSize.x * (m_Index % static_cast<int>(m_TileSize.x))
                 + (m_ImgSize.x - DUNGEON_TILE_WIDTH) / 2
             ),
             static_cast<int>(
                 m_ImgSize.y * static_cast<int>(m_Index / m_TileSize.x)
             ),
             static_cast<int>(DUNGEON_TILE_WIDTH),
             static_cast<int>(m_ImgSize.y - m_OffSetY)}
        );
    }
    m_Drawable = m_SpriteSheet;
}

bool Tile::GetSeen() const {
    return m_Seen;
}

void Tile::SetCameraUpdate(bool cameraUpdate) {
    SetVisible(cameraUpdate);
    for (auto& child : m_Children) {
        child->SetVisible(cameraUpdate);
    }
}

void Tile::SetTorch(bool torch) {
    if (!torch) {
        if (m_Torch) {
            RemoveChild(m_Torch);
            m_Torch.reset();
        }
        return;
    }
    m_TorchAnimation = std::make_shared<SpriteSheet>(
        ASSETS_DIR "/level/wall_torch.png",
        glm::vec2(12, 26),
        std::vector<std::size_t>{0, 1, 2, 3},
        true,
        100,
        true,
        100
    );
    m_TorchAnimation->SetColorMod({0, 0, 0, 255});
    m_Torch = std::make_shared<GameObject>(m_TorchAnimation, m_ZIndex + 0.1f);
    m_Torch->m_Transform.scale = {DUNGEON_SCALE, DUNGEON_SCALE};
    m_Torch->m_Transform.translation = ToolBoxs::GamePostoPos(
        {m_Tile.x, m_Tile.y}
    );
    m_Torch->m_Transform.translation.y += DUNGEON_TILE_WIDTH * DUNGEON_SCALE
                                          / 2;
    m_Torch->SetVisible(false);
    AddChild(m_Torch);
}

}  // namespace Dungeon
