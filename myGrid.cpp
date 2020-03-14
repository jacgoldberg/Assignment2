#include <iostream>
#include <cmath>
#include <fstream>
#include "myGrid.h"

//Defualt constructor
myGrid::myGrid()
{
  rowLength = 0;
  colLength = 0;
  density = 0;
  this->grid = new char*[rowLength];
  for(int i = 0; i < rowLength; i++){
    grid[i] = new char[colLength];
  }
}

//constructor to make a grid based on random generation
myGrid::myGrid(int row, int col, double inPopDensity)
{

  rowLength = row;
  colLength = col;
  density = inPopDensity;


  this->grid = new char*[rowLength];
  for(int i = 0; i < rowLength; i++){
    grid[i] = new char[colLength];
  }

  this->shadow = new char*[rowLength];
  for(int i = 0; i < rowLength; i++){
    shadow[i] = new char[colLength];
  }
  for(int i = 0; i < rowLength; ++i){
    for(int j = 0; j < colLength; ++j){
      grid[i][j] = '-';
    }
  }
}
//Constructor for populating with a given file
myGrid::myGrid(string fileName)//, char** osolator)
{
  this->fileName = fileName;
  iFile.open(fileName);

    if(!iFile){
      cout << "Couldn't open file :( " << endl;
      exit(1);
    }

  for(int i = 0; i < 2; ++i){
      getline(iFile,value);
      if(i == 0){
        rowLength = stoi(value);
      }
      if(i == 1){
        colLength = stoi(value);
      }
    }

    grid = new char*[rowLength];
    for(int i = 0; i < rowLength; i++){
      grid[i] = new char[colLength];
    }
    int i = 0;
    while(!iFile.eof()){
      getline(iFile,value);
      if(i < rowLength){
          for(int j = 0; j < colLength - 1; ++j){
            grid[i][j] = value.at(j);
          }
        }
          i++;
      }
    iFile.close();
    this->shadow = new char*[rowLength];
    for(int i = 0; i < rowLength; i++){
      shadow[i] = new char[colLength];
    }
  }
//fills the grid with its inital values from random generation
void myGrid::fill(){

  int num1 = 0;
  int num2 = 0;
  int total = rowLength * colLength;
  int ocupiedCells = round(total * density);
  int cellsToBeFilled = 0;
  while(ocupiedCells > cellsToBeFilled){
      num1 = (int)(rand() % rowLength);
      num2 = (int)(rand() % colLength);
      grid[num1][num2] = 'X';
      cellsToBeFilled++;
    }
  }

//helper function
int myGrid::getRow(){
  return rowLength;
}
//helper function
int myGrid::getCol(){
  return colLength;
}
//Returns a bool for weather the array is empty or not
bool myGrid::isEmpty(){
  for(int i = 0; i < rowLength; ++i){
    for(int j = 0; j < colLength; ++j){
      if(grid[i][j] == 'X'){
        return false;
      }
    }
    return true;
  }
}
//sets the game mode
void myGrid::setMode(int i){
  this->mode = i;
}
//prints to the consol
void myGrid::print(){
  cout << "Generation: "<< generation << endl;
  for(int i = 0; i < rowLength; ++i){
    for(int j = 0; j < colLength; ++j){
      cout << grid[i][j];
      }
      cout << endl;
    }
    generation++;
}
//prints to a file of  users choice
void myGrid::printFile(string file){
  this->fileName = file;
  oFile.open(fileName, ios::app);
  if(!oFile){
    cout << "Sorry couldn't open it" << endl;
    exit(1);
  }
  oFile << "Generation: "<< generation << endl;
  for(int i = 0; i < rowLength; ++i){
    for(int j = 0; j < colLength; ++j){
      oFile << grid[i][j];
    }
    cout << endl;
  }
  generation++;
}
//holds all of the logic for populating the next generation
void myGrid::populate(){
  if(this->mode == 1){
    neighbor = 0;
    for(int i = 0; i < rowLength; ++i){
      for(int j = 0; j < colLength; ++j){
        neighbor = 0;
        if(i == 0){
          if(j == 0){

          if(grid[i+1][j] == 'X'){
            neighbor++;
          }
          if(grid[i+1][j+1] == 'X'){
            neighbor++;
          }
          if(grid[i][j+1] == 'X'){
            neighbor++;
          }

        }else if(j == (rowLength-1)){

          if(grid[i][j-1] == 'X'){
            neighbor++;
          }
          if(grid[i+1][j-1] == 'X'){
            neighbor++;
          }
          if(grid[i+1][j] == 'X'){
            neighbor++;
          }
        }else{
          if(grid[i][j-1] == 'X'){
            neighbor++;
          }
          if(grid[i][j+1] == 'X'){
            neighbor++;
          }
          if(grid[i+1][j] == 'X'){
            neighbor++;
          }
          if(grid[i+1][j-1] == 'X'){
            neighbor++;
          }
          if(grid[i+1][j+1] == 'X'){
            neighbor++;
          }
        }
      }else if(i == (rowLength - 1)){
          if(j == 0){
            if(grid[i-1][j] == 'X'){
              neighbor++;
            }
            if(grid[i-1][j+1] == 'X'){
              neighbor++;
            }
            if(grid[i][j+1] == 'X'){
              neighbor++;
            }

          }else if(j == (rowLength - 1)){
            if(grid[i-1][j] == 'X'){
              neighbor++;
            }
            if(grid[i-1][j-1] == 'X'){
              neighbor++;
            }
            if(grid[i][j-1] == 'X'){
              neighbor++;
            }
          }

        }else{
          if(j == 0){
            if(grid[i-1][j] == 'X'){
              neighbor++;
            }
            if(grid[i+1][j] == 'X'){
              neighbor++;
            }
            if(grid[i-1][j+1] == 'X'){
              neighbor++;
            }
            if(grid[i][j+1] == 'X'){
              neighbor++;
            }
            if(grid[i+1][j+1] == 'X'){
              neighbor++;
            }
          }else if(j == (rowLength-1)){
            if(grid[i-1][j] == 'X'){
              neighbor++;
            }
            if(grid[i+1][j] == 'X'){
              neighbor++;
            }
            if(grid[i-1][j-1] == 'X'){
              neighbor++;
            }
            if(grid[i][j-1] == 'X'){
              neighbor++;
            }
            if(grid[i+1][j-1] == 'X'){
              neighbor++;
            }
          }else{
            if(grid[i-1][j] == 'X'){
              neighbor++;
            }
            if(grid[i-1][j-1] == 'X'){
              neighbor++;
            }
            if(grid[i][j-1] == 'X'){
              neighbor++;
            }
            if(grid[i+1][j-1] == 'X'){
              neighbor++;
            }
            if(grid[i+1][j] == 'X'){
              neighbor++;
            }
            if(grid[i+1][j+1] == 'X'){
              neighbor++;
            }
            if(grid[i][j+1] == 'X'){
              neighbor++;
            }
            if(grid[i-1][j+1] == 'X'){
              neighbor++;
            }
            if(grid[i-1][j] == 'X'){
              neighbor++;
            }
          }
        }

        if(this->neighbor == 4){
          shadow[i][j] = '-';
        }else if(neighbor == 3){
          shadow[i][j] = 'X';
        }else if(neighbor == 1 || neighbor == 0){
          shadow[i][j] = '-';
        }else if(neighbor == 2){
          if(shadow[i][j] == 'X'){
            shadow[i][j] = 'X';
          }
          if(shadow[i][j] == '-'){
            shadow[i][j] = '-';
        }
      }
      }
    }
    for(int i = 0; i < rowLength; ++i){
      for(int j = 0; j < colLength; ++j){
        grid[i][j] = shadow[i][j];
      }
    }
  }

  if(this->mode == 2){
    int neighbor = 0;
    for(int i = 0; i < rowLength; ++i){
      for(int j = 0; j < colLength; ++j){
        if(i == 0){
          if(j == 0){
            if(grid[0][0] == 'X'){
              neighbor += 3;
            }
            if(grid[i+1][0] == 'X'){
              neighbor += 2;
            }
            if(grid[i][j+1] == 'X'){
              neighbor+=2;
            }
            if(grid[i+1][j+1] == 'X'){
              neighbor++;
            }
          }else if(j==(rowLength-1)){
            if(grid[0][rowLength-1] == 'X'){
              neighbor += 3;
            }
            if(grid[0][j-1] == 'X'){
              neighbor += 2;
            }
            if(grid[i+1][j] == 'X'){
              neighbor += 2;
            }
            if(grid[i+1][j-1] == 'X'){
              neighbor++;
            }
          }else{
            if(grid[i][j-1] == 'X'){
              neighbor += 2;
            }
            if(grid[i][j] == 'X'){
              neighbor ++;
            }
            if(grid[i][j+1] == 'X'){
              neighbor += 2;
            }
            if(grid[i-1][j-1] == 'X'){
              neighbor++;
            }
            if(grid[i-1][j] == 'X'){
              neighbor++;
            }
            if(grid[i-1][j+1] == 'X'){
              neighbor++;
            }
          }
        }else if(i == (colLength-1)){
          if(j == 0){
            if(grid[i][j] == 'X'){
              neighbor += 3;
            }
            if(grid[i-1][j] == 'X'){
              neighbor += 2;
            }
            if(grid[i][j+1] == 'X'){
              neighbor += 2;
            }
            if(grid[i-1][j+1] == 'X'){
              neighbor++;
            }
          }else if(j == (rowLength-1)){
            if(grid[i][j] == 'X'){
              neighbor += 3;
            }
            if(grid[i][j-1] == 'X'){
              neighbor += 2;
            }
            if(grid[i-1][j] == 'X'){
              neighbor += 2;
            }
            if(grid[i-1][j-1] == 'X'){
              neighbor++;
            }
          }else{
            if(grid[i][j-1] == 'X'){
              neighbor += 2;
            }
            if(grid[i][j] == 'X'){
              neighbor++;
            }
            if(grid[i][j+1] == 'X'){
              neighbor += 2;
            }
            if(grid[i-1][j-1] == 'X'){
              neighbor++;
            }
            if(grid[i][j] == 'X'){
              neighbor++;
            }
            if(grid[i-1][j+1] == 'X'){
              neighbor++;
            }
          }
        }else if(j == 0 || j == (rowLength - 1) && (i != 0 && i != (colLength - 1))){
          if(j == 0){
            if(grid[i][j] == 'X'){
              neighbor ++;
            }
            if(grid[i+1][j] == 'X'){
              neighbor += 2;
            }
            if(grid[i-1][j] == 'X'){
              neighbor += 2;
            }
            if(grid[i+1][j+1] == 'X'){
              neighbor++;
            }
            if(grid[i][j+1] == 'X'){
              neighbor++;
            }
            if(grid[i-1][j+1] == 'X'){
              neighbor++;
            }
          }else if(j == (rowLength-1)){
            if(grid[i][j] == 'X'){
              neighbor++;
            }
            if(grid[i-1][j] == 'X'){
              neighbor += 2;
            }
            if(grid[i+1][j] == 'X'){
              neighbor += 2;
            }
            if(grid[i-1][j-1] == 'X'){
              neighbor++;
            }
            if(grid[i][j-1] == 'X'){
              neighbor++;
            }
            if(grid[i+1][j-1] == 'X'){
              neighbor++;
            }
          }
        }else{
          if(grid[i-1][j] == 'X'){
            ++neighbor;
          }
          if(grid[i-1][j-1] == 'X'){
            ++neighbor;
          }
          if(grid[i][j-1] == 'X'){
            ++neighbor;
          }
          if(grid[i+1][j-1] == 'X'){
            ++neighbor;
          }
          if(grid[i+1][j] == 'X'){
            ++neighbor;
          }
          if(grid[i+1][j+1] == 'X'){
            ++neighbor;
          }
          if(grid[i][j+1] == 'X'){
            ++neighbor;
          }
          if(grid[i-1][j+1] == 'X'){
            ++neighbor;
          }
          if(grid[i-1][j] == 'X'){
            ++neighbor;
          }
        }
        if(neighbor == 4){
          shadow[i][j] = '-';
        }else if(neighbor == 3){
          shadow[i][j] = 'X';
        }else if(neighbor <= 1){
          shadow[i][j] = '-';
        }
        }
        }
        for(int i = 0; i < rowLength; ++i){
          for(int j = 0; j < colLength; ++j){
            grid[i][j] = shadow[i][j];
          }
        }
  }
  if(this->mode == 3){
    int neighbor = 0;
    for(int i = 0; i < rowLength; ++i){
      for(int j = 0; j < colLength; ++j){
        if(i == 0){
          if(j == 0){
            if(grid[rowLength-1][colLength-1] == 'X'){
              neighbor++;
              }
            if(grid[colLength-1][0] == 'X'){
              neighbor++;
            }
            if(grid[colLength-1][1] == 'X'){
              neighbor++;
            }
            if(grid[0][rowLength-1] == 'X'){
              neighbor++;
            }
            if(grid[1][rowLength-1] == 'X'){
              neighbor++;
            }
          }else if(j == (rowLength - 1)){
            if(grid[colLength-1][0] == 'X'){
              neighbor++;
            }
            if(grid[i][0] == 'X'){
              neighbor++;
            }
            if(grid[i+1][rowLength- 1] == 'X'){
              neighbor++;
            }
            if(grid[colLength-1][j-1] == 'X'){
              neighbor++;
            }
            if(grid[colLength-1][j] == 'X'){
              neighbor++;
            }
          }else {
            if(grid[colLength-1][j] == 'X'){
              neighbor++;
            }
            if(grid[colLength-1][j-1]){
              neighbor++;
            }
            if(grid[colLength-1][j + 1] == 'X'){
              neighbor++;
            }
          }
        }else if(i == (colLength-1)){
            if(j == 0){
              if(grid[0][rowLength-1] == 'X'){
                neighbor++;
              }
              if(grid[colLength-1][rowLength-1] == 'X'){
                neighbor++;
              }
              if(grid[i-1][rowLength-1] == 'X'){
                neighbor++;
              }
              if(grid[0][0] == 'X'){
                neighbor++;
              }
              if(grid[0][1] == 'X'){
                neighbor++;
              }
            }else if(j == (rowLength - 1)){
              if(grid[0][0] == 'X'){
                neighbor++;
              }
              if(grid[0][rowLength-1] == 'X'){
                neighbor++;
              }
              if(grid[0][j-1] == 'X'){
                neighbor++;
              }
              if(grid[i][0]== 'X'){
                neighbor++;
              }
              if(grid[i-1][0] == 'X'){
                neighbor++;
              }
            }else{
              if(grid[0][j] == 'X'){
                neighbor++;
              }
              if(grid[0][j-1] == 'X'){
                neighbor++;
              }
              if(grid[0][j+1] == 'X'){
                neighbor++;
              }
            }
          }else if((i != 0 && i != (colLength - 1)) && (j == 0 && j == (rowLength - 1))){
            if(j==0){
              if(grid[i][rowLength-1] == 'X'){
                neighbor++;
              }
              if(grid[i+1][rowLength-1] == 'X'){
                neighbor++;
              }
              if(grid[i-1][rowLength-1] == 'X'){
                neighbor++;
              }
            }else if(j == (rowLength - 1)){
              if(grid[i][0] == 'X'){
                neighbor++;
              }
              if(grid[i+1][0] == 'X'){
                neighbor++;
              }
              if(grid[i-1][0] == 'X'){
                neighbor++;
              }
            }
          }else{
            if(grid[i-1][j] == 'X'){
              ++neighbor;
            }
            if(grid[i-1][j-1] == 'X'){
              ++neighbor;
            }
            if(grid[i][j-1] == 'X'){
              ++neighbor;
            }
            if(grid[i+1][j-1] == 'X'){
              ++neighbor;
            }
            if(grid[i+1][j] == 'X'){
              ++neighbor;
            }
            if(grid[i+1][j+1] == 'X'){
              ++neighbor;
            }
            if(grid[i][j+1] == 'X'){
              ++neighbor;
            }
            if(grid[i-1][j+1] == 'X'){
              ++neighbor;
            }
            if(grid[i-1][j] == 'X'){
              ++neighbor;
            }
          }
          if(neighbor == 4){
            shadow[i][j] = '-';
          }else if(neighbor == 3){
            shadow[i][j] = 'X';
          }else if(neighbor <= 1){
            shadow[i][j] = '-';
          }
      }
    }
    for(int i = 0; i < rowLength; ++i){
      for(int j = 0; j < colLength; ++j){
        grid[i][j] = shadow[i][j];
      }
    }
  }
}
