package thread;

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
		if((func == 3 || func == 4) && (min > 0 || max > 0)) {
			System.out.println("Negatív számot tartalmazó intervallum esetén nem használhatod ezt a függvényt!");
			System.exit(0);
		} else {
			func = sc.nextInt();
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
		
		threadMethod(data, xArray);
		
		return data;
	}
	
	public static void threadMethod(Data data, double[] xArray) {
		
		final int threadCount = 4;
	    final int startNumber;
	    final int endNumber;
	    
	    if (data.getMode() == 1) {
	    	startNumber = 1;
	    	endNumber = data.getSize()-1;
	    } else {
	    	startNumber = 0;
	    	endNumber = data.getSize()-2;
	    }
	    
	    Thread[] threads = new Thread[threadCount];
	    
	    long startTime = System.currentTimeMillis();
	    
	    for(int i = 0; i < threadCount; i++) {
	    	final int threadNumber = i;
	    	
	    	threads[i] = new Thread(() -> {
	    		calcIntegral(threadNumber, startNumber, endNumber, threadCount, data, xArray);
	    	});
	    	
	    	threads[i].start();
	    }
	    
	    for (Thread thread : threads) {
            try {
                thread.join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
	    
	    long endTime = System.currentTimeMillis();
	    long executionTime = endTime - startTime;
	    
	    System.out.println("Futási idõ: " + executionTime + " ms");
	}
	
	public static void calcIntegral(int threadNumber, int startNumber, int endNumber, int threadCount, 
			Data data, double[] xArray) 
	{
		double partialSum = 0;
		
		if(data.getMode() == 0) {
			for (int i = startNumber + threadNumber; i <= endNumber; i += threadCount) {
	            partialSum += integrableFunction(xArray[i], data);;
	        }
	
	        synchronized (Main.class) {
	            sum += data.getH()*partialSum;
	        }
		} else if (data.getMode() == 1) {
			for (int i = startNumber + threadNumber; i <= endNumber; i += threadCount) {
	            partialSum += integrableFunction(xArray[i], data);
	        }
	
	        synchronized (Main.class) {
	            sum += data.getH()*partialSum;
	        }
		} else {
			for (int i = startNumber + threadNumber; i <= endNumber; i += threadCount) {
	            partialSum += ((xArray[i+1] - xArray[i]) / 2) * (integrableFunction(xArray[i], data) + integrableFunction(xArray[i+1], data));
	        }
	
	        synchronized (Main.class) {
	            sum += partialSum;
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
