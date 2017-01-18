#include "PCH.h"
#include "Enemy.h"

// Default constructor.
Enemy::Enemy()
{
	// Set stats.
	m_health = std::rand() % 41 + 80;
	m_attack = std::rand() % 11 + 6;
	m_defense = std::rand() % 11 + 6;
	m_strength = std::rand() % 11 + 6;
	m_dexterity = std::rand() % 11 + 6;
	m_stamina = std::rand() % 11 + 6;

	// Set speed.
	m_speed = rand() % 51 + 150;
}

// Applies the given amount of damage to the enemy.
void Enemy::Damage(int damage)
{
    int applied_damage = static_cast<int>(damage - (ENEMY_TAKEN_DAMAGE_REDUCTION_SCALE * m_defense));
    m_health -= applied_damage > 0 ? applied_damage : 0;
}

// Checks if the enemy has taken enough damage that they are now dead.
bool Enemy::IsDead()
{
	return (m_health <= 0);
}

// Calculate an amount of damage to an enemy.
int Enemy::CalculateDamage()
{
    float damage_scale(1.f);
    damage_scale += ENEMY_DEXTERITY_DAMAGE_SCALE * m_dexterity;

    float damage = (std::rand() % (ENEMY_MAX_DAMAGE + 1)) + (ENEMY_ATTACK_DAMAGE_SCALE * m_attack);
    return static_cast<int>(damage * damage_scale);
}
