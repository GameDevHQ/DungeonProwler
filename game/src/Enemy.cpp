#include <cmath>
#include "PCH.h"
#include "Enemy.h"


/*
 * TODO: Добавить столкновение со стенками для врагов как у игрока (см. CausesCollision)
 * TODO: При рассчете A* просчитать дистанцию Манхеттена между игроков и врагом. Если больше порога
 *       некоторого, то останавливаем поиск + сбрасываем анимацию
 */

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


// Overrides the default Update function of Entity.
void Enemy::Update(float timeDelta, Level &level)
{
    sf::Vector2f previousPosition = m_position;

    // Move towards current target location.
    if (!m_targetPositions.empty())
    {
        sf::Vector2f targetLocation = m_targetPositions.front();
        m_velocity = sf::Vector2f(targetLocation.x - m_position.x, targetLocation.y - m_position.y);

        if (std::abs(m_velocity.x) < 10.f && std::abs(m_velocity.y) < 10.f)
        {
            m_targetPositions.erase(m_targetPositions.begin());
        }
        else
        {
            float length = std::sqrt(m_velocity.x * m_velocity.x + m_velocity.y * m_velocity.y);

            // Calculate horizontal movement.
            if (CausesCollision(sf::Vector2f(m_velocity.x, 0.0f), level))
            {
                m_position.x = previousPosition.x;
            }
            else
            {
                m_velocity.x /= length;
                m_position.x += m_velocity.x * (m_speed * timeDelta);
            }

            // Calculate horizontal movement.
            if (CausesCollision(sf::Vector2f(0.0f, m_velocity.y), level))
            {
                m_position.y = previousPosition.y;
            }
            else
            {
                m_velocity.y /= length;
                m_position.y += m_velocity.y * (m_speed * timeDelta);
            }

            m_sprite.setPosition(m_position);
        }
    }

    Entity::Update(timeDelta);
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


// Updates the target position of the enemy.
void Enemy::UpdatePathfinding(Level &level, sf::Vector2f playerPosition)
{
    // Reset all nodes.
    level.ResetNodes();

    // Store the start and goal nodes.
    Tile* startNode = level.GetTile(m_position);
    Tile* goalNode = level.GetTile(playerPosition);

    // Check we have a valid path to find. If not we can just end the
    // function as there's no path to find.
    if (startNode == goalNode)
    {
        m_targetPositions.clear();
        return;
    }

    // Step 1: Calculate the Manhattan distance for each tile on the level.
    for (int i = 0; i < level.GetSize().x; i++)
    {
        for (int j = 0; j < level.GetSize().y; j++)
        {
            Tile* node = level.GetTile(i, j);
            int heightOffset = std::abs(node->rowIndex - goalNode->rowIndex);
            int widthOffset = std::abs(node->columnIndex - goalNode->columnIndex);
            node->H = heightOffset + widthOffset;
        }
    }

    std::vector<Tile*> openList;
    std::vector<Tile*> closedList;
    std::vector<Tile*> pathList;
    std::vector<Tile*>::iterator position;
    Tile* currentNode = nullptr;

    openList.push_back(startNode);
    while(!openList.empty())
    {
        // Step 2: Find the node in the open list with the lowest F value and mark it as current.
        int lowestF = INT_MAX;
        for (Tile* tile: openList)
        {
            if (tile->F < lowestF)
            {
                lowestF = tile->F;
                currentNode = tile;
            }
        }

        // Remove the current node from the open list and add it to the closed list.
        position = std::find(openList.begin(), openList.end(), currentNode);
        if (position != openList.end()) openList.erase(position);
        closedList.push_back(currentNode);

        // Step 3: Find all adjacent tiles
        std::vector<Tile*> adjacentTiles;
        Tile* node;

        for (int i = -1; i <= 1; i++)
        {
            for (int j = -1; j <= 1; j++)
            {
                node = level.GetTile(currentNode->columnIndex + i, currentNode->rowIndex + j);
                if ((node != nullptr) && (level.IsFloor(*node)) && (node != currentNode))
                {
                    adjacentTiles.push_back(node);
                }
            }
        }

        // For all adjacent nodes.
        for (Tile* adjacentNode: adjacentTiles)
        {
            if (adjacentNode == goalNode)
            {
                // Parent the goal node to current.
                adjacentNode->parentNode = currentNode;

                // Store the current path.
                while (adjacentNode->parentNode != nullptr)
                {
                    pathList.push_back(adjacentNode);
                    adjacentNode = adjacentNode->parentNode;
                }

                // Empty the open list and break out of our for loop.
                openList.clear();
                break;
            }
            else
            {
                // If the node is not in the closed list.
                position = std::find(closedList.begin(), closedList.end(), adjacentNode);
                if (position == closedList.end())
                {
                    // If the node is not in the open list.
                    position = std::find(openList.begin(), openList.end(), adjacentNode);
                    if (position == openList.end())
                    {
                        // Add the node to the open list.
                        openList.push_back(adjacentNode);

                        // Set the parent of the node to the current node.
                        adjacentNode->parentNode = currentNode;

                        // Calculate G (total movement cost so far) cost.
                        adjacentNode->G = currentNode->G + ENEMY_PATHFINDING_STEP_COST;

                        // Calculate the F (total movement cost + heuristic) cost.
                        adjacentNode->F = adjacentNode->G + adjacentNode->H;
                    }
                    else
                    {
                        // Check if this path is quicker that the other.
                        int tempG = currentNode->G + ENEMY_PATHFINDING_STEP_COST;

                        // Check if tempG is faster than the other. I.e, whether it's
                        // faster to go A->C->B that A->C.
                        if (tempG < adjacentNode->G)
                        {
                            // Re-parent node to this one.
                            adjacentNode->parentNode = currentNode;
                        }
                    }
                }
            }
        }
    }

    // Clear the vector of target positions.
    m_targetPositions.clear();

    // Store the node locations as the enemies target locations.
    for (Tile* tile : pathList)
    {
        m_targetPositions.push_back(level.GetActualTileLocation(tile->columnIndex, tile->rowIndex));
    }

    // Reverse the target position as we read them from goal to origin and we need them the other way around.
    std::reverse(m_targetPositions.begin(), m_targetPositions.end());
}
