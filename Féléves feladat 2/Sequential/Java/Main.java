package seq;

import java.util.Scanner;
import java.lang.Math;

public class Main extends Data {

	public static Scanner sc = new Scanner(System.in); 
	private static volatile double sum = 0;
	
	public static void main(String[] args) {
		makeXArray();
		
		System.out.println("A közelítés értéke: " + sum);
	}
	
	public static Data getDatas() {
		
		double min, max, h;
		int size = 0, mode = 0, func = 0;
		
		System.out.println("Adja meg az intervallumot:");
		//
		System.out.print("Min(a): ");
		min = sc.nextDouble();
		sc.nextLine();
		//
		System.out.print("Max(b): ");
		max = sc.nextDouble();
		sc.nextLine();
		//
		System.out.print("Adja meg az n-et: ");
		size = sc.nextInt();
		sc.nextLine();
		//
		System.out.println("Melyik függvény? (0 - sin, 1 - cos, 2 - exp, 3 - sqrt, 4 - log)");
		func = sc.nextInt();
		if((func == 3 || func == 4) && (min > 0 || max > 0)) {
			System.out.println("Negatív számot tartalmazó intervallum esetén nem használhatod ezt a függvényt!");
			System.exit(0);
		}
		sc.nextLine();
		//
		System.out.println("Adja meg, melyik formulát alkalmazná: (0 - egyszerû téglalap, 1 - összetett téglalap, 2 - összetett trapéz)");
		mode = sc.nextInt();
		sc.nextLine();
		
		h = (max - min) / size;
		
		Data data = new Data(min, max, h, size, mode, func);
		
		return data;
	}
	
	public static Data makeXArray() {
		Data data = getDatas();
		
		double[] xArray = new double[data.getSize()];
		
		for(int i = 0; i < data.getSize(); i++) {
			xArray[i] += data.getA()+i*data.getH();
		}
		
		long startTime = System.currentTimeMillis();
		
		calcIntegral(xArray, data);
		
		long endTime = System.currentTimeMillis();
	    long executionTime = endTime - startTime;
	    
	    System.out.println("Futási idõ: " + executionTime + " ms");
		
		return data;
	}
		
	public static void calcIntegral(double[] xArray, Data data) 
	{		
		if(data.getMode() == 0) {
			for(int i = 0; i < data.getSize()-1; i++) {
				sum += data.getH()*integrableFunction(xArray[i], data);
			}
		} else if(data.getMode() == 1) {
			for(int i = 1; i < data.getSize(); i++) {
				sum += data.getH()*integrableFunction(xArray[i], data);
			}
		} else {
			for(int i = 0; i < data.getSize()-1; i++) {
				sum += ((xArray[i+1] - xArray[i]) / 2) * (integrableFunction(xArray[i], data) + integrableFunction(xArray[i+1], data));
			}
		}
	}
	
	public static double integrableFunction(double x, Data data) {
		if (data.getFunc() == 0) {
            return Math.sin(x);
        } else if (data.getFunc() == 1) {
            return Math.cos(x);
        } else if (data.getFunc() == 2) {
            return Math.exp(x);
        } else if (data.getFunc() == 3) {
            return Math.sqrt(x);
        } else if (data.getFunc() == 4) {
            return Math.log(x);
        } else {
            throw new IllegalArgumentException("Érvénytelen függvény. Válassz 0 és 4 közötti egész számot.");
        }
	}
}
