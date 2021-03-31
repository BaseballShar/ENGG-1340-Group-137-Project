// ENGG 1340 Group 137 Project
//
// Developer: Chan Tsz Ho  (3035785738)
//            Chan Yuk Yin (3035786574)
//
// Description: This is a text-based role-playing game which is set in 
// a dark medieval fantasy world. You the player will act as an adventurer 
// in the game. By acquiring strength and powerful equipment through combating
// monsters spread throughout the world, player will eventually be able to 
// fight the Monster King and save mankind to win the game.

#include <iostream>
#include <fstream>
#include <cmath>
#include <string>

#include "combat.h"
#include "character.h"
#include "skill_points.h"
using namespace std;

// Purpose: Print out a line of user specified symbol and length
void Line(char symbol, int noOfSym = 75) {   
  string output;
  for (int i = 0; i < noOfSym; i++) {
    output.push_back(symbol) ;
  }
  cout << output << endl ;
}

// Purpose: Print out the game story
void PrintStory() {
  string story = "You were a hardworking programmer in an international IT\n"
  "company,you had contributed to the company with all your heart and soul.\n"
  "However, you recently discovered that your boss had been stealing your idea\n"
  "and presenting it to the central which brought him wealth and fame.\n"
  "You were so outraged that you grabbed a keyboard nearby and smashed it\n"
  "against your boss.\n\n"
  "Not knowing why you missed it!\n"
  "The keyboard crashed onto the monitor and the electrical wires inside\n"
  "were in contact with your hand. It was too late to retract your hands.\n"
  "Suddenly, a blue portal emerged near the desk and you were teleported to\n"
  "a strange new world.\n\n"   
  "And now! You are destinated to be the hero of this world!\n"
  "Fight the three most horrible Monsters to take their maps!\n"
  "The maps lead you to fight the King Of Boss \"Infinite Comments Client\"!\n"
  "The world needs your power!\n";
  cout << story << endl;
}

// Purpose: For checking whether the player has played the game before
bool IsOldPlayer() {   
  int has_played;

  cout << "Have you played this game before ?" << endl;
  cout << "[1]Have not    [2]Have" << endl;
  cout << "Enter the number in brackets to select the action: ";
  cin >> has_played ;

  switch(has_played) {
    case 1:
      return false;

    case 2:
      return true;

    default:
      return false;
  }   
}

// Purpose: For saving the game
void SaveGame(Player player) {
  ofstream file("rpg_save");
  file << player.name;
  file << "\n";
  file << player.career;
  file << "\n";
  file << player.hp_basic;
  file << "\n";
  file << player.str_basic;
  file << "\n";
  file << player.def_basic;
  file << "\n";
  file << player.agi_basic;
  file << "\n";
  file << player.level;
  file << "\n";
  file << player.exp;
  file << "\n";
  file << player.skill_pt;
  file << "\n";
  file << player.money;
  file << "\n";
}

// Input: Player object for storing the retrieved data from file
// Purpose: Loading the saved progress of previous game
void LoadGame(Player &player) {
  ifstream file("rpg_save");
  file >> player.name;
  file >> player.career;
  file >> player.hp_basic;
  file >> player.str_basic;
  file >> player.def_basic;
  file >> player.agi_basic;
  file >> player.level;
  file >> player.exp;
  file >> player.skill_pt;
  file >> player.money;
}

// Input: Player object for recording the name of the player
// Purpose: Function to get the name of the player
void GetName(Player &player) {   
  string name;

  cout << "What is your name adventurer ? ";
  getline(cin, name);
  getline(cin, name);
  cout << "Welcome " << name << endl;
  player.name = name;
}

// Purpose: Function to get the career of the player
void GetCareer(int pause_career, Player &player) {   
  // Display avaliable choices
  int career_choice; 
  
  cout << "Here are the list of careers that you can choose from" << endl;
  Pause(pause_career);
  cout << "Adventurer Class: Human with average abilities " << endl;
  Pause(pause_career);
  cout << "Warrior Class: Human with moderately high strength"
  << " and superior defense but low mobility " << endl;
  Pause(pause_career);
  cout << "Assassin Class: Human with strong attack, rapid movement" 
  << " but lack defense " << endl;
  cout << "[1]Adventurer Class ,"
  << " [2]Warrior and [3]Assassin" << endl;
  cin >> career_choice;
    

  // Assign character status
  switch (career_choice) {   
    // hp str def agi career
    case 1:
      player.SetStatus(1000, 100, 100, 100, "Adventurer");
      break;
    case 2:
      player.SetStatus(2000, 150, 200, 50, "Warrior");
      break;
    case 3:
      player.SetStatus(800, 250, 50, 200, "Assassian");
      break;
  }

}

// Purpose: Functions for displaying the welcome message
// If player has played before, saved progress will be loaded
// If player has not played before, new character profile will be created
void DisplayWelcomeMenu(Player &player) {
  cout << "Welcome to Deep Dark Fantasy" << endl;
  
  if (IsOldPlayer()) {
    LoadGame(player);
  } else {  
    PrintStory(); 
    GetName(player);
    GetCareer(500, player); // 500 ms pause
  }
} 

void PrintPlayerDetailStatus(Player player) {
  Line('*');
  cout << "DEEP DARK FANTASY" << endl;
  cout << left;
  cout << setw(30) << "Name: " + player.name  << 
  "HP: " << player.hp_actual << endl;

  cout << setw(30) << "Career: " + player.career 
  << "STR: " << player.str_actual << endl;

  cout << setw(30) << "Level: " + to_string(player.level) + "(" + to_string(player.exp) + "/" 
  + to_string(50 * player.level * player.level) + ")" << "DEF: " 
  << player.def_actual << endl;

  cout << setw(30) << "$" + to_string(player.money) << "AGI: " 
  << player.agi_actual << endl;

  cout << setw(30) << "Map(" + to_string(player.num_map) + "/3)" 
  << "Token: " + to_string(player.num_token) << endl;
  
  Line('-');
  cout << setw(15) << "[1]Fight" << setw(15) << "[2]Shop" <<
  setw(15) << "[3]Skill" << endl;
  cout << setw(15) << "[4]Status" << setw(15) << "[5]Quit" << endl;
  
  player.PrintEquipment();

  Line('*');
}

// Purpose: Function to get the action take by the player
void GetAction(Player &player/*, Shop shop*/) {   
  int action;
  int combat_result;

  PrintPlayerDetailStatus(player);

  cin >> action;
  
  //To determine which action to be taken
  switch(action) {   
    case 1: // Combat
      combat_result = Combat(player/*, shop*/);
      CombatReward(player, combat_result);
      SaveGame(player);
      break;
    /*case 2: // Shop
      shop_access(player , shop);
      SaveGame(player);
      break; */
    case 3: // Skill points assignment
      SkillPoint(player);
      //player_equipment_effect(player, shop);
      SaveGame(player);
      break; 
    /*case 4: // Player status
      player_detail_status(player, shop);
      SaveGame(player);
      break;*/
    case 5:
      player.death = true;
      break;
  }
} 

//// Will be amended later
void PlayerEquipmentEffect (Player &player/*, Shop shop*/) {
  player.hp_actual = player.hp_basic;
  player.str_actual = player.str_basic;
  player.def_actual = player.def_basic;
  player.agi_actual = player.agi_basic;
}

//main function
int main() {
  Player player;

  // Greeting and initializing game character
  DisplayWelcomeMenu(player);

  // Playing session
  while (player.death == false) {   
    PlayerEquipmentEffect(player);
    GetAction(player/*, shop*/);
    if (player.death == false) {
      LevelUpdate(player);
    }
  }
    return 0;
}
