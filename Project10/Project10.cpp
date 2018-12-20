// Author: Swrajit Paul

#include <iostream>
#include <fstream>

using namespace std;

ifstream inFile;
ifstream inFiletwo;
ofstream outFile;

class morphology {
	
	public:
		
		int numRowsImg;
		int numColsImg; 
		int minImg; 
		int maxImg; 
	
	  	int numRowsStructElem; 
		int numColsStructElem; 
		int minStrctElem; 
		int maxStrctElem; 
	
		int rowOrigin; 
		int colOrigin; 
	
		int rowFrameSize; 
		int colFrameSize; 
	
		int** imgAry; // a 2D array, to store the input image, 
				// needs to dynamically allocate at run time
				// of size numRowsImg + rowFrameSize by numColsImg + colFrameSize.
		
		int** morphAry; // a 2D array, need to dynamically allocate at run time
				// of size numRowsImg + rowFrameSize by numColsImg + colFrameSize.		
	   	int** structElemAry; //a 2D array, need to dynamically allocate at run time
				// of size numRowsStructElem by numColsStructElem.
		char choice;


	    
	    morphology() {
	    	
			inFile >> numRowsImg;
			inFile >> numColsImg; 
			inFile >> minImg; 
			inFile >> maxImg;;
			
			inFiletwo >> numRowsStructElem; 
			inFiletwo >> numColsStructElem; 
			inFiletwo >> minStrctElem; 
			inFiletwo >> maxStrctElem;
  			
  			inFiletwo >> rowOrigin; 
			inFiletwo >> colOrigin; 
			
	    } 
	    
	    void computeFrameSize(){
	    	rowFrameSize = numRowsStructElem; 
			colFrameSize = numColsStructElem; 

		}
	    
	    void loadImage(int** FramedAry) {
			// reads line by line from the input into zeroFramedAry
			for(int i = rowFrameSize/2; i < numRowsImg + rowFrameSize/2; i++) {
				for(int j = colFrameSize/2; j < numColsImg + colFrameSize/2; j++) {
					inFile >> FramedAry[i][j];
				} 
			}
		}
		
		 void loadstruct(int** FramedAry) {
			// reads line by line from the input into zeroFramedAry
			for(int i = 0; i < numRowsStructElem; i++) {
				for(int j = 0; j < numColsStructElem; j++) {
					inFiletwo >> FramedAry[i][j]; } }

		}
		
		void zeroFrameImg(int** FramedAry) {
			for(int j = 0; j < numColsImg + colFrameSize; j++) {
				FramedAry[0][j] = 0;
				FramedAry[numRowsImg + rowFrameSize+1][j] = 0; }
			
			for(int j = 0; j < numRowsImg + rowFrameSize; j++) {
				FramedAry[j][0] = 0;
				FramedAry[j][numColsImg + colFrameSize] = 0; }
		}
		
		
		char consoleRequest() {
			char c;
			cout << "D for dilation" << endl;
			cout << "E for erosion" << endl;
			cout << "C for closing" << endl;
			cout << "O for opening" << endl;
			cout << "Q for quit" << endl;
			cin >> c;
			return c;
		}
		
		void dilation() {
			for(int i = rowFrameSize/2; i < numRowsImg + rowFrameSize/2; i++) {
				for(int j = colFrameSize/2; j < numColsImg + colFrameSize/2; j++) {
					if(imgAry[i][j] > 0){
						for(int r = 0, m = i-rowOrigin; r < rowFrameSize , m < i+2; r++, m++){
							for(int c = 0, n = j-colOrigin; c < colFrameSize, n < j+2; c++, n++){
								if(structElemAry[r][c]	== 1) {
									morphAry[m][n] = 1;
								}
							}
						}	
					}
				}
			}
		}
		
		void erosion() {
			for(int i = rowFrameSize/2; i < numRowsImg + rowFrameSize/2; i++) {
				for(int j = colFrameSize/2; j < numColsImg + colFrameSize/2; j++) {
					if(imgAry[i][j] > 0){
						bool flag = true;
						for(int r = 0, m = i-rowOrigin; r < rowFrameSize , m < i+2; r++, m++){
							for(int c = 0, n = j-colOrigin; c < colFrameSize, n < j+2; c++, n++){
								if(structElemAry[r][c]	== 1) {
									if(imgAry[m][n] != 1) {
										goto done;
									}
									else {
										continue;
									}
								}
							}
						}
						morphAry[i][j] = 1;	
					}
					done: ;
				}
			}
		}
	
		void closing() {
			for(int i = rowFrameSize/2; i < numRowsImg + rowFrameSize/2; i++) {
				for(int j = colFrameSize/2; j < numColsImg + colFrameSize/2; j++) {
					if(imgAry[i][j] > 0){
						for(int r = 0, m = i-rowOrigin; r < rowFrameSize , m < i+2; r++, m++){
							for(int c = 0, n = j-colOrigin; c < colFrameSize, n < j+2; c++, n++){
								if(structElemAry[r][c]	== 1) {
									morphAry[m][n] = 1;
								}
							}
						}	
					}
				}
			}
			
			for(int i = rowFrameSize/2; i < numRowsImg + rowFrameSize/2; i++) {
				for(int j = colFrameSize/2; j < numColsImg + colFrameSize/2; j++) {
					if(morphAry[i][j] > 0){
						bool flag = true;
						for(int r = 0, m = i-rowOrigin; r < rowFrameSize , m < i+2; r++, m++){
							for(int c = 0, n = j-colOrigin; c < colFrameSize, n < j+2; c++, n++){
								if(structElemAry[r][c]	== 1) {
									if(morphAry[m][n] != 1) {
										goto done;
									}
									else {
										continue;
									}
								}
							}
						}
						for(int r = 0, m = i-rowOrigin; r < rowFrameSize , m < i+2; r++, m++){
							for(int c = 0, n = j-colOrigin; c < colFrameSize, n < j+2; c++, n++){
								if(structElemAry[r][c]	== 1) {
									if(m == i && n== j) {
										continue;
									}
									else {
										morphAry[m][n] = 0;
									}
								}
							}
						}
					}
					done: ;
				}
			}
		}	
		
		void opening() {
			for(int i = rowFrameSize/2; i < numRowsImg + rowFrameSize/2; i++) {
				for(int j = colFrameSize/2; j < numColsImg + colFrameSize/2; j++) {
					if(imgAry[i][j] > 0){
						bool flag = true;
						for(int r = 0, m = i-rowOrigin; r < rowFrameSize , m < i+2; r++, m++){
							for(int c = 0, n = j-colOrigin; c < colFrameSize, n < j+2; c++, n++){
								if(structElemAry[r][c]	== 1) {
									if(imgAry[m][n] != 1) {
										goto done;
									}
									else {
										continue;
									}
								}
							}
						}
						morphAry[i][j] = 1;	
					}
					done: ;
				}
			}
			
			int** tempAry;
			tempAry  = new int*[numRowsImg + rowFrameSize+2];
			for(int i = 0; i < numRowsImg + rowFrameSize+2; i++){
				tempAry[i] = new int[numColsImg + colFrameSize+2]; }
			for(int i = rowFrameSize/2; i < numRowsImg + rowFrameSize/2; i++) {
				for(int j = colFrameSize/2; j < numColsImg + colFrameSize/2; j++) {
					tempAry[i][j] = morphAry[i][j];
				} 
			}
			for(int i = rowFrameSize/2; i < numRowsImg + rowFrameSize/2; i++) {
				for(int j = colFrameSize/2; j < numColsImg + colFrameSize/2; j++) {
					if(tempAry[i][j] > 0){
						for(int r = 0, m = i-rowOrigin; r < rowFrameSize , m < i+2; r++, m++){
							for(int c = 0, n = j-colOrigin; c < colFrameSize, n < j+2; c++, n++){
								if(structElemAry[r][c]	== 1) {
									morphAry[m][n] = 1;
								}
							}
						}	
					}
				}
			}
			
			
		}
		
	
		void consolePrettyPrint (int** imgOutAry) {
			if (imgOutAry == imgAry){
				cout << "Image Array" << endl;
				for(int i = rowFrameSize/2; i < numRowsImg + rowFrameSize/2; i++) {
					for(int j = colFrameSize/2; j < numColsImg + colFrameSize/2; j++) {
						cout << imgAry[i][j];
					} 
					cout << endl;
				}	
				cout << endl;
			}
			
			else if(imgOutAry == structElemAry){
				cout << "Structural Element Array" << endl;
				for(int i = 0; i < numRowsStructElem; i++) {
					for(int j = 0; j < numColsStructElem; j++) {
						cout << structElemAry[i][j]; 
					} 
					cout << endl;
				}
				cout << endl;
			}
			
			else {
				for(int i = rowFrameSize/2; i < numRowsImg + rowFrameSize/2; i++) {
					for(int j = colFrameSize/2; j < numColsImg + colFrameSize/2; j++) {
						cout << morphAry[i][j];
					} 
					cout << endl;
				}	
				cout << endl;
			}
		}
		
		void outFilePrettyPrint (int** imgOutAry) {
			outFile << numRowsImg << " " << numColsImg << " " << minImg << " " << maxImg << endl;
			for(int i = rowFrameSize/2; i < numRowsImg + rowFrameSize/2; i++) {
				for(int j = colFrameSize/2; j < numColsImg + colFrameSize/2; j++) {
					outFile << imgOutAry[i][j];
				} 
				outFile << endl;
			}
			outFile << endl;
		}
		
		void zeroOut(){
			for(int i = rowFrameSize/2; i < numRowsImg + rowFrameSize/2; i++) {
				for(int j = colFrameSize/2; j < numColsImg + colFrameSize/2; j++) {
					morphAry[i][j] = 0;
				} 
			}
		}
		
		void transfer(){
			for(int i = rowFrameSize/2; i < numRowsImg + rowFrameSize/2; i++) {
				for(int j = colFrameSize/2; j < numColsImg + colFrameSize/2; j++) {
					imgAry[i][j] = morphAry[i][j];
				} 
			}
		}
};

int main(int argc, char *argv[]){
	
	inFile.open(argv[1]);
	
	inFiletwo.open(argv[2]);
	
	outFile.open(argv[3]);
	
	morphology morp;
	
	morp.computeFrameSize();
	
	morp.imgAry  = new int*[morp.numRowsImg + morp.rowFrameSize+2];
	for(int i = 0; i < morp.numRowsImg + morp.rowFrameSize+2; i++){
		morp.imgAry[i] = new int[morp.numColsImg + morp.colFrameSize+2]; }// set up the array with proper rows and cols
	for(int i = 0; i < morp.numRowsImg + morp.rowFrameSize+2; i++) {
		for(int j = 0; j < morp.numColsImg + morp.colFrameSize+2; j++) {
			morp.imgAry[i][j] = 0; } }// initialize the array
		
	morp.loadImage(morp.imgAry);
	morp.zeroFrameImg(morp.imgAry);
	morp.consolePrettyPrint(morp.imgAry);
	
	morp.morphAry  = new int*[morp.numRowsImg + morp.rowFrameSize+2];
	for(int i = 0; i < morp.numRowsImg + morp.rowFrameSize+2; i++){
		morp.morphAry[i] = new int[morp.numColsImg + morp.colFrameSize+2]; }// set up the array with proper rows and cols
	for(int i = 0; i < morp.numRowsImg + morp.rowFrameSize; i++) {
		for(int j = 0; j < morp.numColsImg + morp.colFrameSize+2; j++) {
			morp.morphAry[i][j] = 0; } }// initialize the array
			
	morp.structElemAry  = new int*[morp.numRowsStructElem];
	for(int i = 0; i < morp.numRowsStructElem; i++){
		morp.structElemAry[i] = new int[morp.numColsStructElem]; }// set up the array with proper rows and cols
	for(int i = 0; i < morp.numRowsStructElem; i++) {
		for(int j = 0; j < morp.numColsStructElem; j++) {
			morp.structElemAry[i][j] = 0; } }// initialize the array

	morp.loadstruct(morp.structElemAry);
	morp.consolePrettyPrint(morp.structElemAry);
	
	
	char c = morp.choice;
	while (c != 'Q'){
		c = morp.consoleRequest();
		switch (c) { 
		    case 'D' : 	morp.dilation();
		    			cout << "Morph Array after dilation" << endl;
		    			outFile << "Morph Array after dilation" << endl;
		    			morp.consolePrettyPrint(morp.morphAry);
						morp.outFilePrettyPrint(morp.morphAry);
		    			break;
	     	case 'E' : 	morp.erosion();
	     				cout << "Morph Array after erosion" << endl;
	     				outFile << "Morph Array after erosion" << endl;
	     				morp.consolePrettyPrint(morp.morphAry);
						morp.outFilePrettyPrint(morp.morphAry);
						break;
            case 'O' : 	morp.opening();
            			cout << "Morph Array after opening" << endl;
            			outFile << "Morph Array after opening" << endl;
						morp.consolePrettyPrint(morp.morphAry);
						morp.outFilePrettyPrint(morp.morphAry);
						break; 
			case 'C' : 	morp.closing();
						cout << "Morph Array after closing" << endl;
						outFile << "Morph Array after closing" << endl;
						morp.consolePrettyPrint(morp.morphAry);
						morp.outFilePrettyPrint(morp.morphAry);
						break;
            case 'Q' : break;
			default : cout << "The input is either not one of choices OR the input choice is not captialized" << endl; 
						break;
		} 
		if(c == 'Q'){
			morp.zeroOut();
		}
		else if(c == 'D' || c == 'E' || c == 'O' || c == 'C'){
			morp.transfer();
			morp.zeroOut();
		}
	}
	
	inFile.close();
	outFile.close();
	inFiletwo.close();
	return 0;
}
	
