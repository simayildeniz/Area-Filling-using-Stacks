# include <iostream>
# include <string>
# include <fstream>
# include <sstream>
# include "DynamicStackClass.h"

;using namespace std;

bool initialChecker(string & coord)
{
	for (int i = 0; i < coord.length(); i++)
	{
		if ('0' > coord[i] || coord[i] > '9')
		{
			return false;
		}
	}
	int check = stoi(coord);
	if (check < 3)
	{
		return false;
	}
	return true;
}

bool coordCheck(string & xCoord, string & yCoord, int rowSize, int columnSize)
{
	rowSize = rowSize - 1;
	columnSize = columnSize - 1;
	for (int i = 0; i < xCoord.length(); i++)
	{
		if ('0' > xCoord[i] || xCoord[i] > '9')
		{
			return false;
		}
	}
	for (int i = 0; i < yCoord.length(); i++)
	{
		if ('0' > yCoord[i] || yCoord[i] > '9')
		{
			return false;
		}
	}
	int x = stoi(xCoord);
	int y = stoi(yCoord);
	if (x > rowSize || y > columnSize)
	{
		return false;
	}
	return true;
}

/* Begin: code taken from matrix.cpp and updated */ 
void PrintMatrix(char **matrix, int rowSize, int columnSize)
{
	for(int i=0; i < rowSize; i++)
	{
		//cout << "Row " << (i+1) << " :" << endl; 
		for(int j=0; j<columnSize; j++)
		{
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
}

void DeleteMatrix(char ** & matrix, int size)
{
	for(int i=0; i<size; i++)
	{
		delete [] matrix[i];
	}
	delete [] matrix;
}
/* End: code taken from matrix.cpp and updated */

int main()
{
	string initialRow, initialColumn, fileName, line, startX, startY;
	cout << "Enter the number of rows: ";
	cin >> initialRow;
	while (!initialChecker(initialRow))
	{
		cout << initialRow << " is not valid! " << endl;
		cin.clear();
		cout << "Enter the number of rows: ";
		cin >> initialRow;
	}
	int row = stoi(initialRow); // row count is stored in row

	cout << "Enter the number of columns: ";
	cin >> initialColumn;
	while (!initialChecker(initialColumn))
	{
		cout << initialColumn << " is not valid! " << endl;
		cin.clear();
		cout << "Enter the number of columns: ";
		cin >> initialColumn;
	}
	int column = stoi(initialColumn); // column count is stored in column

	ifstream inFile;
	cout << "Please enter file name: ";
	cin >> fileName;

	inFile.open(fileName.c_str());

	while (inFile.fail())
	{
		cout << "Cannot open file named " << fileName << endl;
		cin.clear();
		cout << "Please enter file name: ";
		cin >> fileName;
		inFile.open(fileName.c_str());
	}

	cout << "Enter the starting point: ";
	cin >> startX >> startY;  // strings

	while (!coordCheck(startX,startY,row,column))
	{
		cout << "Invalid coordinate! " << endl;
		cout << "Enter the starting point: ";
		cin >> startX >> startY;
		coordCheck(startX,startY,row,column);
	}
	int xCoord =  stoi(startX);  // now they are integers
	int yCoord = stoi(startY);

	// Above, every check is made; now create a 2D dynamic char matrix

	char ** dMatrix = new char *[row];
	for (int i = 0; i < row; i++)
	{
		dMatrix[i] = new char[column];
	} // this is just a memory seperation

	int a = 0; // row // a th row
	// fill the matrix:

	while (getline(inFile,line))
	{
		for (int j = 0; j < line.length(); j++)
		{
			dMatrix[a][j] = line[j];

		}
		a++;
	}//matrix is ready:

	//PrintMatrix(dMatrix,row,column);

	if (dMatrix[xCoord][yCoord] == 'X' || dMatrix[xCoord][yCoord] == 'x')
	{
		cout << "Starting point is already occupied. " << endl;
		cout << "Terminating... " << endl;
	}
	else
	{
		char fillWith;
		cout << "Enter the filling char: ";
		cin >> fillWith;

		while (fillWith == 'X' || fillWith == 'x')
		{
			cout << "Filling char is not valid! " << endl;
			cout << "Enter the filling char: ";
			cin >> fillWith;
		} // I have a valid fill char here:

		DynamicStack myStack;
		dMatrix[xCoord][yCoord] = fillWith;

		//int checkX = xCoord;
		//int checkY = yCoord;
		bool terminate = false;

		while (!terminate)
		{
			if (((yCoord+1) < column) && (dMatrix[xCoord][yCoord+1] != 'x' || dMatrix[xCoord][yCoord+1] != 'X') && (dMatrix[xCoord][yCoord+1] == ' ') && (dMatrix[xCoord][yCoord+1] != fillWith))
			{
				// go right
				myStack.push(xCoord,yCoord);
				yCoord = yCoord + 1;
				dMatrix[xCoord][yCoord] = fillWith;
			}
			else if (((xCoord+1) < row) && (dMatrix[xCoord+1][yCoord] != 'x' || dMatrix[xCoord+1][yCoord] != 'X') && (dMatrix[xCoord+1][yCoord] == ' ') && (dMatrix[xCoord+1][yCoord] != fillWith))
			{
				// go down
				myStack.push(xCoord,yCoord);
				xCoord = xCoord + 1;
				dMatrix[xCoord][yCoord] = fillWith;

			}
			else if (((yCoord-1)>=0) && (dMatrix[xCoord][yCoord-1] != 'x' || dMatrix[xCoord][yCoord-1] != 'X') && (dMatrix[xCoord][yCoord-1] == ' ') && (dMatrix[xCoord][yCoord-1] != fillWith))
			{
				// go left
				myStack.push(xCoord,yCoord);
				yCoord = yCoord - 1;
				dMatrix[xCoord][yCoord] = fillWith;
			}
			else if (((xCoord-1)>=0) && (dMatrix[xCoord-1][yCoord] != 'x' || dMatrix[xCoord-1][yCoord] != 'X') && (dMatrix[xCoord-1][yCoord] == ' ') && (dMatrix[xCoord-1][yCoord] != fillWith))
			{
				// go up
				myStack.push(xCoord,yCoord);
				xCoord = xCoord - 1;
				dMatrix[xCoord][yCoord] = fillWith;
			}
			else
			{
				//PrintMatrix(dMatrix,row,column);
				//cout << "First" << endl;
				myStack.pop(xCoord,yCoord);
			}	

			if (myStack.isEmpty() && dMatrix[xCoord][yCoord+1] != ' ' && dMatrix[xCoord+1][yCoord] != ' ' && dMatrix[xCoord][yCoord-1] != ' ' && dMatrix[xCoord-1][yCoord] != ' ' )
			{
				terminate = true;
			}
		}
		// myStack is empty here:
		PrintMatrix(dMatrix,row,column);
	}
	DeleteMatrix(dMatrix,row);
	inFile.close();
	return 0;
}
