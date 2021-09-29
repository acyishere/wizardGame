#include "Character.h"
#include<bits/stdc++.h>
using namespace std;

int casualties = 0;
string lastDead1,lastDead2;
vector<Character> community1;
vector<Character> c1Sorted;
vector<Character> community2;
vector<Character> c2Sorted;

// Special skills
void elvesSkill(Character &def,Character &hob,Character &elv){ 
	
	Character* elf = &elv;
	Character* hobbit = &hob;
	Character* defender = &def;
	int healing = elv.remainingHealth / 2;
	elf->nRoundsSinceSpecial = -1;
	hobbit->remainingHealth += healing;
	elf->remainingHealth -= healing; 

	if(elv.attack > def.defense){ 
		defender->remainingHealth -= elv.attack - def.defense;
	}
	if(defender->remainingHealth <= 0){
	
		defender->remainingHealth = 0;
		defender->isAlive = false;
		casualties++; 
		for(int a = 0;a<5;a++){
			if(defender->name == community1[a].name){ //lastdead1 değişcek
				lastDead1 = defender->name;
			}
			else if(defender->name == community2[a].name){ //lastdead2 değişcek
				lastDead2 = defender->name;
			}
		}

	}
}
void wizardsSkill(Character &lastd, Character &wiz, Character &def){ 
										
	Character* dead = &lastd;
	Character* wizard = &wiz;
	Character* defender = &def;
	wizard->nRoundsSinceSpecial = -1; // bunu mainde yap çünkü cab fulleyince yapmıycak !

	if(!dead->isAlive){ // ölüyse diriltiyoz

		dead->isAlive = true;
		dead->remainingHealth = dead->healthHistory[0];
		dead->nRoundsSinceSpecial = -1;
		casualties--;
	}
	else{
		dead->remainingHealth = dead->healthHistory[0];
	}
	if(wiz.attack > def.defense){
		defender->remainingHealth -= wiz.attack-def.defense;
	}
	if(defender->remainingHealth <= 0){
		
		defender->remainingHealth = 0;
		defender->isAlive = false;
		casualties++; 
		for(int a = 0;a<5;a++){
			if(defender->name == community1[a].name){ //lastdead1 değişcek
				lastDead1 = defender->name;
			}
			else if(defender->name == community2[a].name){
				lastDead2 = defender->name;
			}
		}
	}
}
void dwarfsSkill(Character &def,Character &dwf){
	
	Character* defender = &def;
	Character* dwarfs = &dwf;
	dwarfs->nRoundsSinceSpecial = -1;

	if(dwf.attack > def.defense){
		defender->remainingHealth -= 2*(dwf.attack-def.defense);
	}
	if(defender->remainingHealth <= 0){
		
		defender->remainingHealth = 0;
		defender->isAlive = false;
		casualties++; 
		for(int a = 0;a<5;a++){
			if(defender->name == community1[a].name){ //lastdead1 değişcek
				lastDead1 = defender->name;
			}
			else if(defender->name == community2[a].name){
				lastDead2 = defender->name;
			}
		}
	}
}

bool isDefeated(vector<Character> &vec)  { // use every round,if hobbit dead defeated, if 4 others dead defeated

	vector<Character> spec;

	int count = 0;
	for(int t = 0;t<5;t++){
		if(vec[t].type == "Hobbit" && !vec[t].isAlive){
			return true;
		}
		if(!vec[t].isAlive)
			count++;
	}

	if(count == 4){ // given community defeated
		return true;
	}
	else{
		return false;
	}
}

Character* whoc(Character &x,vector<Character> &cSorted){ // finds which character is attacker or defender
	if(x.isAlive){
		return &x; // ?
	}
	else { //x is dead find alphabetically who's next.
		int inofx;
		for(int i = 0;i<5;i++){
			if(cSorted[i].name == x.name){
				inofx = i;
			}
		}
		if(inofx == 0){
			for(int i = 1;i<5;i++){
				if(cSorted[i].isAlive){
					return &cSorted[i];
				}
			}
		}
		else if(inofx == 1){
			for(int i = 2;i<5;i++){
				if(cSorted[i].isAlive)
					return &cSorted[i];
			}
			return &cSorted[0];
		}
		else if(inofx == 2){
			for(int i = 3;i<5;i++){
				if(cSorted[i].isAlive)
					return &cSorted[i];
			}
			for(int i = 1;i>=0;i--){
				if(cSorted[i].isAlive)
					return &cSorted[i];
			}
			return &x;
		}
		else if(inofx == 3){
			for(int i = 4;i<5;i++){
				if(cSorted[i].isAlive)
					return &cSorted[i];
			}
			for(int i = 2;i>=0;i--){
				if(cSorted[i].isAlive)
					return &cSorted[i];
			}
			return &x;
		}
		else {
			for(int i = 3;i>=0;i--){
				if(cSorted[i].isAlive)
					return &cSorted[i];
			}
			return &x;
		}
	}
}


int main(int argc, char* argv[]) {

	ifstream readFrom(argv[1]);
	ofstream writeTo(argv[2]);

	int noR; // number of rounds
	readFrom >> noR;
	int realNor = noR;

	// COMMUNITY 1
	string name1,type1;
	int at1,def1,hp1;
	
	for(int i = 0;i<5;i++){

		readFrom >> name1 >> type1 >> at1 >> def1 >> hp1;
		Character toon1 = Character(name1,type1,at1,def1,hp1,noR);
		community1.push_back(toon1);
		c1Sorted.push_back(toon1);
	}
	
	// COMMUNITY 2
	string name2,type2;
	int at2,def2,hp2;

	for(int i = 0;i<5;i++){

		readFrom >> name2 >> type2 >> at2 >> def2 >> hp2;
		Character toon2 = Character(name2,type2,at2,def2,hp2,noR);
		community2.push_back(toon2);
		c2Sorted.push_back(toon2);

	}
	for(int i = 0;i<5;i++)	{
		for(int j = 1;j<5;j++){
			
			if(c1Sorted[j].name<c1Sorted[j-1].name){
				
				Character temp(c1Sorted[j]);				
				c1Sorted[j] = c1Sorted[j-1];
				c1Sorted[j-1]=temp;

			}
			if(c2Sorted[j].name<c2Sorted[j-1].name){
				
				Character temp(c2Sorted[j]);				
				c2Sorted[j] = c2Sorted[j-1];
				c2Sorted[j-1]=temp;
			}
		}
	}
	// WAR
	string attacker,defender,skill;

	for(int i = 0;i<noR;i++){   // simulation happens inside this for !!

		readFrom >> attacker >> defender >> skill;

		if(i % 2 == 0){ // attacker from community1 , defender from community2

			int aj;
			int dk;
			for(int j = 0;j<5;j++){
				if(c1Sorted[j].name == attacker){ 
				aj = j;
				break;
				}
			}
			for(int k = 0;k<5;k++){
				if(c2Sorted[k].name == defender){ 
				dk = k;
				break;
				}
			}
			// here whoc(c1Sorted[aj]) and whoc(c2Sorted[dk]) are our attacker and defender.

			if(skill == "SPECIAL" && whoc(c1Sorted[aj],c1Sorted)->type != "Men" && whoc(c1Sorted[aj],c1Sorted)->type != "Hobbit"){ 

				int hobbitIndex;
				for(int h = 0;h<5;h++){
					if(c1Sorted[h].type == "Hobbit"){
						hobbitIndex = h;
						break;
					}				
				}
				Character* A = whoc(c1Sorted[aj],c1Sorted); // attacker
				Character* B = whoc(c2Sorted[dk],c2Sorted); // defender
				Character* Hob = &c1Sorted[hobbitIndex];

				if(A->type == "Elves"){
					if(A->nRoundsSinceSpecial >= 10){
						elvesSkill(*B,*Hob,*A); 
					}
					else{
						if(A->attack > B->defense){
							B->remainingHealth -= A->attack - B->defense;
						}
						if(B->remainingHealth <= 0){
					
							B->remainingHealth = 0;
							B->isAlive = false;
							casualties++;
							for(int a = 0;a<5;a++){
								if(B->name == c1Sorted[a].name){
									lastDead1 = B->name;
								}
								else if(B->name == c2Sorted[a].name){
									lastDead2 = B->name;
								}
							}
						}
					}
				}
				else if(A->type == "Wizards"){	
						
					bool flag = false;					
					for(int y = 0;y<5;y++){
						if(c1Sorted[y].name == lastDead1 && A->nRoundsSinceSpecial >= 50){
							wizardsSkill(c1Sorted[y],*A,*B);
							flag = true;
						}
					}
					if(flag == false){
						if(A->attack > B->defense){
							B->remainingHealth -= A->attack - B->defense;
						}
						if(B->remainingHealth <= 0){
					
							B->remainingHealth = 0;
							B->isAlive = false;
							casualties++;
							for(int a = 0;a<5;a++){
								if(B->name == c1Sorted[a].name){
									lastDead1 = B->name;
								}
								else if(B->name == c2Sorted[a].name){
									lastDead2 = B->name;
								}
							}
						}
					}
				}
				else if(A->type == "Dwarfs"){
					if(A->nRoundsSinceSpecial >= 20){
						dwarfsSkill(*B,*A);
					}
					else{
						if(A->attack > B->defense){
							B->remainingHealth -= A->attack - B->defense;
						}
						if(B->remainingHealth <= 0){
					
							B->remainingHealth = 0;
							B->isAlive = false;
							casualties++;
							for(int a = 0;a<5;a++){
								if(B->name == c1Sorted[a].name){ 
									lastDead1 = B->name;
								}
								else if(B->name == c2Sorted[a].name){
									lastDead2 = B->name;
								}
							}
						}
					}
				}
			}
			else{

				Character* A = whoc(c1Sorted[aj],c1Sorted);
				Character* B = whoc(c2Sorted[dk],c2Sorted);

				if(A->attack > B->defense)
					B->remainingHealth -= A->attack - B->defense;

				if(B->remainingHealth <= 0){
					
					B->remainingHealth = 0;
					B->isAlive = false;
					casualties++;
					for(int a = 0;a<5;a++){
						if(B->name == c1Sorted[a].name){ 
							lastDead1 = B->name;
						}
						else if(B->name == c2Sorted[a].name){
							lastDead2 = B->name;
						}
					}
				}
			}
		}
		else{ // attacker from community 2 and defender from community 1
			int aj;
			int dk;
			for(int j = 0;j<5;j++){
				if(c2Sorted[j].name == attacker){ 
				aj = j;
				break;
				}
			}
			for(int k = 0;k<5;k++){
				if(c1Sorted[k].name == defender){
				dk = k;
				break;
				}
			}
			// here whoc(c2Sorted[aj]) and whoc(c1Sorted[dk]) are our attacker and defender.

			if(skill == "SPECIAL" && whoc(c2Sorted[aj],c2Sorted)->type != "Men" && whoc(c2Sorted[aj],c2Sorted)->type != "Hobbit"){
			 // burda specialli durumlar
				Character* A = whoc(c2Sorted[aj],c2Sorted); //attacker
				Character* B = whoc(c1Sorted[dk],c1Sorted); //defender

				int hobbitIndex;
				for(int h = 0;h<5;h++){
					if(c2Sorted[h].type == "Hobbit"){
						hobbitIndex = h;
						break;
					}
				}
				Character* Hob = &c2Sorted[hobbitIndex];

				if(A->type == "Elves"){
					if(A->nRoundsSinceSpecial >= 10){
						elvesSkill(*B,*Hob,*A); 
					}
					else{
						if(A->attack > B->defense){
							B->remainingHealth -= A->attack - B->defense;
						}
						if(B->remainingHealth <= 0){
					
							B->remainingHealth = 0;
							B->isAlive = false;
							casualties++;
							for(int a = 0;a<5;a++){
								if(B->name == c1Sorted[a].name){
									lastDead1 = B->name;
								}
								else if(B->name == c2Sorted[a].name){
									lastDead2 = B->name;
								}
							}
						}
					}					
				}
				else if(A->type == "Wizards"){	
						
					bool flag = false;			
					for(int y = 0;y<5;y++){
						if(c2Sorted[y].name == lastDead2 && A-> nRoundsSinceSpecial >= 50){
							wizardsSkill(c2Sorted[y],*A,*B);
							flag = true;
						}
					}
					if(flag == false){
						if(A->attack > B->defense){
							B->remainingHealth -= A->attack - B->defense;
						}
						if(B->remainingHealth <= 0){
					
							B->remainingHealth = 0;
							B->isAlive = false;
							casualties++;
							for(int a = 0;a<5;a++){
								if(B->name == c1Sorted[a].name){ 
									lastDead1 = B->name;
								}
								else if(B->name == c2Sorted[a].name){
									lastDead2 = B->name;
								}
							}
						}
					}
				}
				else if(A->type == "Dwarfs"){
					if(A->nRoundsSinceSpecial >= 20){
						dwarfsSkill(*B,*A);
					}
					else{
						if(A->attack > B->defense){
							B->remainingHealth -= A->attack - B->defense;
						}
						if(B->remainingHealth <= 0){
					
							B->remainingHealth = 0;
							B->isAlive = false;
							casualties++;
							for(int a = 0;a<5;a++){
								if(B->name == c1Sorted[a].name){ 
									lastDead1 = B->name;
								}
								else if(B->name == c2Sorted[a].name){
									lastDead2 = B->name;
								}
							}
						}
					}
				}
			}
			else{

				Character* A = whoc(c2Sorted[aj],c2Sorted);
				Character* B = whoc(c1Sorted[dk],c1Sorted);
				if(A->attack > B->defense)
					B->remainingHealth -= A->attack - B->defense;

				if(B->remainingHealth <= 0){
					
					B->remainingHealth = 0;
					B->isAlive = false;
					casualties++;
					for(int a = 0;a<5;a++){
						if(B->name == c1Sorted[a].name){ 
							lastDead1 = B->name;
						}
						else if(B->name == c2Sorted[a].name){
							lastDead2 = B->name;
						}
					}
				}
			}
		}

		for(int j = 0;j<5;j++){ 

			c1Sorted[j].nRoundsSinceSpecial++;
			c2Sorted[j].nRoundsSinceSpecial++;
			c1Sorted[j].healthHistory[i+1] = c1Sorted[j].remainingHealth;
			c2Sorted[j].healthHistory[i+1] = c2Sorted[j].remainingHealth;
		}

		if(isDefeated(c1Sorted)){
			writeTo << "Community-2" << endl;
			realNor = i+1;
			break; // simülasyonu bitir
		}
		else if(isDefeated(c2Sorted)){ 
			writeTo << "Community-1" << endl;
			realNor = i+1;
			break;
		}


		if(i == noR-1){
			writeTo << "Draw" << endl; 
		}
	}

	// Writing to output

	writeTo << realNor << endl << casualties << endl;

	for(int l = 0;l<5;l++){
		writeTo << community1[l].name << " ";
		int j;
		for(j = 0;j<5;j++){
			if(c1Sorted[j].name == community1[l].name){
				break;
			}
		}
		for(int m = 0;m <= realNor;m++){
			writeTo << c1Sorted[j].healthHistory[m] << " ";
		}
		writeTo << endl;
	}
	for(int l = 0;l<5;l++){
		writeTo << community2[l].name << " ";
		int j;
		for(j = 0;j<5;j++){
			if(c2Sorted[j].name == community2[l].name){
				break;
			}
		}
		for(int m = 0;m <= realNor;m++){
			writeTo << c2Sorted[j].healthHistory[m] << " ";
		}
		writeTo << endl;
	}
    return 0;
}