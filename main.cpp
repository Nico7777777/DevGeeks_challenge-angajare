#include<fstream>
#include<algorithm>
#include<stdlib.h>
#include<iomanip>
using namespace std;
ofstream f("results.txt");

struct personaj{
    short int life;
    short int power;
    short int defend;
    short int speed;
    short int luck;
}hero, monster;

void init(){
    srand(time(NULL));
    //initialization of the hero stats
    hero.life = 65 + rand()%31; //between [65 - 95]
    hero.power = 60 + rand()%11; //between [60 - 70]
    hero.defend = 40 + rand()%11; //between [40 - 50]
    hero.speed = 40 + rand()%11; //between [40 - 50]
    hero.luck = 10 + rand()%21; //between [10 - 30] out of a range of [0 - 100]

    //initialization of the monster stats
    monster.life = 55 + rand()%26; //between [55 - 80]
    monster.power = 50 + rand()%31; //between [50 - 80]
    monster.defend = 35 + rand()%21; //between [35 - 55]
    monster.speed = 40 + rand()%21; //between [40 - 60]
    monster.luck = 25 + rand()%16; //between [25 - 40] out of a range of [0 - 100]
}

short int damage(short int attacker_attack, short int defender_defend){
    //Damage = Puterea atacatorului – Apararea aparatorului (daca rezultatul este mai mic ca 0 atunci el
    //va fi 0, daca va fi mai mare ca 100 atunci va fi 100)
    short int difference = attacker_attack - defender_defend;
    difference = (difference > 0)?(difference):(0);
    difference = (difference > 100)?(100):(difference);
    return difference;
}

void show(){
    f << "erou:\n";
    f <<"life="<< hero.life <<"    power="<< hero.power <<"    defend="<< hero.defend <<"    speed="<< monster.speed<<"    luck="<< hero.luck <<"\n";
    f << "\nmonstru:\n";
    f <<"life="<< monster.life <<"    power="<< monster.power <<"    defend="<< monster.defend <<"    speed="<< monster.speed <<"    luck="<< monster.luck <<"\n";
    f<< "----------------------------------------------------------\n\n\n";
    ///It just works well
}

bool dragon_power(){
    short int  chance = rand()%10;//10% equals 1 out of 10
    return (chance == 1)? true : false;
}

bool magic_shield(){
    short int chance = rand()%5;//20% equals 1 out of 5
    return (chance == 1)? true : false; 
}

bool starting(){
    if( hero.speed > monster.speed ) return true;
    else if( hero.speed == monster.speed ){
        if( hero.luck >= monster.luck ) return true;
        else return false; 
    }
    else return false;
}

int main(){
    init();
    show();
    
    bool hero_starts = starting();

    for(short int round=1; round<=20, hero.life>0, monster.life>0; round++){
        f << "runda "<<round<<":\t";
        short int the_attack;
        if(hero_starts){
            f << "Hero's turn.\n";
            //Offensive power activation
            bool activate = dragon_power();
            
            if( activate ){
                f << "!!!THE DRAGON'S POWER IS ACTIVATED\n";
                the_attack = 2*damage(hero.power, monster.defend);
                monster.life -= the_attack;

            }
            else{
                the_attack = damage(hero.power, monster.defend);
                monster.life -= the_attack;
            }

            f << "hero's_life=" << hero.life<<"    monster's_life=" << monster.life <<"    !hero's_attack="<<the_attack<<"\n";
        }


        else{
            f << "Monster's turn.\n";
            //Defensive power activation
            bool lucky_turn = (rand()%100<hero.luck)?(true):(false);
            
            if( lucky_turn ){
                the_attack = 0;
                hero.life -= the_attack;
                f << "LUCKY TURN(hero takes no damage)\n";
            }
            else{
                bool activate = magic_shield();
                if( activate ){
                    f <<"!!!THE MAGIC SHIELD IS ACTIVATED\n";
                    the_attack = int( damage(monster.power, hero.defend)/2 );
                    hero.life -= the_attack;
                }
                else{
                    the_attack = damage(monster.power, hero.defend);
                    hero.life -= the_attack;
                    //f<<"-->"<<hero.life<<'\n';
                }
            }
            f << "hero's_life=" << hero.life<<"    monster's_life=" << monster.life <<"    !monster's_attack="<<the_attack<<"\n";
            //acum urmeaza sa zic despre ce puteri i se activeaza in functie de noroc, asta DACA se activeaza
            //stai ca asta nu are puteri, de fapt
        }

        hero_starts = !hero_starts;
        f <<"\n\n";
    }
    string result = (hero.life > monster.life)?("The hero won"):("The monster won!");
    f << result;
}