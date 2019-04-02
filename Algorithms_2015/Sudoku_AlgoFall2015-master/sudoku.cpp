// Declarations and functions for the Sudoku project

#include <iostream>
#include <limits.h>
#include "d_matrix.h"
#include "d_except.h"
#include <list>
#include <fstream>
#include <cstdlib>

using namespace std;

typedef int ValueType; // The type of the value in a cell
const int Blank = -1;  // Indicates that a cell is blank
 
const int SquareSize = 3;  //  The number of cells in a small square
                           //  (usually 3).  The board has
                           //  SquareSize^2 rows and SquareSize^2
                           //  columns.

const int BoardSize = SquareSize * SquareSize;

const int MinValue = 1;
const int MaxValue = 9;

int numSolutions = 0;

class board
// Stores the entire Sudoku board
{
   public:
      board(int);
      void clear();
      void initialize(ifstream &fin);

      void print();
      bool isBlank(int, int);
      ValueType getCell(int, int);
      void  setCell(int i,int j, ValueType val); 
      void clearCell(int i, int j, ValueType val);

      void printConflicts();
      bool isSolved();
      bool checkConflicts(int i, int j, int value);
      void updateConflicts(int i, int j, ValueType val);

      int squareNumber(int, int);

      void solve();

   private:

      // The following matrices go from 1 to BoardSize in each
      // dimension.  I.e. they are each (BoardSize+1) X (BoardSize+1)

      matrix<ValueType> value;
      matrix<ValueType> conflicts;

      vector <vector<bool> > squareConflicts;
      vector <vector<bool> > rowConflicts;
      vector <vector<bool> > colConflicts;
};



board::board(int sqSize)
   : value(BoardSize+1,BoardSize+1), conflicts(BoardSize + 1, BoardSize + 1)
// Board constructor
{
	//resize boolean vectors of vectors
	squareConflicts.resize(9);
	rowConflicts.resize(9);
	colConflicts.resize(9);


	for (int i = 1; i <= 9; i++)
	{
		squareConflicts[i-1].resize(9);
		rowConflicts[i-1].resize(9);
		colConflicts[i-1].resize(9);
	}
	clear();
}

void board::clear()
// Clear the entire board.
{
    for (int i = 1; i <= BoardSize; i++)        //loop board
    {
        for (int j = 1; j <= BoardSize; j++)
        {
            value[i][j] = Blank;                //set blank
            conflicts[i][j] = 0;
            rowConflicts[i-1][j-1] = false;             //set conflict vectors
            colConflicts[i-1][j-1] = false;
            squareConflicts[i-1][j-1] = false;
        }
    }
}

void  board::setCell(int i,int j, ValueType val)
// set cell i,j to val and update conflicts
{
	int squarenum = squareNumber(i, j); //finds the square number

	value[i][j]=val;

    updateConflicts(i, j, val);
}

void board::initialize(ifstream &fin)
// Read a Sudoku board from the input file.
{
   char ch;

   clear();
   for (int i = 1; i <= BoardSize; i++)
      for (int j = 1; j <= BoardSize; j++)
      {
	 fin >> ch;

         // If the read char is not Blank
	 if (ch != '.')
	 {
            setCell(i,j,ch-'0');   // Convert char to int
	 }
      }
}

int board::squareNumber(int i, int j)
// Return the square number of cell i,j (counting from left to right,
// top to bottom.  Note that i and j each go from 1 to BoardSize
{
   // Note that (int) i/SquareSize and (int) j/SquareSize are the x-y
   // coordinates of the square that i,j is in.  

   return SquareSize * ((i-1)/SquareSize) + (j-1)/SquareSize + 1;
}

ostream &operator<<(ostream &ostr, vector<int> &v)
// Overloaded output operator for vector class.
{
   for (int i = 0; i < (int)v.size(); i++)
      ostr << v[i] << " ";
   ostr << endl;
   return ostr;
}

ValueType board::getCell(int i, int j)
// Returns the value stored in a cell.  Throws an exception
// if bad values are passed.
{
   if (i >= 1 && i <= BoardSize && j >= 1 && j <= BoardSize)
      return value[i][j];
   else
      throw rangeError("bad value in getCell");
}

bool board::isBlank(int i, int j)
// Returns true if cell i,j is blank, and false otherwise.
{
    if (i < 1 || i > BoardSize || j < 1 || j > BoardSize)
        throw rangeError("bad value in setCell");
    if (value[i][j] < 1 || value [i][j] > 9)
        return true;
    else
        return false;
}

void board::print()
// Prints the current board.
{
   for (int i = 1; i <= BoardSize; i++)
   {
      if ((i-1) % SquareSize == 0)
      {
         cout << " -";
	 for (int j = 1; j <= BoardSize; j++)
	    cout << "---";
         cout << "-";
	 cout << endl;
      }
      for (int j = 1; j <= BoardSize; j++)
      {
	 if ((j-1) % SquareSize == 0)
	    cout << "|";
	 if (!isBlank(i,j))
	    cout << " " << getCell(i,j) << " ";
	 else
	    cout << "   ";
      }
      cout << "|";
      cout << endl;
   }

   cout << " -";
   for (int j = 1; j <= BoardSize; j++)
      cout << "---";
   cout << "-";
   cout << endl;
}

bool board::isSolved()
{
    for (int i = 1; i <= BoardSize; i++)
    {
        for (int j = 1; j <= BoardSize; j++)
        {
            if (squareConflicts[i-1][j-1] == false)
            {
                return false;
            }
        }
    }
    //cout<<"Puzzle solved!"<<endl;
    return true;
}

bool board::checkConflicts(int i, int j, int value)
{
	int squarenum = squareNumber(i, j);

	if(!isBlank(i,j)) //checks if not blank
		return true;
	else if (squareConflicts[squarenum-1][value-1])
		return true;
	else if (rowConflicts[i-1][value-1])
		return true;
	else if (colConflicts[j-1][value-1])
		return true;
	else
		return false;
}

void board::updateConflicts(int i, int j, ValueType val)
{
	int squarenum = squareNumber(i,j);

	squareConflicts[squarenum-1][val-1] = true; //creates confict at sq
	rowConflicts[i-1][val-1] = true;
	colConflicts[j-1][val-1] = true;
}

void board::clearCell(int i, int j, ValueType val)
//  clear cell i,j and update conflicts
{
    value[i][j] = Blank;                            //set matrix index to blank

    int s = squareNumber(i,j);                      //get square number
    rowConflicts[i-1][val-1] = false;                       //set conflict vectors to false
    colConflicts[j-1][val-1] = false;
    squareConflicts[s-1][val-1] = false;
}

void board::printConflicts()
{
	cout<<"Conflicts\n---------------------"<<endl;

	for (int r = 0; r < 9; r++)
	{
		cout<<"Conflicts in Row "<<r<<":"<<endl;
		cout<<"Columns ";
		for (int c = 0; c < 9; c++)
		{
			//checks the row
			if (!rowConflicts[r][c])
				cout<<c<<" ";
		}
		cout<<endl;
	}

	for (int r = 0; r < 9; r++)
	{
		cout<<"Conflicts in Column "<<r<<":"<<endl;
		cout<<"Rows ";
		for (int c = 0; c < 9; c++)
		{
			//checks the row
			if (!colConflicts[r][c])
				cout<<c<<" ";
		}
		cout<<endl;
	}

	for (int r = 0; r < 9; r++)
	{
		cout<<"Conflicts in Square "<<r<<":"<<endl;
		cout<<"Indexes ";
		for (int c = 0; c < 9; c++)
		{
			//checks the row
			if (!squareConflicts[r][c])
				cout<<c<<" ";
		}
		cout<<endl;
	}
}

void board::solve()
{
    int i=0, j=0, k=0;
    int r=1, c=1;
    bool check = false;
    if (isSolved() == true)
    {
        print();
    }
    else
    {
        for (i = 1; i <= BoardSize; i++)
        {
            for (j = 1; j <= BoardSize; j++)
            {
                for (k = 1; k <= BoardSize; k++)
                {
                    if (checkConflicts(i,j,k) == false && isBlank(i, j) == true)
                        conflicts[i][j]++;
                }
            }
        }

        for (i = 1; i <= BoardSize; i++)
        {
            for (j = 1; j <= BoardSize; j++)
            {
                check = isBlank(i,j);
                if (check)
                {
                    r = i;
                    c = j;
                    break;
                }
            }
            if (check)
                break;
        }


        for (i = 1; i <= BoardSize; i++)
        {
            for (j = 1; j <= BoardSize; j++)
            {
                if (conflicts[r][c] > conflicts [i][j]  && isBlank(i, j) == true)
                {
                    r = i;
                    c = j;
                }
            }
        }

        for (k = 1; k <= BoardSize; k++)
        {
            if (checkConflicts(r, c, k) == false)
            {
                setCell(r, c, k);
                print();
                numSolutions++;
                solve();
                if (isSolved() == false)
                    clearCell(r,c,k);
            }
        }
    }
}

int main()
{
   ifstream fin;
   
   // Read the sample grid from the file.
   string fileName = "sudoku.txt";

   fin.open(fileName.c_str());
   if (!fin)
   {
      cerr << "Cannot open " << fileName << endl;
      exit(1);
   }

   try
   {
      board b1(SquareSize);
      numSolutions = 0;
      while (fin && fin.peek() != 'Z')
      {
	 b1.initialize(fin);
	 b1.print();
	 //b1.printConflicts();
	 b1.solve();
	 if(b1.isSolved()){
		 cout<<"Board is solved!"<<endl;
	 	 cout<<"It took "<<numSolutions<<" recursive calls"<<endl;
	 	 }
      }
   }
   catch  (indexRangeError &ex)
   {
      cout << ex.what() << endl;
      exit(1);
   }
}

