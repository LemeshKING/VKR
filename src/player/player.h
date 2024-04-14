#pragma once
#include"../character/character.h"
#include "../Camera/Camera.h"
#include "../Weapon/weapon.h"

class Player : public Character
{
 public: 

   Player();
   void Initialization(int x, int y);
   void update(const float time, std::vector<std::vector<Tile>>& location) override;
   void setCamera(Camera &_camera);
   Camera getCamera();
   void TakeDamage(int damageValue) override;
   bool isImmunity();
   void removeImmunity();
   void setWeapon(weapon *_weapon);
   void BecomeImmune();
   weapon* getWeapon();
   bool satDown = false;
   bool dashing = false;
   int dashFramers = 0;
   int dashColdown = 77;
private:
  
   weapon *Weapon;
   bool immunity = false;
   Camera camera;
   void CollisionX(std::vector<std::vector<Tile>>& location) override;
   void CollisionY(std::vector<std::vector<Tile>>& location) override;
};