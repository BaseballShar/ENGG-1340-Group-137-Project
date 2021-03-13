#include "character.h"
    
// Input: Basic status and career of the player
// Purpose: This function is to initialize the status of the player
void Player::SetStatus(long long hp_basic, long long str_basic, 
                long long def_basic, long long agi_basic, string career) {   
  this -> hp_basic = hp_basic;
  this -> str_basic = str_basic;
  this -> def_basic = def_basic;
  this -> agi_basic = agi_basic;
  this -> career = career;
}

// Purpose: This function is to print the status of the player
void Player::PrintStatus() {
  cout << name << " HP: " << hp_actual << " STR: " << str_actual 
  << " DEF: " << def_actual << " AGI: " << agi_actual << endl;
}

// Purpose: Printing out the monster status
void Monster::PrintStatus() {
  cout << name << " HP: " << hp << " STR: " << str << " DEF: " 
  << def << " AGI: " << agi << endl;
}
