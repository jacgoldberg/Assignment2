#include <iostream>
#include <fstream>
#include <string>
using namespace std;
class myGrid{
    public:
        myGrid();
        myGrid(int r, int c, double p);
        myGrid(string s);
        ~myGrid();

        void fill();
        void fill(double);
        void populate();
        void print();
        int getRow();
        int getCol();
        bool isEmpty();
        void setMode(int);
        void printFile(string);
        //bool osolation();

    private:
      double density = 0.0;
      int rowLength = 0;
      int colLength = 0;
      char** grid;
      int mode = 0;
      char** shadow;
      ofstream oFile;
      string fileName = "";
      int generation;
      string value = "";
      ifstream iFile;
      int neighbor = 0;
};
