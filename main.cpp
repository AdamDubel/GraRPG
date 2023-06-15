#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <windows.h>
using namespace std;
string przeciwnicy[23]={"Dziki pies","Dzik","Wilk","Niedzwiedz","Tygrys","Lucznik","Wojownik","Komandor","General","Malpi miotacz","Malpi wojownik","Goblin","Dziki Skuga","Mahon","Ork","Czarny Or","Drzewiec","Sukkub","Minotaur","Centaur","Smok","Dziekan"};
class Character {
    public:
    string name;
    int strength;
    int speed;
    int agility;
    int HPPlayer;
    int experience=0;
    int level=1;
    int expReq[20]={30,80,150,300,750,1100,1500,2100,3000,4000,5500,6750,8000,10000,11000,12000,13000,14000,15500,17000};
    int punkty=0;
    int czymabron[3]={0,0,0};
    int czymapancerz[3]={0,0,0};
};
class Item{
public:
    string nazwa;
    int id;
    int strength;
    int speed;
    int agility;
    int durability;
    Item(string nazwa,int id,int strength,int speed,int agility, int durability):nazwa(nazwa),id(id),strength(strength),speed(speed),agility(agility),durability(durability){}

};
int wybor;

void createCharacter(Character* character, int availablePoints) {
        int dobrze=0;
do{
    cout << "Podaj nazwe postaci: ";
    cin >> character->name;

    cout << "Dostepne punkty: " << availablePoints << endl;

    cout << "Podaj wartosc atrybutu sily: ";
    cin >> character->strength;
    availablePoints -= character->strength;

cout << "Podaj wartosc atrybutu szybkosci: ";
    cin >> character->speed;
    availablePoints -= character->speed;

    cout << "Podaj wartosc atrybutu zwinnosci: ";
    cin >> character->agility;
    availablePoints -= character->agility;

    cout << "Pozostale niewykorzystane punkty: " << availablePoints << endl;
    character->HPPlayer=character->agility*10;
    character->punkty=availablePoints;
        if(availablePoints<0){
                cout<<"Przekroczyles limit punktow!"<<endl<<"Postac nie zostala stworzona"<<endl;
        dobrze=0;
    }
    else{
        dobrze=1;
    }
}while(dobrze==0);
}
void DodajPunkty(Character* character, int availablePoints) {
    int dobrze=0;
do{

    cout << "Dostepne punkty: " << availablePoints << endl;
int s;
    cout << "Dodaj wartosc atrybutu sily: ";
    cin >> s;
    character->strength+=s;
    availablePoints -= s;

cout << "Podaj wartosc atrybutu szybkosci: ";
    cin >> s;
    character->speed+=s;
    availablePoints -= s;

    cout << "Podaj wartosc atrybutu zwinnosci: ";
    cin >> s;
    character->agility+=s;
    availablePoints -= s;

    cout << "Pozostale niewykorzystane punkty: " << availablePoints << endl;
    character->HPPlayer=character->agility*10;
    character->punkty=availablePoints;
    if(availablePoints<0){
            cout<<"Przekroczyles limit punktow! Sprobuj jeszcze raz"<<endl;
        dobrze=0;
    }
    else{
        dobrze=1;
    }
}while(dobrze==0);
}
Character generateEnemy(Character* player) {
    Character enemy;
    int los=rand()%3+player->level;
    enemy.name = przeciwnicy[los];
    enemy.strength = rand() % 10+(player->level*5);
    enemy.speed = rand() % 10+(player->level*5);
    enemy.agility = rand() % 10+(player->level*5);
    return enemy;
}

void fight(Character* player, Character enemy) {
    if((player->HPPlayer/player->agility*10)*100<10){
        cout<<"Masz za malo zdrowia aby walczyc! Ulecz sie najpierw"<<endl;

    }
    else{
    int start;
    int HPEnemy=enemy.agility*10;
    int obrazenia;
    system("cls");
    cout << "Pojedynek: " << player->name << " vs " << enemy.name << endl;
    cout << "Statystyki gracza"<<endl;
    cout << "Sila " << player->name << ": " << player->strength << endl;
    cout << "Szybkosc " << player->name << ": " << player->speed << endl;
    cout << "Zwinnosc " << player->name << ": " << player->agility << endl;
    cout << "Punkty Zycia " << player->name << ": " << player->HPPlayer << endl;

    cout <<endl<< "Statystyki przeciwnika"<<endl;
    cout << "Sila " << enemy.name << ": " << enemy.strength << endl;
    cout << "Szybkosc " << enemy.name << ": " << enemy.speed << endl;
    cout << "Zwinnosc " << enemy.name << ": " << enemy.agility << endl;
    cout << "Punkty Zycia " << enemy.name << ": " << HPEnemy << endl;

    int enemyScore = enemy.strength + enemy.speed + enemy.agility;
    if (player->speed > enemy.speed) {
        cout << "Gracz " << player->name << " zaczyna jako pierwszy" << endl;
    start=1;
    }
    else {
        cout << "Przeciwnik " << enemy.name << " zaczyna jako pierwszy" << endl;
    start=0;
    }
    while(HPEnemy>0 && player->HPPlayer>0){
    if(start==1){
    obrazenia=(rand()%3+1)*player->strength;
    HPEnemy-=obrazenia;
    start=0;
    if(HPEnemy<=0){start=2;}
    cout<<endl<<"Gracz zadaje: "<<obrazenia<<" obrazen"<<endl<<"Pozostale HP przeciwnika: "<<HPEnemy<<endl;
    Sleep(3000);
                }
    if(start==0){
    obrazenia=(rand()%3+1)*enemy.strength;
    player->HPPlayer-=obrazenia;
    start=1;
    cout<<endl<<"Otrzymujesz: "<<obrazenia<<" obrazen"<<endl<<"Twoje pozostale HP: "<<player->HPPlayer<<endl;
    Sleep(3000);

                }

    }
    if(HPEnemy<=0){
        cout<<"Wygrales"<<endl<<"Otrzymane doswiadczenie: "<< enemyScore<<endl;
        player->experience+=enemyScore;
        if(player->experience>player->expReq[player->level-1]){
            cout<<"Otrzymujesz awans!"<<endl;
            player->level+=1;
            player->punkty+=10;
        }
//Przedmiot
            int los=rand()%100+1;
                if(los==1){
cout<<"Otrzymujesz legendarny przedmiot"<<endl;
player->czymabron[2]=1;
                            }
                            else if(los>1&&los<7){
cout<<"Otrzymujesz rzadki przedmiot"<<endl;
player->czymabron[1]=1;
                            }
                            else if(los>6&&los<17){
cout<<"Otrzymujesz zwykly przedmiot"<<endl;
player->czymabron[0]=1;

                            }
    }
    else{
        cout<<"Przegrales"<<endl;
    }
    }
}
void leczenie(Character* player){
int koniec=1;
int wybor;
while(koniec==1){
cout<<"Ulecz swoje rany za pomoca doswiadczenia"<<endl;
cout<<"Liczba twoich punktow doswiadczenia: "<<player->experience<<endl;
cout<<"Lizba twoich punktow zycia: "<<player->HPPlayer<<endl<<endl;
cout<<"1. Ulecz 10HP za 5 exp"<<endl;
cout<<"2. Ulecz 50HP za 25 exp"<<endl;
cout<<"0. Powrot"<<endl;
cin>>wybor;
switch(wybor){
case 1:{
    if(player->experience<5){
        cout<<"Nie uleczono! Masz za malo doswiadzcenia"<<endl;
    }
    else{
system("cls");
cout<<"Uleczono 10HP za 5 exp"<<endl;
player->HPPlayer+=10;
player->experience-=5;
}
break;
}
case 2:{
       if(player->experience<25){
        cout<<"Nie uleczono! Masz za malo doswiadzcenia"<<endl;
    }
    else{
system("cls");
cout<<"Uleczono 50HP za 25 exp"<<endl;
player->HPPlayer+=50;
player->experience-=25;
    }
break;
}
case 0:{
koniec=0;
break;
}
            }
    }
}
void saveCharacter(Character* character, const string& filename) {
ifstream isfile(filename);
    if (isfile.good()) {
        cout << "Plik o nazwie " << filename << " juz istnieje. Czy chcesz go nadpisac? (y/n): ";
        char choice;
        cin >> choice;
        if (choice != 'y' && choice != 'Y') {
            cout << "Zapis postaci anulowany." << endl;
            return;
        }
    }

    ofstream file(filename);
    if (file.is_open()) {
        file << character->name << endl;
        file << character->strength << endl;
        file << character->speed << endl;
        file << character->agility << endl;
        file << character->HPPlayer << endl;
        file << character->experience << endl;
        file << character->level << endl;
        file << character->punkty << endl;
        file.close();
        cout << "Postac zostala zapisana do pliku: " << filename << endl;
    }
    else {
        cout << "Nie udalo sie otworzyc pliku do zapisu." << endl;
    }
}

void loadCharacter(Character* character, const string& filename) {
    ifstream file(filename);
    if (file.is_open()) {
        getline(file, character->name);
        file >> character->strength;
        file >> character->speed;
        file >> character->agility;
        file >> character->HPPlayer;
        file >> character->experience;
        file >> character->level;
        file >> character->punkty;
        file.close();
        cout << "Postac zostala wczytana z pliku: " << filename << endl;
    }
    else {
        cout << "Nie udalo sie otworzyc pliku do wczytania." << endl;
    }
}

int main() {
    srand(time(NULL));
    Character player;
    Item bron0("Miecz",0,3,1,1,3);
    Item bron1("Topor",1,8,3,3,5);
    Item bron2("Wlocznia",2,20,10,10,8);
    int availablePoints =100;

int koniec=1;
while(koniec==1){
cout<<"1. Kolejny przeciwnik"<<endl<<"2. Ekwipunek"<<endl<<"3. Postac"<<endl<<"4. Dodaj Punkty"<<endl<<"5. Zapisz Postac"<<endl<<"6. Wczytaj Postac"<<endl<<"9.Stworz nowa postac"<<endl<<"0. Wyjscie "<<endl;
cin >>wybor;
switch(wybor){
case 1:{
    Character enemy = generateEnemy(&player);
    fight(&player, enemy);
    break;
        }
case 2:{
    cout<<"Twoj ekwipunek: "<<endl;
    if(player.czymabron[0]==0&&player.czymabron[1]==0&&player.czymabron[2]==0){
        cout<<"Brak przedmiotow w ekwipunku"<<endl;
    }
    if(player.czymabron[0]==1){
        cout<<"Posiadasz miecz: "<<endl<<"Sila=3"<<endl<<"Szybkosc=1"<<endl<<"Zrecznosc=1"<<endl<<"Wytrzymalosc=3"<<endl;
    }
    if(player.czymabron[1]==1){
        cout<<"Posiadasz topr: "<<endl<<"Sila=8"<<endl<<"Szybkosc=3"<<endl<<"Zrecznosc=3"<<endl<<"Wytrzymalosc=5"<<endl;
    }
    if(player.czymabron[2]==1){
        cout<<"Posiadasz wlocznie: "<<endl<<"Sila=20"<<endl<<"Szybkosc=10"<<endl<<"Zrecznosc=10"<<endl<<"Wytrzymalosc=8"<<endl;
    }
    cout<<"Ktora bron chcesz zalozyc? Pamietaj ze poprzednia zostanie pozostawiona"<<endl;
    int bron;
    cin>>bron;
    if(bron==1&&player.czymabron[0]==1){
            cout<<"Zakladasz miecz"<<endl;
    }
    else if(bron==2&&player.czymabron[1]==1){
            cout<<"Zakladasz topor"<<endl;
    }
    else if(bron==3&&player.czymabron[2]==1){
            cout<<"Zakladasz wlocznie"<<endl;
    }
    else{
        cout<<"Nie masz takiej broni"<<endl;
    }
    break;
}
case 3:{
    int wybor2;
    system("cls");
    cout<<"Postac: "<< player.name<<endl;
    cout<<"Sila: "<< player.strength<<endl;
    cout<<"Zrecznosc: "<<player.agility<<endl;
    cout<<"Szybkosc: "<<player.speed<<endl;
    cout<<"Punkty Zycia: "<<player.HPPlayer<<endl;
    cout<<"Poziom: "<<player.level<<endl;
    cout<<"Doswiadczenie: "<<player.experience<<" / "<<player.expReq[player.level-1]<<endl;
    cout<<"Pozostale punkty do rozdysponowania: "<<player.punkty<<endl;
    cout<<"Aby dodac punkty wcisnij 1:"<<endl;
    cout<<"Aby sie uleczyc wcisnij 2:"<<endl;
    cin>>wybor2;
    switch(wybor2){
case 1:{
system("cls");
DodajPunkty(&player,player.punkty);
break;
}
case 2:{
system("cls");
leczenie(&player);
break;
    }
    }
    break;
}
case 4:{
system("cls");
DodajPunkty(&player,player.punkty);
break;
}
case 5:{
system("cls");
    string filename=player.name;
    saveCharacter(&player, filename);
    break;
}
case 6:{
system("cls");
    string filename;
    cout << "Podaj nazwe pliku do wczytania: ";
    cin >> filename;
    loadCharacter(&player, filename);
    break;
}
case 9:{
system("cls");
    createCharacter(&player, availablePoints);
    break;
}
case 0:{
koniec=0;
break;
}
default:{

    cout<<"Nic";
    break;
}
}
}



    return 0;
}
