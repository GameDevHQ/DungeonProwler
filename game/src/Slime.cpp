#include "PCH.h"
#include "Slime.h"

// Default constructor.
Slime::Slime()
{
    // Load textures.
    m_textureIDs[static_cast<int>(ANIMATION_STATE::WALK_UP)] = TextureManager::AddTexture("../resources/enemies/slime/spr_slime_walk_up.png");
    m_textureIDs[static_cast<int>(ANIMATION_STATE::WALK_DOWN)] = TextureManager::AddTexture("../resources/enemies/slime/spr_slime_walk_down.png");
    m_textureIDs[static_cast<int>(ANIMATION_STATE::WALK_RIGHT)] = TextureManager::AddTexture("../resources/enemies/slime/spr_slime_walk_right.png");
    m_textureIDs[static_cast<int>(ANIMATION_STATE::WALK_LEFT)] = TextureManager::AddTexture("../resources/enemies/slime/spr_slime_walk_left.png");
    m_textureIDs[static_cast<int>(ANIMATION_STATE::IDLE_UP)] = TextureManager::AddTexture("../resources/enemies/slime/spr_slime_idle_up.png");
    m_textureIDs[static_cast<int>(ANIMATION_STATE::IDLE_DOWN)] = TextureManager::AddTexture("../resources/enemies/slime/spr_slime_idle_down.png");
    m_textureIDs[static_cast<int>(ANIMATION_STATE::IDLE_RIGHT)] = TextureManager::AddTexture("../resources/enemies/slime/spr_slime_idle_right.png");
    m_textureIDs[static_cast<int>(ANIMATION_STATE::IDLE_LEFT)] = TextureManager::AddTexture("../resources/enemies/slime/spr_slime_idle_left.png");

    // Set initial sprite.
    SetSprite(TextureManager::GetTexture(m_textureIDs[static_cast<int>(ANIMATION_STATE::WALK_DOWN)]), false, 8, 12);

    // Set a random color for the slime sprite.
    sf::Uint8 r, g, b, a;
    r = static_cast<sf::Uint8>(std::rand() % 256);
    g = static_cast<sf::Uint8>(std::rand() % 256);
    b = static_cast<sf::Uint8>(std::rand() % 256);
    a = static_cast<sf::Uint8>((std::rand() % 156) + 100);

    sf::Color color(r, g, b, a);
    m_sprite.setColor(color);
}