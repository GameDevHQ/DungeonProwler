#include <cmath>
#include "PCH.h"
#include "Entity.h"

// Default constructor.
Entity::Entity() :
m_currentTextureIndex(static_cast<int>(ANIMATION_STATE::WALK_DOWN)),
m_health(0),
m_maxHealth(0),
m_mana(0),
m_maxMana(0),
m_attack(0),
m_defense(0),
m_strength(0),
m_dexterity(0),
m_stamina(0),
m_speed(0),
m_velocity({0.f, 0.f})
{
}

// Override the default Object::Update function.
void Entity::Update(float timeDelta)
{
	// Choose animation state.
	ANIMATION_STATE animState = static_cast<ANIMATION_STATE>(m_currentTextureIndex);

	if ((m_velocity.x != 0) || (m_velocity.y != 0))
	{
		if (std::abs(m_velocity.x) > std::abs(m_velocity.y))
		{
			if (m_velocity.x <= 0)
			{
				animState = ANIMATION_STATE::WALK_LEFT;
			}
			else
			{
				animState = ANIMATION_STATE::WALK_RIGHT;
			}
		}
		else
		{
			if (m_velocity.y <= 0)
			{
				animState = ANIMATION_STATE::WALK_UP;
			}
			else
			{
				animState = ANIMATION_STATE::WALK_DOWN;
			}
		}
	}

	// Set animation speed.
	if ((m_velocity.x == 0) && (m_velocity.y == 0))
	{
		// The character is still.
		if (IsAnimated())
		{
			// Update sprite to idle version.
			m_currentTextureIndex += 4;

			// Stop movement animations.
			SetAnimated(false);
		}
	}
	else
	{
		// The character is moving.
		if (!IsAnimated())
		{
			// Update sprite to walking version.
			m_currentTextureIndex -= 4;

			// Start movement animations.
			SetAnimated(true);
		}
	}

	// Set the sprite.
	if (m_currentTextureIndex != static_cast<int>(animState))
	{
		m_currentTextureIndex = static_cast<int>(animState);
		m_sprite.setTexture(TextureManager::GetTexture(m_textureIDs[m_currentTextureIndex]));
	}
}

// Gets the entities health.
int Entity::GetHealth() const
{
	return m_health;
}

// Gets the entities max health.
int Entity::GetMaxHealth() const
{
	return m_maxHealth;
}

// Gets the entities attack.
int Entity::GetAttack() const
{
	return m_attack;
}

// Gets the entities defense.
int Entity::GetDefense() const
{
	return m_defense;
}

// Gets the entities strength.
int Entity::GetStrength() const
{
	return m_strength;
}

// Gets the entities dexterity.
int Entity::GetDexterity() const
{
	return m_dexterity;
}

// Gets the entities stamina.
int Entity::GetStamina() const
{
	return m_stamina;
}

// Sets the entities attack stat.
void Entity::SetAttack(int attackValue)
{
	m_attack = attackValue;
}

// Sets the entities defense stat.
void Entity::SetDefense(int defenseValue)
{
	m_defense = defenseValue;
}

// Sets the entities strength stat.
void Entity::SetStrength(int strengthValue)
{
	m_strength = strengthValue;
}

// Sets the entities dexterity stat.
void Entity::SetDexterity(int dexterityValue)
{
	m_dexterity = dexterityValue;
}

// Sets the entities stamina stat.
void Entity::SetStamina(int staminaValue)
{
	m_stamina = staminaValue;
}


// Checks is the given movement will result in a collision.
bool Entity::CausesCollision(sf::Vector2f movement, Level& level)
{
    // Get the tiles that the four corners other player are overlapping with.
    Tile* overlappingTiles[4];
    sf::Vector2f newPosition = m_position + movement;

    // Top left.
    overlappingTiles[0] = level.GetTile(sf::Vector2f(newPosition.x - 14.f, newPosition.y - 14.f));

    // Top right.
    overlappingTiles[1] = level.GetTile(sf::Vector2f(newPosition.x + 14.f, newPosition.y - 14.f));

    // Bottom left.
    overlappingTiles[2] = level.GetTile(sf::Vector2f(newPosition.x - 14.f, newPosition.y + 14.f));

    // Bottom right.
    overlappingTiles[3] = level.GetTile(sf::Vector2f(newPosition.x + 14.f, newPosition.y + 14.f));

    // If any of the overlapping tiles are solid there was a collision.
    for (int i = 0; i < 4; i++)
    {
        if (level.IsSolid(overlappingTiles[i]->columnIndex, overlappingTiles[i]->rowIndex))
            return true;
    }

    // If we've not returned yet no collisions were found.
    return false;
}