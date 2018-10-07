/**
 * Project 3
 * Author: Swrajit Paul
 */

import java.io.*;
import java.util.Scanner;

public class ImageProcessing {
	
	static int numRows;
	static int numCols; 
	static int minVal; 
	static int maxVal; 
	static double newMinVal = 0; 
	static double newMaxVal = 0; 
	static double[][] zeroFramedAry;
	static int[][] skeletonAry;
    
    static FileInputStream fInput = null;
    static FileOutputStream fOutputone;
    static FileOutputStream fOutputtwo;
    static FileOutputStream fOutputthree;
    
    static Scanner inputfile;
    
    public ImageProcessing() {
    	
    } 
    
    private static void loadImage(double[][] arrayB) {	
		for(int i = 1; i < numRows+1; i++) {
			for(int j = 1; j < numCols+1; j++) {
				arrayB[i][j] = inputfile.nextInt();
			}
		}
	}
	
    private static void zeroFrame(double[][] FramedAry) {
		for(int j = 0; j < numCols+2; j++) {
			FramedAry[0][j] = 0;
			FramedAry[numRows+1][j] = 0; }
		
		for(int j = 0; j < numRows+2; j++) {
			FramedAry[j][0] = 0;
			FramedAry[j][numCols+1] = 0;
		}
	}
	
    private static void fistPass_EuclidianDistance (double[][] imgAry) {
		for(int i = 1; i < numRows+1; i++) {
			for(int j = 1; j < numCols+1; j++) {
				if (imgAry[i][j] > 0) {
					double[] tempAry = new double[4];
					tempAry[0] = Double.parseDouble(String.format("%.2f", imgAry[i-1][j-1] + Math.sqrt(2)));
					tempAry[1] = imgAry[i-1][j] + 1;
					tempAry[2] = imgAry[i-1][j+1] + Math.sqrt(2);
					tempAry[3] = imgAry[i][j-1] + 1;
					
					double min = 20000000.0;
					
					for(int k =0; k < 4; k++){
						if(Double.parseDouble(String.format("%.2f", tempAry[k]))  < min){
						min = Double.parseDouble(String.format("%.2f", tempAry[k])); } }
					
					imgAry[i][j] = min;			
				}
			}
		}
	}
	
    private static void secondPass_EuclidianDistance (double[][] imgAry) {
		for(int i = numRows+1; i>= 1; i--) {
			for(int j = numCols+1; j >= 1; j--) {
				if (imgAry[i][j] > 0){
					double []tempAry = new double[4];
					tempAry[0] = imgAry[i][j+1] +1;
					tempAry[1] = imgAry[i+1][j-1] + Math.sqrt(2);
					tempAry[2] = imgAry[i+1][j] +1;
					tempAry[3] = imgAry[i+1][j+1] + Math.sqrt(2);
					 
					double min = 20000000.0;
					 
					for(int k =0; k < 4; k++){
					 	if(Double.parseDouble(String.format("%.2f", tempAry[k])) < min){
					 		min = Double.parseDouble(String.format("%.2f", tempAry[k])) ;
						}
					} 
					if (imgAry[i][j] >= min){
					 
						imgAry[i][j] = min;
					}	
					if(imgAry[i][j] >= newMaxVal){
						newMaxVal = imgAry[i][j];
					}
				}
			} 
		} 
	}	
			
    private static int is_maxima (double[][] imgAry, int i, int j){
				
		double tempAry[] = new double[8];
		tempAry[0] = imgAry[i-1][j-1];
		tempAry[1] = imgAry[i-1][j];
		tempAry[2] = imgAry[i-1][j+1];
		tempAry[3] = imgAry[i][j-1];
		tempAry[4] = imgAry[i][j+1];
		tempAry[5] = imgAry[i+1][j-1];
		tempAry[6] = imgAry[i+1][j];
		tempAry[7] = imgAry[i+1][j+1];
		
		for(int k =0; k < 8; k++){
			if (!(imgAry[i][j] >= tempAry[k])){
				return 0;
			}
		}
	   return 1;
	}
		
    private static void compute_localMaxima(double[][] imgAry, int[][] skAry){
    	for(int i = 1; i < numRows+1; i++) {
			for(int j = 1; j < numCols+1; j++) {
				if (imgAry[i][j] > 0){
					if(is_maxima(imgAry, i,j) ==1){
						skeletonAry[i][j] = 1;
					} 
					else{	
						skeletonAry[i][j] = 0;
					}
				}		
			}
		}
	}
			
    private static void printImage(double[][] imgAry,  FileOutputStream oFile) { 
    	PrintStream print = new PrintStream(oFile);
    	print.println(numRows + " " + numCols + " " + newMinVal + " " + newMaxVal );
    	for(int i = 1; i < numRows+1; i++) {
			for(int j = 1; j < numCols+1; j++) {
				print.print(imgAry[i][j] + " ");
			}
			print.println();
		}
	}
    
    private static void printSkeleton(int[][] imgAry,  FileOutputStream oFile) { 
    	PrintStream print = new PrintStream(oFile);
    	print.println(numRows + " " + numCols + " " + newMinVal + " " + 1 );
    	for(int i = 1; i < numRows+1; i++) {
			for(int j = 1; j < numCols+1; j++) {
				print.print(imgAry[i][j] + " ");
			}
			print.println();
		}
	}
			
    private static void prettyPrintDistance (double[][] imgAry, String pass) {
    	PrintStream print = new PrintStream(fOutputthree);
    	print.println(pass);
		for(int i = 1; i < numRows+1; i++) {
			for(int j = 1; j < numCols+1; j++) {
				if (imgAry[i][j] == 0.0)
					print.print("   ");
				else {
					if(imgAry[i][j] / 10.0 == 0.0)
						print.print(String.format("%.1f",imgAry[i][j]) + " ");
					else 
						print.print(String.format("%.1f",imgAry[i][j]));
				}
			}
			print.println(); 
		}
		print.println();
	}

    private static void prettyPrintSkeleton (int[][] imgAry) {
    	PrintStream print = new PrintStream(fOutputthree);
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
		
		zeroFramedAry = new double[numRows+2][numCols+2];
		skeletonAry = new int[numRows+2][numCols+2];
		
		zeroFrame(zeroFramedAry);
		loadImage(zeroFramedAry);
		fistPass_EuclidianDistance(zeroFramedAry);
		prettyPrintDistance(zeroFramedAry, "pass-1");
		secondPass_EuclidianDistance(zeroFramedAry);
		printImage(zeroFramedAry, fOutputone);
		prettyPrintDistance(zeroFramedAry, "pass-2");
		compute_localMaxima(zeroFramedAry, skeletonAry);
		printSkeleton(skeletonAry, fOutputtwo); 
		prettyPrintSkeleton(skeletonAry);
		
		inputfile.close();
		try {
			fInput.close();
		} catch (IOException e) {
			
			e.printStackTrace();
		}
	}
	
}