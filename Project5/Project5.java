/**
 * Project 5
 * Author: Swrajit Paul
 */

import java.io.*;
import java.util.Scanner;

public class Project5 {
	
	static int numRows;
	static int numCols; 
	static int minVal; 
	static int maxVal; 
	static int newMinVal = 0; 
	static int newMaxVal = 0; 
	static int[][] zeroFramedAry;
	static int[][] skeletonAry;
    
    static FileInputStream fInput = null;
    static FileOutputStream fOutputone;
    static FileOutputStream fOutputtwo;
    static FileOutputStream fOutputthree;
    static FileOutputStream fOutputfour;
    
    static Scanner inputfile;
    
    public Project5() {
    	
    } 
    
    private static void loadImage(int[][] imgAry) {	
		for(int i = 1; i < numRows+1; i++) {
			for(int j = 1; j < numCols+1; j++) {
				imgAry[i][j] = inputfile.nextInt();
			}
		}
	}
	
    private static void zeroFrame(int[][] imgAry) {
		for(int j = 0; j < numCols+2; j++) {
			imgAry[0][j] = 0;
			imgAry[numRows+1][j] = 0; }
		
		for(int j = 0; j < numRows+2; j++) {
			imgAry[j][0] = 0;
			imgAry[j][numCols+1] = 0;
		}
	}
	
    private static void fistPass_4Distance (int[][] imgAry) {
    	for(int i = 1; i < numRows+1; i++) {				
			for(int j = 1; j < numCols+1; j++) {
				if (imgAry[i][j] > 0){
					int[] tempAry = new int[2];
					tempAry[0] = imgAry[i-1][j];
					tempAry[1] = imgAry[i][j-1];
					int min = 20000000;
					
					for(int k =0; k < 2; k++){
						if(tempAry[k] + 1 < min){
						min = tempAry[k] + 1; } }
					
					imgAry[i][j] = min;
				}	
			}
		}
	}
	
    private static void secondPass_4Distance (int[][] imgAry) {
    	for(int i = numRows+1; i > 0; i--) {
			for(int j = numCols+1; j > 0; j--) {
				if (zeroFramedAry[i][j] > 0){
					int[] tempAry = new int[2];
					tempAry[0] = imgAry[i+1][j];
					tempAry[1] = imgAry[i][j+1];
					 
					int min = 20000000;
					 
					for(int k =0; k < 2; k++){
					 	if(tempAry[k] + 1 < min){
					 		min = tempAry[k] + 1;
						}
					} 
					if (imgAry[i][j] > min){
					 
						imgAry[i][j] = min;
					}	
					if(imgAry[i][j] >= newMaxVal){
						newMaxVal = imgAry[i][j];
					}
				}	
			}	
		} 
	}	
			
    private static int is_maxima (int[][] imgAry, int i, int j){
				
    	int[] tempAry = new int[4];
		tempAry[0] = imgAry[i-1][j];
		tempAry[1] = imgAry[i][j-1];
		tempAry[2] = imgAry[i][j+1];
		tempAry[3] = imgAry[i+1][j];
		
		for(int k =0; k < 4; k++){
			if (imgAry[i][j] < tempAry[k]){
				return 0;
			}
		}
	   return 1;
	}
		
    private static void compute_localMaxima(int[][] imgAry, int[][] skAry){
    	PrintStream print = new PrintStream(fOutputthree);
    	for(int i = 1; i < numRows+1; i++) {
			for(int j = 1; j < numCols+1; j++) {
				if (imgAry[i][j] > 0){
					if(is_maxima(imgAry, i,j) ==1){
						skeletonAry[i][j] = 1;
						print.println(i + " " + j + " " + imgAry[i][j]);
					} 
					else{	
						skeletonAry[i][j] = 0;
					}
				}		
			}
		}
	}
			
    private static void outputDistance(int[][] imgAry,  FileOutputStream oFile) { 
    	PrintStream print = new PrintStream(oFile);
    	for(int i = 1; i < numRows+1; i++) {
			for(int j = 1; j < numCols+1; j++) {
				print.print(imgAry[i][j] + " ");
			}
			print.println();
		}
	}
    
    private static void outputSkeleton(int[][] imgAry,  FileOutputStream oFile) { 
    	PrintStream print = new PrintStream(oFile);
    	for(int i = 1; i < numRows+1; i++) {
			for(int j = 1; j < numCols+1; j++) {
				print.print(imgAry[i][j] + " ");
			}
			print.println();
		}
	}
			
    private static void prettyPrintDistance (int[][] imgAry, String pass) {
    	PrintStream print = new PrintStream(fOutputfour);
    	print.println(pass);
		for(int i = 0; i < numRows+1; i++) {
			for(int j = 1; j < numCols+1; j++) {
				if (imgAry[i][j] == 0)
					print.print("   ");
				else {
					if(imgAry[i][j] / 10 == 0)
						print.print(imgAry[i][j] + "  ");
					else 
						print.print(imgAry[i][j] + " ");
				}
			}
			print.println(); 
		}
		print.println();
	}

    private static void prettyPrintSkeleton (int[][] imgAry) {
    	PrintStream print = new PrintStream(fOutputfour);
		for(int i = 1; i < numRows+1; i++) {
			for(int j = 1; j < numCols+1; j++) {
				if (imgAry[i][j] == 0)
					print.print(".");
				else {
					print.print("9");
				}
			}
			print.println(); 
		}
		print.println();
	}
	
	public static void main(String[] args) {
		
		try {
			
			String inputone = args[0];
			String outputone = args[1];
			String outputtwo = args[2];
			String outputthree = args[3];
			String outputfour = args[4];
			fInput = new FileInputStream(inputone);
			fOutputone = new FileOutputStream(outputone);
			fOutputtwo = new FileOutputStream(outputtwo);
			fOutputthree = new FileOutputStream(outputthree);
			fOutputfour = new FileOutputStream(outputfour);
			
		} catch (IOException e) {
			System.out.println("one of the arguments in missing or wrong");
		}
		
		
		inputfile = new Scanner(fInput);
		numRows = inputfile.nextInt();
		numCols = inputfile.nextInt();
		minVal = inputfile.nextInt();
		maxVal = inputfile.nextInt();
		
		zeroFramedAry = new int[numRows+2][numCols+2];
		skeletonAry = new int[numRows+2][numCols+2];
		
		zeroFrame(zeroFramedAry);
		
		loadImage(zeroFramedAry);
		
		fistPass_4Distance (zeroFramedAry);
		
		prettyPrintDistance(zeroFramedAry, "pass-1");
		
		secondPass_4Distance(zeroFramedAry);
		
		prettyPrintDistance(zeroFramedAry, "pass-2");
		
		PrintStream print = new PrintStream(fOutputone);
    	print.println(numRows + " " + numCols + " " + newMinVal + " " + newMaxVal );
    	PrintStream print1 = new PrintStream(fOutputtwo);
    	print1.println(numRows + " " + numCols + " " + newMinVal + " " + newMaxVal );
    	PrintStream print11 = new PrintStream(fOutputthree);
    	print11.println(numRows + " " + numCols + " " + newMinVal + " " + newMaxVal );
		
    	outputDistance(zeroFramedAry, fOutputone);
		compute_localMaxima(zeroFramedAry, skeletonAry);
		outputSkeleton(skeletonAry, fOutputtwo);
		prettyPrintSkeleton(skeletonAry);
		
		inputfile.close();
		try {
			fInput.close();
			fOutputone.close();
			fOutputtwo.close();
			fOutputthree.close();
			fOutputfour.close();
		} catch (IOException e) {
			
			e.printStackTrace();
		}
	}
	
}