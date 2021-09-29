#include "Character.h"

Character::Character(string _name, string _type, int _attack, int _defense, int _remainingHealth, int _nMaxRounds) { //parameterized constructor

	this -> name = _name;
	this -> remainingHealth = _remainingHealth;
	this -> nMaxRounds = _nMaxRounds;
	this -> defense = _defense;
	this -> type = _type;
	this -> attack = _attack;
	this -> healthHistory = new int[_nMaxRounds+1];
	this -> healthHistory[0] = this -> remainingHealth;
	this -> nRoundsSinceSpecial = 0;

}

Character::Character(const Character& character) { // copy constructor

	this -> name = character.name;
	this -> defense = character.defense;
	this -> attack = character.attack;
	this -> remainingHealth = character.remainingHealth;
	this -> nMaxRounds = character.nMaxRounds;
	this -> type = character.type;
	this -> healthHistory = new int[character.nMaxRounds+1];
	this -> healthHistory[0] = this -> remainingHealth;
	this -> nRoundsSinceSpecial = character.nRoundsSinceSpecial;
	this -> isAlive = character.isAlive;
}

Character& Character::operator=(const Character& character) {

	this -> name = character.name;
	this -> defense = character.defense;
	this -> attack = character.attack;
	this -> remainingHealth = character.remainingHealth;
	this -> nMaxRounds = character.nMaxRounds;
	this -> type = character.type;
	delete[] this-> healthHistory;
	this -> healthHistory = new int[character.nMaxRounds+1];
	this -> healthHistory[0] = this -> remainingHealth;
	this -> nRoundsSinceSpecial = character.nRoundsSinceSpecial;
	this -> isAlive = character.isAlive;

	return *this;
}

bool Character::operator<(const Character& other) { // overloading < operator by alphabetic order

	if(this -> name < other.name)
		return true;
	else
		return false;

}

Character::~Character() { // destructor of the class
delete[] this -> healthHistory;
}