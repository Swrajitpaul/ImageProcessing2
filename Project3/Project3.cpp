// Author: Swrajit Paul

#include <iostream>
#include <fstream>

using namespace std;

ifstream inFile;
ofstream outFile;
ofstream outFiletwo;
ofstream outFilethree;

		
class imageProcessing {
	
	struct Property {
		int label;
		int numPixels;
		int minRow;
		int minCol;
		int maxRow;
		int maxCol;
	};
	
	public:
		
		int numRows;
		int numCols; 
		int minVal; 
		int maxVal; 
		int newMin; 
		int newMax; 
			
		int newLabel = 0;
		int* EQAry;
		int** zeroFramedAry;
	    int NeighborAry[4];
		Property* cc;

	    imageProcessing(string in, string out, string outtwo, string outthree) {
	    	
	    	
	    	inFile.open(in.c_str());
  			
			outFile.open(out.c_str());
  			
			outFiletwo.open(outtwo.c_str());
			
			outFilethree.open(outthree.c_str());
  			
			inFile >> numRows;
			inFile >> numCols; 
			inFile >> minVal; 
			inFile >> maxVal;
			
			
			zeroFramedAry = new int*[numRows+2];
			for(int i = 0; i < numRows+2; i++){
				zeroFramedAry[i] = new int[numCols+2];
			}// set up the array with proper rows and cols
			for(int i = 0; i < numRows+2; i++) {
				for(int j = 0; j < numCols+2; j++) {
					zeroFramedAry[i][j] = 0;
				}
			}// initialize the array
			
			EQAry = new int[((numRows*numCols)/2)];
			for(int i = 0; i < ((numRows*numCols)/2); i++){
				EQAry[i] = i;
			} // set up ary
			
			
	    } 
	    
	    void loadImage(int** FramedAry) {
			// reads line by line from the input into zeroFramedAry
			for(int i = 1; i < numRows+1; i++) {
				
				for(int j = 1; j < numCols+1; j++) {
					
					inFile >> FramedAry[i][j];
				
				}
				
			}
			
		}
		
		
		void zeroFrame(int** FramedAry) {
			
			for(int j = 0; j < numCols+2; j++) {
					
				FramedAry[0][j] = 0;
				FramedAry[numRows+1][j] = 0;
					
			}
			
			for(int j = 0; j < numRows+2; j++) {
					
				FramedAry[j][0] = 0;
				FramedAry[j][numCols+1] = 0;
					
			}
				
			
		}
		
		void loadNeighbors (int i, int j){
			NeighborAry[0] = zeroFramedAry[i-1][j];
			NeighborAry[1] = zeroFramedAry[i][j-1];
			NeighborAry[2] = zeroFramedAry[i+1][j];
			NeighborAry[3] = zeroFramedAry[i][j+1];
		}
	    
		void ConnectCC_Pass1(){
			
			
			for(int i = 1; i < numRows+1; i++) {
				
				for(int j = 1; j < numCols+1; j++) {
					
					if (zeroFramedAry[i][j] > 0){
						loadNeighbors(i, j);
					
						// Case 1
						if (NeighborAry[0] == 0 && NeighborAry[1] == 0){
							zeroFramedAry[i][j] = ++newLabel;
						}
						
						// Case 2
						else if (NeighborAry[0] != 0 && NeighborAry[1] != 0 && NeighborAry[0] == NeighborAry[1]){
							zeroFramedAry[i][j] = NeighborAry[0];
						}
						
						// Case 3
						else if (NeighborAry[0] != 0 || NeighborAry[1] != 0){
							if (NeighborAry[0] == 0 && NeighborAry[1] != 0){
								zeroFramedAry[i][j] = NeighborAry[1];
							}
							if (NeighborAry[0] != 0 && NeighborAry[1] == 0){
								zeroFramedAry[i][j] = NeighborAry[0];
							}
							if (NeighborAry[0] != 0 && NeighborAry[1] != 0){
								if (NeighborAry[0] < NeighborAry[1] ){
									zeroFramedAry[i][j] = NeighborAry[0];
									EQAry[NeighborAry[1]] = NeighborAry[0];
								}
								if (NeighborAry[0] > NeighborAry[1] ){
									zeroFramedAry[i][j] = NeighborAry[1];
									EQAry[NeighborAry[0]] = NeighborAry[1];
								}
							}
						}	
					}
					
				}
				
			}
			
			
			
		}  
	
		void ConnectCC_Pass2(){
			
			for(int i = numRows+1; i > 0; i--) {
				
				for(int j = numCols+1; j > 0; j--) {
					
					if (zeroFramedAry[i][j] > 0){
						loadNeighbors(i, j);
					
						// Case 1
						// Do nothing
						
						// Case 2
						if ((NeighborAry[2] != 0 && NeighborAry[3] != 0) && (NeighborAry[2] == NeighborAry[3])){
							zeroFramedAry[i][j] = NeighborAry[3];
						}
						
						// Case 3
						else if (NeighborAry[2] != 0 || NeighborAry[3] != 0){
							if (NeighborAry[2] == 0 && NeighborAry[3] != 0){
								zeroFramedAry[i][j] = NeighborAry[3];
							}
							if (NeighborAry[2] != 0 && NeighborAry[3] == 0){
								zeroFramedAry[i][j] = NeighborAry[2];
							}
							if (NeighborAry[2] != 0 && NeighborAry[3] != 0){
								if (NeighborAry[2] < NeighborAry[3] ){
									zeroFramedAry[i][j] = NeighborAry[2];
									updateEQAry(NeighborAry[3], NeighborAry[2]);
									EQAry[NeighborAry[3]] = NeighborAry[2];
								}
								if (NeighborAry[2] > NeighborAry[3] ){
									zeroFramedAry[i][j] = NeighborAry[3];
									EQAry[NeighborAry[2]] = NeighborAry[3];
								}
							}
						}	
					}
					
				}
				
			}
			
		}
		
		void ConnectCC_Pass3() { 
			
			for(int i = 1; i < numRows+1; i++) {
			
				for(int j = 1; j < numCols+1; j++) {
					
					if (zeroFramedAry[i][j] > 0) {
						
						zeroFramedAry[i][j] = EQAry[zeroFramedAry[i][j]];
					}
				}
			}
			
			newMin = 200000;
			newMax = 0;
			
			for(int i = 0; i <= newLabel; i++) {
				if(EQAry[i] > newMax){
					newMax = EQAry[i];
				}
				if (EQAry[i] < newMin){
					newMin = EQAry[i];
				}
			}
			outFiletwo << numRows << " " << numCols << " " << newMin << " " << newMax << " " << endl;
			for(int i = 1; i < numRows+1; i++) {
			
				for(int j = 1; j < numCols+1; j++) {
					
					if(zeroFramedAry[i][j] < 10){
						outFiletwo << zeroFramedAry[i][j] << "  ";
					}
					else {
						outFiletwo << zeroFramedAry[i][j] << " ";		
					}
			
				}
				
				outFiletwo << endl;
			}
			cc = new Property[newMax+1];
			
			for(int k = 1; k <= newMax; k++) {
				int countPixels = 0;
				int maxr, maxc, minc, minr;
				maxr = 0;
				maxc = 0;
				minc = numCols;
				minr = numRows;
				for(int i = 1; i < numRows+1; i++) {
			
					for(int j = 1; j < numCols+1; j++) {
						
						if(zeroFramedAry[i][j] == k){
							if(i-1 < minr){
								minr = i-1;
							}
							if(i-1 > maxr){
								maxr = i-1;
							}
							if(j-1 > maxc){
								maxc = j-1;
							}
							if(j-1 < minc){
								minc = j-1;
							}
							countPixels++;
						}
					}
				}
				
				
				cc[k].label = k;
				cc[k].numPixels = countPixels;
				cc[k].minRow = minr;
				cc[k].minCol = minc;
				cc[k].maxRow = maxr;
				cc[k].maxCol = maxc;
				
			}
			
		}
	
		void updateEQAry(int i, int k){
			EQAry[i] = k;
		}
		
		void manageEQAry(int* EQAry){	  // manage the EQAry so to findout true number of connected components..
	    	int trueLabel = 0;
			int index = 1;
			while(index <= newLabel) {
				
				if (EQAry[index] == index) {
					trueLabel++;
					EQAry[index] = trueLabel;
				}
				else{
					EQAry[index] = EQAry[EQAry[index]]; 
				}
	
				index++;
			}
		
		}
		
		void printCCProperty(){ 
			// print the connected components property
			outFilethree << numRows << " " << numCols << " " << newMin << " " << newMax << " " << endl;
			outFilethree << newMax << endl;
			for(int i = 1; i <= newMax; i++) {
				outFilethree << cc[i].label << endl;
				outFilethree << cc[i].numPixels << endl;
				outFilethree << cc[i].minRow << " " << cc[i].minCol << endl;
				outFilethree << cc[i].maxRow << " " << cc[i].maxCol << endl;
			}
		}
		
	    void prettyPrint(int pass){
	    	
	    	
	    	// if pass equals one, two or three
	    	if(pass ==1 || pass == 2 || pass == 3){
	    		outFile << "This is the result of pass " << pass << ":" << endl;
	    		for(int i = 1; i < numRows+1; i++) {
				
					for(int j = 1; j < numCols+1; j++) {
						
						if (zeroFramedAry[i][j] > 0){
							outFile << zeroFramedAry[i][j];	
						}
						
						else {
							outFile << "  ";
						}
						
					}
					outFile << endl;
				}
				
				outFile << endl;
				outFile << "This is the EQAry after pass " << pass << ":" << endl;
				for(int i = 0; i <= newLabel; i++){
					outFile << i << " "<< EQAry[i] <<endl; 
				}	
				outFile << endl;
			}
			
			else {
				outFile << "The EQAry after manageEQAry is:" << endl;
				for(int k = 0; k <= newLabel; k++){
					outFile << k << " "<< EQAry[k] <<endl; 
				}
				outFile << endl;
			}
		}
	
		
};

int main(int argc, char *argv[]) {
		
	imageProcessing img (argv[1],argv[2],argv[3],argv[4]);
	
	img.loadImage(img.zeroFramedAry);
	
	img.ConnectCC_Pass1();
	
	img.prettyPrint(1);
	
	img.ConnectCC_Pass2();
	
	img.prettyPrint(2);
	
	img.manageEQAry(img.EQAry);
	
	img.prettyPrint(4);
	
	img.ConnectCC_Pass3();
	
	img.prettyPrint(3);
	
	img.printCCProperty();

	inFile.close();
	outFile.close();
	outFiletwo.close();
	outFilethree.close();
	return 0;
}

	
	
