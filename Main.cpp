#include <iostream>
#include <fstream>
#include <cstdlib>
#include "myGrid.h"
#include <thread>
#include <chrono>
using namespace std;

bool start(){
  bool a;
  cout << "Would you like to begin?(1/0)" << endl;
  cin >> a;
  return a;
}
void flair(){
  cout << "                 ---------WELCOME TO THE GAME OF LIFE---------" << endl;
}

int main(int argc, char **argv){
  char answer = '\0';
  int rowLength = 0;
  int colLength = 0;
  double inPopDensity = 0.0;
  myGrid* map;
  bool ent = false;
  bool fileBool = false;

  if(start()){
    flair();
//inital user prompting
    char answer = '\0';
    string fileName = "\0";
    cout << "Would you like to provide a file map for the game or use a randomly generated one? (F/R)" << endl;
    cin >> answer;
    if(answer == 'F'){
      cout << "Please enter the name of the .txt file: " << endl;
      cin >> fileName;
      map = new myGrid(fileName);
    }
    else{
//Random variable prompting
    cout << "What would you like the width of your world to be?: " << endl;
    cin >> rowLength;
    cout << "What would you like the length of your world to be?: " << endl;
    cin >> colLength;
    cout << "What would you like your initial population density to be?(1 > x > 0): " << endl;
    cin >> inPopDensity;
    map = new myGrid(rowLength, colLength, inPopDensity);
    map->fill();
  }

    cout << "Which mode would you Like?\nDefault: (D)\nDonut/Torus: (T)\nMirror: (M)" << endl;
    cin >> answer;

    map->print();
    if(answer == 'D'){
       map->setMode(1);
       while(!(map->isEmpty())){
       map->populate();
       map->print();
     }
     }
    if(answer == 'T'){
      while(map->isEmpty() /* && isOsolating()*/){
      map->setMode(2);
      map->populate();
      map->print();
      }
    }
    if(answer == 'M'){

      map->setMode(3);

      while(!(map->isEmpty()) /* && isOsolating()*/){
      map->populate();
      map->print();
    }
  }

  }
}
