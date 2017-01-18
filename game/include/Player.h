//-------------------------------------------------------------------------------------
// Player.h
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Written by Dale Green. Copyright (c) Packt Publishing. All rights reserved.
//-------------------------------------------------------------------------------------
#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "Input.h"
#include "Level.h"
#include "Projectile.h"

/**
 * The number of traits that the player can have.
 */
static const int PLAYER_TRAIT_COUNT = 2;
static const int PLAYER_MAX_DAMAGE = 25;
static const float PLAYER_DEXTERITY_DAMAGE_SCALE = 0.075f;
static const float PLAYER_ATTACK_DAMAGE_SCALE = 0.1f;
static const float PLAYER_TAKEN_DAMAGE_REDUCTION_SCALE = 0.05f;


class Player : public Entity
{
public:
    /**
     * Default constructor.
     */
    Player();

    /**
     * Updates the player object.
     * The main purpose of this function is to update the players position.
     * @param timeDelta The time, in MS, since the last game tick.
     * @param level A reference to the level object.
     */
    void Update(float timeDelta, Level& level);

    /**
    * Gets the player's mana.
    * @return The player's mana.
    */
    int GetMana() const;

    /**
    * Gets the player's max mana.
    * @return The player's max mana.
    */
    int GetMaxMana() const;

    /**
     * Set the player's health.
     * @param healthValue The player's new health.
     */
    void SetHealth(int healthValue);

    /**
     * Set the player's mana level.
     * @param mana The new mana value.
     */
    void SetMana(int manaValue);

    /**
     * Gets the player's aim sprite.
     * return The player's aim sprite.
     */
    sf::Sprite& GetAimSprite();

    /**
     * Checks if the player is currently attacking.
     * @return True if the player is attacking.
     */
    bool IsAttacking();

    /**
     * Checks if the player can take damage.
     * @return True if the player can take damage.
     */
    bool CanTakeDamage();

    /**
     * Apply the given amount of damage to the player.
     * @param damage The amount of damage to deal to the player.
     */
    void Damage(int damage);

    /**
     * Get an actual player's class.
     * @return The player's class.
     */
    PLAYER_CLASS GetClass() const;

    /**
     * Get the number of traits the player has.
     * @return The number of traits the player has.
     */
    int GetTraitCount();

    /**
    * Gets the players current traits.
    * @return The players two current traits.
    */
    PLAYER_TRAIT* GetTraits();

    /**
     * Calculate an amount of damage to an enemy.
     * @return Dealt damage to an enemy.
     */
    int CalculateDamage();
private:

    /**
     * Checks if the given movement will result in a collision.
     * @param movement The movement to check.
     * @param level A reference to the level object.
     * @return True if the given movement will result in a collision.
     */
    bool CausesCollision(sf::Vector2f movement, Level& level);

    /**
     * Chooses PLAYER_TRAIT_COUNT random traits for the character.
     */
    void SetRandomTraits();
private:

    /**
     * The sprite for the player's aim cross hair.
     */
    sf::Sprite m_aimSprite;

    /**
     * The time since the player's last attack.
     */
    float m_attackDelta;

    /**
     * The time since the player last took damage.
     */
    float m_damageDelta;

    /**
     * The time since the last mana regeneration.
     */
    float m_manaDelta;

    /**
     * Is the player attacking.
     */
    bool m_isAttacking;

    /**
     * Can the player take damage.
     */
    bool m_canTakeDamage;

    /**
     * Count of stat points for the player.
     */
    int m_statPoints;

    /**
     * The player's class.
     */
    PLAYER_CLASS m_class;

    /**
     * An array containing the character's traits.
     */
    PLAYER_TRAIT m_traits[PLAYER_TRAIT_COUNT];
};
#endif