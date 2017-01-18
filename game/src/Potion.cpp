#include "PCH.h"
#include "Potion.h"

// Default constructor.
Potion::Potion() :
m_attack(0),
m_defense(0),
m_strength(0),
m_dexterity(0),
m_stamina(0)
{
    // The string for the sprite path.
    std::string spriteFilePath;

    // Set the potion type.
    m_potionType = static_cast<POTION>(std::rand() % static_cast<int>(POTION::COUNT));

    // Set stat modifiers, sprite file path, and item name.
    switch (m_potionType)
    {
        case POTION::ATTACK:
            m_dexterity = std::rand() % 5 + 5;
            spriteFilePath = "../resources/loot/potions/spr_potion_attack.png";
            break;
        case POTION::DEFENSE:
            m_dexterity = std::rand() % 5 + 5;
            spriteFilePath = "../resources/loot/potions/spr_potion_defense.png";
            break;
        case POTION::STRENGTH:
            m_strength = std::rand() % 5 + 5;
            spriteFilePath = "../resources/loot/potions/spr_potion_strength.png";
            break;
        case POTION::DEXTERITY:
            m_dexterity = std::rand() % 5 + 5;
            spriteFilePath = "../resources/loot/potions/spr_potion_dexterity.png";
            break;
        case POTION::STAMINA:
            m_stamina = std::rand() % 5 + 5;
            spriteFilePath = "../resources/loot/potions/spr_potion_stamina.png";
            break;
        default:
            m_dexterity = std::rand() % 11 + 5;
            spriteFilePath = "../resources/loot/potions/spr_potion_attack.png";
            break;
    }

    // Load and set sprite.
    SetSprite(TextureManager::GetTexture(TextureManager::AddTexture(spriteFilePath)), false, 8, 12);

    // Set the item type.
    m_type = ITEM::POTION;
}

// Gets the attack value of the potion.
int Potion::GetAttack() const
{
    return m_attack;
}

// Gets the defense value of the potion.
int Potion::GetDefense() const
{
    return m_defense;
}

// Gets the strength value of the potion.
int Potion::GetStrength() const
{
    return m_strength;
}

// Gets the dexterity value of the potion.
int Potion::GetDexterity() const
{
    return m_dexterity;
}

// Gets the stamina value of the potion.
int Potion::GetStamina() const
{
    return m_stamina;
}

// Gets the potion type.
POTION Potion::GetPotionType() const
{
    return m_potionType;
}