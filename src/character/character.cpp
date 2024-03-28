#include "character.h"

Character::Character()
{
}

void Character::update(const float &time, const std::vector<std::vector<int>>& location)
{
   rect.left += dx * time;
   CollisionX(location);
   if(!onGround) dy = dy + 0.005*time ;
   rect.top += dy * time;
   onGround = false;
   CollisionY(location);
   rectangle.setPosition(rect.left,rect.top);
   dx = 0;
}

void Character::setDirection(int _direction)
{
   direction = _direction;
}

void Character::setDx(float _dx)
{
   dx = _dx;
}

void Character::setDy(float _dy)
{
   dy = _dy;
}

void Character::setCharacterHeight(int _CharacterHeight)
{
   characterHeight = _CharacterHeight;
}

void Character::setCharacterWidth(int _CharacterWidth)
{
   characterWidth = _CharacterWidth;
}

bool Character::isOnGround()
{
   return onGround;
}

sf::RectangleShape Character::getRectangle()
{
   return rectangle;
}

hlth::Health Character::getHealth()
{
   return health;
}

sf::FloatRect Character::getRect()
{
   return rect;
}

void Character::CollisionX(const std::vector<std::vector<int>>& location)
{
   for (int i = rect.top / 32; i < (rect.top + rect.height) / 32; i++)
      for (int j = rect.left / 32; j < (rect.left + rect.width) / 32; j++)
         if (location[i][j] == 1)
            if (dx > 0)
               rect.left = j * 32 - rect.width;
            else if (dx < 0)
               rect.left = j * 32 + 32;
}


void Character::CollisionY(const std::vector<std::vector<int>>& location)
{
   for (int i = rect.top / 32; i < (rect.top + rect.height) / 32; i++)
      for (int j = rect.left / 32; j < (rect.left + rect.width) / 32; j++)
         if (location[i][j] == 1)
            if (dy > 0)
            {
               rect.top = i * 32 - rect.height;
               dy = 0;
               onGround = true;
            }
            else if (dy < 0)
            {
               rect.top = i * 32 + 32;
               dy = 0;
            }
}
