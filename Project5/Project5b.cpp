// Author: Swrajit Paul

#include <iostream>
#include <fstream>

using namespace std;

ifstream inFile;
ofstream outFile;
ofstream outFiletwo;

class imageProcessing {
	
	public:
		
		int numRows;
		int numCols; 
		int minVal; 
		int maxVal; 			
		int** deCompressedAry;
	
	    imageProcessing(string in, string out, string outtwo) {
	    	
	    	inFile.open(in.c_str());
			outFile.open(out.c_str());
			outFiletwo.open(outtwo.c_str());
			inFile >> numRows;
			inFile >> numCols; 
			inFile >> minVal; 
			inFile >> maxVal;
			
			deCompressedAry = new int*[numRows+2];
			for(int i = 0; i < numRows+2; i++){
				deCompressedAry[i] = new int[numCols+2]; }// set up the array with proper rows and cols
			for(int i = 0; i < numRows+2; i++) {
				for(int j = 0; j < numCols+2; j++) {
					deCompressedAry[i][j] = 0; } }// initialize the array
			
			outFile << numRows << " " << numCols << " " << minVal << " " << maxVal << endl;
	    	
	    	int row, col;
	    	while (!inFile.eof()){
	    		inFile >> row;
	    		inFile >> col;
	    		inFile >> deCompressedAry[row][col];
			}
	    	
		}
		 
		int max(int a, int b){
			if (a>b){
				return a;
			}
			else if(b>a){
				return b;
			}
			else{
				return a;
			}
		}
		
		void fistPass_deCompress (int** imgAry){	
			for(int i = 1; i < numRows+1; i++) {
				for(int j = 1; j < numCols+1; j++) {
					if (imgAry[i][j] == 0){
						if(max(imgAry[i-1][j], imgAry[i][j-1]) > 0){
							imgAry[i][j] = max(imgAry[i-1][j], imgAry[i][j-1]) -1;
						}
					} 
				} 
			}
		}  
		
		void secondPass_deCompress (int** imgAry){	
			for(int i = numRows; i > 0; i--) {
				for(int j = numCols; j > 0; j--) {
					if (imgAry[i][j] < max(imgAry[i+1][j], imgAry[i][j+1])){
						if(max(imgAry[i+1][j], imgAry[i][j+1]) > 1){
							imgAry[i][j] = max(imgAry[i+1][j], imgAry[i][j+1]) -1;
						}
					}	
				}	
			}
		}
		
		void outputDecompressImg (int** imgAry) {
			for(int i = 1; i < numRows+1; i++) {
				for(int j = 1; j < numCols+1; j++) {
					outFile << imgAry[i][j];
				}
				outFile << endl;
			}
			outFile << endl;
		}
		
		void prettyPrint (int** imgAry, string pass) {
			outFiletwo << "the result of " << pass << " decompression";
			for(int i = 1; i < numRows+1; i++) {
				for(int j = 1; j < numCols+1; j++) {
					if (imgAry[i][j] == 0)
						outFiletwo << "  ";
					else {
						if(imgAry[i][j] / 10 == 0)
							outFiletwo << imgAry[i][j] << " ";
						else 
							outFiletwo << imgAry[i][j];
					}
				}
				outFiletwo << endl;
			}
			outFiletwo << endl;
		}
		
};

int main(int argc, char *argv[]) {
		
	imageProcessing img (argv[1],argv[2],argv[3]);
	
	img.fistPass_deCompress(img.deCompressedAry);
	
	img.prettyPrint(img.deCompressedAry, "pass-1");
	
	img.secondPass_deCompress(img.deCompressedAry);
	
	img.prettyPrint(img.deCompressedAry, "pass-2");
	
	img.outputDecompressImg(img.deCompressedAry);
	
	return 0;
}

	
	
