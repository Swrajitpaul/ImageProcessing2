/**
 * Project 3
 * Author: Swrajit Paul
 */

import java.io.*;
import java.util.Scanner;

class Property {
	
	int label;
	int numPixels;
	int minRow;
	int minCol;
	int maxRow;
	int maxCol;
	
	Property(){
		
	}
}

public class Project3 {
	
	static int numRows;
	static int numCols; 
	static int minVal; 
	static int maxVal; 
	static int newMin; 
	static int newMax; 
	
	static int newLabel = 0;
	
	static int[][] zeroFramedAry;
	static int[] EQAry;
    static int[] neighborAry = new int[4];
    static Property[] cc;
    
    static FileInputStream fInput = null;
    static FileOutputStream fOutputone;
    static FileOutputStream fOutputtwo;
    static FileOutputStream fOutputthree;
    
    static Scanner inputfile;
    
    public Project3() {
    	
    } 
    
    public static void loadImage(int[][] arrayB) {
		
		for(int i = 1; i < numRows+1; i++) {
			
			for(int j = 1; j < numCols+1; j++) {
				
				arrayB[i][j] = inputfile.nextInt();
			}
		}

	}
	
	public static void zeroFrame(int[][] array) {
		// java initializes array with 0, therefore this is redundant
	}
	
	public static void loadNeighbors(int i, int j) {
		for(int k = 0; k < neighborAry.length; k++) {
			neighborAry[k] = 0;
		}
		
		neighborAry[0] = zeroFramedAry[i-1][j];
		neighborAry[1] = zeroFramedAry[i][j-1];
		neighborAry[2] = zeroFramedAry[i+1][j];
		neighborAry[3] = zeroFramedAry[i][j+1];
	}
	
	public static void ConnectCC_Pass1() {
		
		for(int i = 1; i < numRows+1; i++) {
			
			for(int j = 1; j < numCols+1; j++) {
				
				if (zeroFramedAry[i][j] > 0) {
					
					loadNeighbors(i,j);
					
					// Case 1
					if (neighborAry[0] == 0 && neighborAry[1] == 0){
						zeroFramedAry[i][j] = ++newLabel;
					}
					
					// Case 2
					else if (neighborAry[0] != 0 && neighborAry[1] != 0 && neighborAry[0] == neighborAry[1]){
						zeroFramedAry[i][j] = neighborAry[0];
					}
					
					// Case 3
					else if (neighborAry[0] != 0 || neighborAry[1] != 0){
						if (neighborAry[0] == 0 && neighborAry[1] != 0){
							zeroFramedAry[i][j] = neighborAry[1];
						}
						if (neighborAry[0] != 0 && neighborAry[1] == 0){
							zeroFramedAry[i][j] = neighborAry[0];
						}
						if (neighborAry[0] != 0 && neighborAry[1] != 0){
							if (neighborAry[0] < neighborAry[1] ){
								zeroFramedAry[i][j] = neighborAry[0];
								updateEQAry(neighborAry[1],neighborAry[0]);
							}
							if (neighborAry[0] > neighborAry[1] ){
								zeroFramedAry[i][j] = neighborAry[1];
								updateEQAry(neighborAry[0], neighborAry[1]);
							}
						}
					}
				}
			}
		}
		
	}
	
	public static void ConnectCC_Pass2() {
		
		for(int i = numRows+1; i>= 1; i--) {
			
			for(int j = numCols+1; j >= 1; j--) {
				
				if (zeroFramedAry[i][j] > 0){
					
					loadNeighbors(i,j);
					
					// Case 1
					// DO nothing
					
					// Case 2
					if ((neighborAry[2] != 0 && neighborAry[3] != 0) && (neighborAry[2] == neighborAry[3])){
						zeroFramedAry[i][j] = neighborAry[2];
					}
					
					// Case 3
					else if (neighborAry[2] != 0 || neighborAry[3] != 0){
						if (neighborAry[2] == 0 && neighborAry[3] != 0){
							zeroFramedAry[i][j] = neighborAry[3];
						}
						if (neighborAry[2] != 0 && neighborAry[3] == 0){
							zeroFramedAry[i][j] = neighborAry[2];
						}
						if (neighborAry[2] != 0 && neighborAry[3] != 0){
							if (neighborAry[2] < neighborAry[3] ){
								zeroFramedAry[i][j] = neighborAry[2];
								updateEQAry(neighborAry[3],neighborAry[2]);
							}
							if (neighborAry[2] > neighborAry[3] ){
								zeroFramedAry[i][j] = neighborAry[3];
								updateEQAry(neighborAry[2],neighborAry[3]);
							}
						}
					}
				}
			} // end of inner loop
		} // end of outer loop
	
	}
	
	public static void ConnectCC_Pass3() {
		
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
		
		PrintStream print = new PrintStream(fOutputtwo);
		print.println(numRows + " " + numCols + " " + newMin + " " + newMax + " ");
		for(int i = 1; i < numRows+1; i++) {
		
			for(int j = 1; j < numCols+1; j++) {
				
				if(zeroFramedAry[i][j] < 10){
					print.print(zeroFramedAry[i][j] + "  ");
				}
				else {
					print.print(zeroFramedAry[i][j] + " ");		
				}
		
			}
			print.println();
			
		}
		cc = new Property[newMax+1];
		for(int k = 0; k < newMax+1; k++) {
			cc[k] = new Property();
		}
		
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
	
	public static void updateEQAry(int i, int j) {
		EQAry[i] = j;
	}
	
	public static void manageEQAry() {
		int trueLabel = 0;
		
		int index = 1;
		
		while(index <= newLabel) {
			
			if (EQAry[index] == index) {
				trueLabel++;
				EQAry[index] = trueLabel;
			}
			else
				EQAry[index] = EQAry[EQAry[index]]; 

			index++;
		}
		
	}
	
	public static void printCCProperty() {
		
		PrintStream print = new PrintStream(fOutputthree);
		print.println(numRows + " " + numCols + " " + newMin + " " + newMax);
		print.println(newMax);
		for(int i = 1; i <= newMax; i++) {
			print.println(cc[i].label);
			print.println(cc[i].numPixels);
			print.println(cc[i].minRow + " " + cc[i].minCol);
			print.println(cc[i].maxRow + " " + cc[i].maxCol);
		}
		
	}

	public static void prettyPrint (int pass) {
		
		PrintStream print = new PrintStream(fOutputone);
		if(pass == 1 || pass == 2 || pass == 3) {
			print.println("This is the result of pass " + pass + ":");
			for(int i = 0; i < zeroFramedAry.length; i++) {
				
				for(int j = 0; j < zeroFramedAry[0].length; j++) {
					
					if(zeroFramedAry[i][j] > 0) {
						print.print(zeroFramedAry[i][j]);
					}
					else {
						print.print("  ");
					}
				}
				print.println();
			}
			
			print.println();
			print.println("This is the EQAry after pass " + pass);
			for(int i=0; i <= newLabel; i++) {
				print.println(i + " " + EQAry[i]);
			}
			print.println();
		}
		else {
			print.println("The EQAry after manageEQAry is:");
			for(int k = 0; k <= newLabel; k++){
				print.println(k + " "+ EQAry[k]); 
			}
			print.println();
		}
		
	}
	
	public static void main(String[] args) {
		
		try {
			
			String inputone = args[0];
			String outputone = args[1];
			String outputtwo = args[2];
			String outputthree = args[3];
			
			fInput = new FileInputStream(inputone);
			fOutputone = new FileOutputStream(outputone);
			fOutputtwo = new FileOutputStream(outputtwo);
			fOutputthree = new FileOutputStream(outputthree);
			
		} catch (IOException e) {
			System.out.println("one of the arguments in missing or wrong");
		}
		
		
		inputfile = new Scanner(fInput);
		
		numRows = inputfile.nextInt();
		numCols = inputfile.nextInt();
		minVal = inputfile.nextInt();
		maxVal = inputfile.nextInt();
		
		zeroFramedAry = new int[numRows+2][numCols+2];;
		EQAry = new int[(numRows*numCols)/2];
		for(int i=0; i < EQAry.length; i++) {
			EQAry[i] = i;
		}
		
		loadImage(zeroFramedAry);
		ConnectCC_Pass1();
		prettyPrint(1);
		ConnectCC_Pass2();
		prettyPrint(2);
		manageEQAry();
		prettyPrint(4);
		ConnectCC_Pass3();
		prettyPrint(3);
		printCCProperty();
		
		
		inputfile.close();
		try {
			fInput.close();
		} catch (IOException e) {
			
			e.printStackTrace();
		}
	}
	
}
	
	
	

