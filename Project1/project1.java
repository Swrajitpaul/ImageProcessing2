/**
 * Author: Swrajit Paul
 */

import java.io.*;
import java.util.Scanner;

public class imageProcessing {
	
	static int numRows;
	static int numCols; 
	static int minVal; 
	static int maxVal; 
	static int newMin; 
	static int newMax; 
	
	static int[][] imgInAry;
	static int[][] imgOutAry;
	static int[][] mirrorFramedAry;
	static int[][] tempAry;
    static int[] hist;
    static int[] neighborAry = new int[9];

    static FileInputStream fInput = null;
    static FileOutputStream fOutputone;
    static FileOutputStream fOutputtwo;
    static FileOutputStream fOutputthree;
    
    static Scanner inputfile;
    
    public imageProcessing() {
    	
    } 
    
    public static void loadImage(int[][] arrayA,int[][] arrayB) {
		
		for(int i = 0; i < numRows; i++) {
			
			for(int j = 0; j < numCols; j++) {
				
				arrayA[i][j] = inputfile.nextInt();
			}
		}
		
		for(int i = 0; i < numRows; i++) {
			
			for(int j = 0; j < numCols; j++) {
				
				arrayB[i+1][j+1] = arrayA[i][j];
			}
		}

	}
	
	public static void ComputeHistogram(int[][] imgInAry, int[] hist, int mVal) {
		
		for(int i = 0; i < imgInAry.length; i++) {
			
			for(int j = 0; j < imgInAry[0].length; j++) {
				
				hist[imgInAry[i][j]] += 1;
			
			}
		}
		
	}
	
	public static void printHist(int[] hist) {
		
		PrintStream print = new PrintStream(fOutputone);
		print.println(numRows + " " + numCols + " " + minVal + " " + maxVal);
		
		for(int j = 0; j < hist.length; j++) {
			
			print.println(j + " " + hist[j]);
		
		}
	}

	public static void mirrowFramed (int[][] mirrorFramedAry) {
		// java automatically initializes everything to zero
	}

	public static void computeAVG3X3 (int[][] mirrorFramedAry,int[][] tempAry) {// see algorithm below
		
		newMin = Integer.MAX_VALUE;
		newMax = 0;
		
		for(int i = 1; i < mirrorFramedAry.length-1; i++) {
			
			for(int j = 1; j < mirrorFramedAry[0].length-1; j++) {
				
				neighborAry[0] = mirrorFramedAry[i-1][j-1];
				neighborAry[1] = mirrorFramedAry[i-1][j];
				neighborAry[2] = mirrorFramedAry[i-1][j+1];
				neighborAry[3] = mirrorFramedAry[i][j-1];
				neighborAry[4] = mirrorFramedAry[i][j];
				neighborAry[5] = mirrorFramedAry[i][j+1];
				neighborAry[6] = mirrorFramedAry[i+1][j-1];
				neighborAry[7] = mirrorFramedAry[i+1][j];
				neighborAry[8] = mirrorFramedAry[i+1][j+1];
				
				int sum =0;
				
				for (int k =0; k < neighborAry.length; k++) {
					sum += neighborAry[k];
				}
				
				int avg = sum / 9;
				
				tempAry[i][j] = avg;
				
				if (avg <= newMin) {
					newMin = avg;
				}
				if (avg >= newMax) {
					newMax = avg;
				}
				
			}
		}
	}
	
	public static void computThreshold (int[][] tempAry, int[][] imgOutAry, int thr_value) {
		
		for(int i = 1; i < tempAry.length-1; i++) {
			
			for(int j = 1; j < tempAry[0].length-1; j++) {
				
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

	public static void prettyPrint (int[][] imgOutAry) {
		
		PrintStream print = new PrintStream(fOutputthree);
		print.println(numRows + " " + numCols + " " + minVal + " " + maxVal);
		
		for(int i = 1; i < imgOutAry.length-1; i++) {
			
			for(int j = 1; j < imgOutAry[0].length-1; j++) {
				
				if(imgOutAry[i][j] > 0) {
					print.print(imgOutAry[i][j]);
				}
				else {
					print.print(" ");
				}
			}
			print.println();
		}
	}
	
	public static void main(String[] args) {
		
		int thr_Value = 0;
		try {
			
			String inputone = args[0];
			thr_Value = Integer.parseInt(args[1]);
			String outputone = args[2];
			String outputtwo = args[3];
			String outputthree = args[4];
			
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
		
		imgInAry = new int[numRows][numCols];
		imgOutAry = new int[numRows][numCols];
		mirrorFramedAry = new int[numRows+2][numCols+2];;
		tempAry = new int[numRows+2][numCols+2];
		hist = new int[maxVal+1];
		
		loadImage(imgInAry, mirrorFramedAry);
		ComputeHistogram(imgInAry, hist, maxVal);
		printHist(hist);
		mirrowFramed (mirrorFramedAry);
		computeAVG3X3 (mirrorFramedAry,  tempAry);
		computThreshold (tempAry, imgOutAry, thr_Value);
		prettyPrint (imgOutAry);

		PrintStream print = new PrintStream(fOutputtwo);
		print.println(numRows + " " + numCols + " " + minVal + " " + maxVal);
		
		for(int i = 1; i < tempAry.length-1; i++) {
			for(int j = 1; j < tempAry[0].length-1; j++) {
				print.print(tempAry[i][j]);
			}
			print.println();
		} // writing to outputfile
		
		inputfile.close();
		try {
			fInput.close();
		} catch (IOException e) {
			
			e.printStackTrace();
		}
	}
	
}
	
	
	

