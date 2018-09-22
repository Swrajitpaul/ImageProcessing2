// Author: Swrajit Paul

#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

ifstream inFile;
ofstream outFile;
ofstream outFiletwo;
ofstream outFilethree;

class imageProcessing {
	
	public:
		
		int numRows;
		int numCols; 
		int minVal; 
		int maxVal; 
		int newMin; 
		int newMax; 
			
		int thr_value;
		int** imgInAry;
		int** imgOutAry;
		int** mirrorFramedAry;
		int** tempAry;
	    int* hist;
	    int neighborAry[9];

	    imageProcessing(string in, string intwo, string out, string outtwo, string outthree) {
	    	
	    	inFile.open(in.c_str());
  			
  			stringstream s(intwo);
  			s >> thr_value;
  			s.clear();
			outFile.open(out.c_str());
  			
			outFiletwo.open(outtwo.c_str());
			
			outFilethree.open(outthree.c_str());
  			
			inFile >> numRows;
			inFile >> numCols; 
			inFile >> minVal; 
			inFile >> maxVal;
			
			
			imgInAry = new int*[numRows];
			for(int i = 0; i < numRows; i++){
				imgInAry[i] = new int[numCols];
			} // set up the array with proper rows and cols
			for(int i = 0; i < numRows; i++) {
				for(int j = 0; j < numCols; j++) {
					imgInAry[i][j] = 0;
				}
			}// initialize the array
			
			imgOutAry = new int*[numRows];
			for(int i = 0; i < numRows; i++){
				imgOutAry[i] = new int[numCols];
			}// set up the array with proper rows and cols
			for(int i = 0; i < numRows; i++) {
				for(int j = 0; j < numCols; j++) {
					imgOutAry[i][j] = 0;
				}
			}// initialize the array
			
			mirrorFramedAry = new int*[numRows+2];
			for(int i = 0; i < numRows+2; i++){
				mirrorFramedAry[i] = new int[numCols+2];
			}// set up the array with proper rows and cols
			for(int i = 0; i < numRows+2; i++) {
				for(int j = 0; j < numCols+2; j++) {
					mirrorFramedAry[i][j] = 0;
				}
			}// initialize the array
			
			tempAry = new int*[numRows+2];
			for(int i = 0; i < numRows+2; i++){
				tempAry[i] = new int[numCols+2];
			}// set up the array with proper rows and cols
			for(int i = 0; i < numRows+2; i++) {
				for(int j = 0; j < numCols+2; j++) {
					tempAry[i][j] = 0;
				}
			}// initialize the array
			
			hist = new int[maxVal+1];
			for(int j = 0; j < maxVal+1; j++) {
				hist[j] =0;
			}
			
			
	    } 
	    
	    void loadImage(int** imgInAry, int** mirrorFramedAry) {
			
			for(int i = 0; i < numRows; i++) {
				
				for(int j = 0; j < numCols; j++) {
					
					inFile >> imgInAry[i][j];
					
				}
			}
			

			for(int i = 0; i < numRows; i++) {
				
				for(int j = 0; j < numCols; j++) {
					
					mirrorFramedAry[i+1][j+1] = imgInAry[i][j];
					
				}
				
			}
			
		}
		
		void ComputeHistogram(int** imgInAry, int* hist, int mVal) {
			
			for(int i = 0; i < numRows; i++) {
				
				for(int j = 0; j < numCols; j++) {
					
					hist[imgInAry[i][j]] += 1;
					
				}
			}
			
			
			
		}
		
		void printHist(int* hist) {
			
			outFile << numRows << " " << numCols << " " << minVal << " " << maxVal << endl;
			
			for(int j = 0; j < maxVal+1; j++) {
				
				outFile << j << " " << hist[j] << endl;
			
			}
			
			outFile.close();
		}
	
		void mirrowFramed (int** mirrorFramedAry) {
			
			for(int j = 0; j < numCols+2; j++) {
					
				mirrorFramedAry[0][j] = 0;
				mirrorFramedAry[numRows+1][j] = 0;
					
			}
			
			for(int j = 0; j < numRows+2; j++) {
					
				mirrorFramedAry[j][0] = 0;
				mirrorFramedAry[j][numCols+1] = 0;
					
			}
				
			
		}
	
		void computeAVG3X3 (int** mirrorFramedAryw,int** tempAryw) {
			
			newMin = 20000000;
			newMax = 0;
			
			for(int i = 1; i < numRows+1; i++) {
				
				for(int j = 1; j < numCols+1 ; j++) {
					
					neighborAry[0] = mirrorFramedAryw[i-1][j-1];
					neighborAry[1] = mirrorFramedAryw[i-1][j];
					neighborAry[2] = mirrorFramedAryw[i-1][j+1];
					neighborAry[3] = mirrorFramedAryw[i][j-1];
					neighborAry[4] = mirrorFramedAryw[i][j];
					neighborAry[5] = mirrorFramedAryw[i][j+1];
					neighborAry[6] = mirrorFramedAryw[i+1][j-1];
					neighborAry[7] = mirrorFramedAryw[i+1][j];
					neighborAry[8] = mirrorFramedAryw[i+1][j+1];
					
					
					
					int sum =0;
					
					for (int k =0; k < 9; k++) {
						sum += neighborAry[k];
					}
					
					int avg = sum / 9;
					
					tempAryw[i][j] = avg;
					
					if (avg <= newMin) {
						newMin = avg;
					}
					if (avg >= newMax) {
						newMax = avg;
					}
					
				}
				
			}
					
		}
		
		void computeMEDIAN3X3 (int** mirrorFramedAryw,int** tempAryw) {
			
			newMin = 20000000;
			newMax = 0;
			
			for(int i = 1; i < numRows+1; i++) {
				
				for(int j = 1; j < numCols+1 ; j++) {
					
					neighborAry[0] = mirrorFramedAryw[i-1][j-1];
					neighborAry[1] = mirrorFramedAryw[i-1][j];
					neighborAry[2] = mirrorFramedAryw[i-1][j+1];
					neighborAry[3] = mirrorFramedAryw[i][j-1];
					neighborAry[4] = mirrorFramedAryw[i][j];
					neighborAry[5] = mirrorFramedAryw[i][j+1];
					neighborAry[6] = mirrorFramedAryw[i+1][j-1];
					neighborAry[7] = mirrorFramedAryw[i+1][j];
					neighborAry[8] = mirrorFramedAryw[i+1][j+1];
					
					sort(neighborAry);
					tempAryw[i][j] = neighborAry[4];
					
					
					if (neighborAry[4] <= newMin) {
						newMin = neighborAry[4];
					}
					if (neighborAry[4] >= newMax) {
						newMax = neighborAry[4];
					}
					
				}
				
			}
					
		}
		
		void sort(int array[]){
			int i, j;
			for (i =0; i < 9; i++){
				for(j =0; j < 9-i-1; j++){
					if(array[j] > array[j+1]){
						int temp = array[j];
						array[j] = array[j+1];
						array[j+1] = temp;
					}
				}
			}
		}
		
		void computeThreshold (int** tempAry, int** imgOutAry, int thr_value) {
			
			
			for(int i = 1; i < numRows+1; i++) {
				
				for(int j = 1; j < numCols+1; j++) {
					
					int pixel = tempAry[i][j];
					
					if(pixel >= thr_value) {
						imgOutAry[i-1][j-1] = 1;
					}
					else {
						imgOutAry[i-1][j-1]= 0;
					}
					
				}
			}
			
		}
	
		void prettyPrint (int** imgOutAryw) {
			
			outFilethree << numRows << " " << numCols << " " << minVal << " " << maxVal << endl;
			
			for(int i = 0; i < numRows; i++) {
				
				for(int j = 0; j < numCols; j++) {
					
					if(imgInAry[i][j] > 0) {
						outFilethree << imgOutAryw[i][j] << " " ;
					}
					else {
						outFilethree << " ";
					}
				}
				outFilethree << endl;
			}
		}
		
	
};

int main(int argc, char *argv[]) {
		
	imageProcessing img (argv[1],argv[2],argv[3],argv[4],argv[5]);
	
	int whichMethod = 0;
	while(true){
		cout << "which method would you like to use?" << endl;
		cout << "enter 1 for average filter or enter 2 for median filter" << endl;
		cin >> whichMethod;
		
		if (whichMethod == 1 || whichMethod == 2){
			break;
		}
		else{
			cout << "please re-enter!" << endl;
		}
	}
	
	img.loadImage(img.imgInAry, img.mirrorFramedAry);
	
	img.ComputeHistogram(img.imgInAry, img.hist, img.maxVal);
			
	img.printHist(img.hist);
	
	img.mirrowFramed(img.mirrorFramedAry);
	
	if(whichMethod == 1){
		img.computeAVG3X3(img.mirrorFramedAry, img.tempAry);	
	}
	else if(whichMethod == 2){
		img.computeMEDIAN3X3(img.mirrorFramedAry, img.tempAry);	
	}
	else if(whichMethod >= 3 || whichMethod <= 0){
		return 0;	
	}
	
	img.computeThreshold (img.tempAry, img.imgOutAry, img.thr_value);
	
	img.prettyPrint (img.imgOutAry);
	
	outFiletwo << img.numRows << " " << img.numCols << " " << img.minVal << " " << img.maxVal << endl;
			
	for(int i = 0; i < img.numRows; i++) {
		
		for(int j = 0; j < img.numCols; j++) {
			
			if(img.tempAry[i][j] > 0) {
				outFiletwo << img.tempAry[i][j] << " ";
			}
			else {
				outFiletwo << " ";
			}
		}
		outFiletwo << endl;
	}
	
	return 0;
}

	
	
	


