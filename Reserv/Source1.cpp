/* Морской бой */

#include  <iostream>
#include <conio.h> //_getch()
#include <math.h>
#include <time.h>
#include <windows.h>
//#include <string.h>
//#include <stdio.h>
//#include <errno.h>
//#include <stdlib.h>


using namespace std;

// Global Var	
const int size = 10;


// Structures
struct ships{
	int deckNum;// decks number
	int amount; // ships quantity 
};


// Procedure & Function Prototypes
void arrPrint(int arr[][size]); // Any array print
void fieldHumanCreate(int arrHum[][size]); // Filling Human Field
bool interferentionCheck(int arr1[][size], int **arr2, int size2);// Check arrays interferention 
void fieldPCCreate(int arrPC[][size]); // Filling PC Field


void main() {

	srand(time(NULL));

	// Create battle fields arrays
	int fieldHum[size][size];
	int fieldPC[size][size];


	//cout << "\t-Sea Battle-" << endl << endl;

	//cout << "Arrange your ships!" << endl << endl;
	//system("pause");

	/*for (int i = 0; i < 256; i++){
		cout << i << "-" << char(i) << endl;
	}
	system("pause");*/

	//fieldHumanCreate(fieldHum);
	//system("cls");
	//arrPrint(fieldHum);
	//cout << "Now PC will arrange his ships" << endl;
	fieldPCCreate(fieldPC);


	//ships ship1;
	//ship1.deckNum = 1;
	//ship1.amount = 4;
	//ships ship2;
	//ship2.deckNum = 2;
	//ship1.amount = 3;
	//ships ship3;
	//ship3.deckNum = 3;
	//ship1.amount = 2;
	//ships ship4;
	//ship4.deckNum = 4;
	//ship1.amount = 1;














}//main


// Filling PC Field
void fieldPCCreate(int arrPC[][size]){

	int x = 0, y = 0;
	int shipsNUM = 10;
	int deckSize = 4;
	
	// Ships amount
	if (shipsNUM == 10)
		deckSize = 4;
	else if (shipsNUM <= 9 && shipsNUM >= 8)
		deckSize = 3;
	else if (shipsNUM <= 7 && shipsNUM >= 5)
		deckSize = 2;
	else
		deckSize = 1;

	
		// Create PC Ships
		
	

	while (1){

		// Temporary array for checking interferention
		int **arrTemp = new int*[2];
		for (int i = 0; i < 2; i++){
			arrTemp[i] = new int[deckSize];
		}// -------------------------------------------


		x = rand() % 10;
		y = rand() % 10;

		int directX = rand()%2;// 0 or 1
		int direct = rand() % 2;// 0 or 1 
		//cout << "directX= " << directX << "  directY= " << directY << endl;

		for (int i = 0; i < deckSize; i ++){

			if (directX==0)
				if (direct==0)
					arrPC[y-i][x] = 1;
				else 
					arrPC[y + i][x] = 1;
			else
				if (direct == 0)
					arrPC[y][x-i] = 1;
				else
					arrPC[y][x+i] = 1;
		}
		arrPrint(arrPC);
		system("pause");


		// Clear memory of temporary array
		for (int i = 0; i < 2; i++){
			delete arrTemp[i];
		}
		delete[] arrTemp;


	}// end while
	


		
		
	




}// end of procedure

// Check place for ship



// Filling Human Field
void fieldHumanCreate(int arrHum[][size]){

	int arrMask[size][size];// Special array to create Human Battle field	

	// Global while
	int inpt = 0;
	int x = 5, y = 5;
	int rotate = 2;
	int shipsNUM = 10;
	int deckSize = 4;

	// Global While
	while (shipsNUM>0){

		system("cls");
		
		// Ships amount
		if (shipsNUM == 10)
			deckSize = 4;
		else if (shipsNUM <= 9 && shipsNUM >= 8)
			deckSize = 3;
		else if (shipsNUM <= 7 && shipsNUM >= 5)
			deckSize = 2;
		else
			deckSize = 1;
		

		// Movement Direction
		if (inpt == 32){// rotate ship			
			if (x+deckSize<=size && y+deckSize<=size)
			rotate++;			
		}
		if (inpt == 77 ){// move right			
			if (rotate % 2 != 0 && x + deckSize < size)
				x++;
			else if (rotate % 2 == 0 && x < size - 1)
				x++;			
		}
		if (inpt == 75 && x > 0)// move left
			x--;
		if (inpt == 80 ){// move down
			if (rotate % 2 != 0 && y < size - 1)
				y++;
			else if (rotate % 2 == 0 && y + deckSize < size)
				y++;			
		}
		if (inpt == 72 && y>0)// move up
			y--;

		
		// Temporary array for checking interferention
		int **arrTemp = new int*[2];
		for (int i = 0; i < 2; i++){
			arrTemp[i] = new int[deckSize];
		}// -------------------------------------------


		// Create array for Human field CYCLE
		
		for (int i = 0; i < size; i++){

			for (int j = 0; j < size; j++){
				
					arrMask[i][j]=arrHum[i][j];
				
				// Create decks
				for (int nDeck = 0; nDeck < deckSize; nDeck++){
					if (rotate % 2 == 0){
						arrMask[y + nDeck][x] = 1;
						arrTemp[0][nDeck] = y + nDeck;
						arrTemp[1][nDeck] = x;
					}
					else{
						arrMask[y][x + nDeck] = 1;
						arrTemp[0][nDeck] = y;
						arrTemp[1][nDeck] = x+nDeck;
					}
				}// end for nDeck

					

			}// end for j

		}// end for i -----------------------------------------------------------
		
		// Print fields
		arrPrint(arrMask);
		//cout <<"REAL FIELD"<<endl;
		//arrPrint(arrHum);
				
		// Get button
		inpt = 224;
		while (inpt == 224){
			inpt = _getch();
		}
		if (inpt == 27)
			break;
		
		// Copy Ship position to Human field
		bool funcRes = interferentionCheck(arrHum, arrTemp, deckSize);
		if (inpt == 13 && funcRes){
			for (int i = 0; i < size; i++){
				for (int j = 0; j < size; j++){
					
					if (arrHum[i][j]!=1)
						arrHum[i][j] = arrMask[i][j];										
				}
			}

			shipsNUM--;
		}// end if 
		if (!funcRes && inpt ==13)
			Beep(800, 500);
		//----------------------------------------------------


		// Write -1 ('-') to the field------------------------
		for (int i = 0; i < size; i++){
			for (int j = 0; j < size; j++){
				if (arrHum[i][j] == 1){
					for (int n = i - 1; n <= i + 1; n++){
						for (int k = j - 1; k <= j + 1; k++){
							if (arrHum[n][k] != 1 && n >= 0 && k >= 0 && n < size && k < size)
								arrHum[n][k] = -1;
						}
					}
				}//end of

			}// end for j
		}//end for i----------------------------------------------
		
		
		// Clear memory of temporary array
		for (int i = 0; i < 2; i++){
			delete arrTemp[i];
		}
		delete[] arrTemp;
		

	}// end Global While
	
}// End procedure 

// Return false , when there is shipDecks interferention
bool interferentionCheck(int arr1[][size], int **arr2, int size2){

	for (int i = 0; i < size2; i++){
		if (arr1[arr2[0][i]][arr2[1][i]] == 1 || arr1[arr2[0][i]][arr2[1][i]] == -1)
			return false;
	}
	return true;
}


// Any array print
void arrPrint(int arr[][size]){

	cout << "   a b c d e f g h i j" << endl;
	cout << "   _ _ _ _ _ _ _ _ _ _" << endl;



	for (int i = 0; i < size; i++){

		if (i + 1 <= 9)
			cout << " ";
		cout << i + 1 << "|";

		for (int j = 0; j < size; j++){
			
			if (arr[i][j] == 1)
				cout << char(4) << " ";
			else if (arr[i][j] == -1)
				cout << "-" << " ";
			else
				cout << "+"<< " ";
		}
		cout << "\b|" << endl;

	}
	cout << "  `````````````````````" << endl;
}