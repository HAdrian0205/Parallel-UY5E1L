package num_int;

// import java.util.Random;
import java.util.Scanner;

public class Main extends Data {

	public static Scanner sc = new Scanner(System.in); 
	private static volatile double sum = 0;
	
	public static void main(String[] args) {
		makeXArray();
		
		System.out.println("A közelítés értéke: " + sum);
	}
	
	public static Data getDatas() {
		
		double min, max, h, temp;
		int size = 0, mode;
		
		System.out.println("Adja meg az intervallumot:");
		System.out.print("Min(a): ");
		min = sc.nextDouble();
		sc.nextLine();
		System.out.print("Max(b): ");
		max = sc.nextDouble();
		sc.nextLine();
		System.out.print("Adja meg a hoppot: ");
		h = sc.nextDouble();
		sc.nextLine();
		System.out.println("Adja meg, melyik formulát alkalmazná: (0 - egyszerû téglalap, 1 - összetett téglalap, 2 - összetett trapéz)");
		mode = sc.nextInt();
		sc.nextLine();
		
		temp = min;
		
		while(temp <= max){
			temp += h;
			size++;
		}
		
		Data data = new Data(min, max, h, size, mode);
		
		return data;
	}
	
	public static Data makeXArray() {
		Data data = getDatas();
		
		double[] xArray = new double[data.getSize()];
		
		for(int i = 0; i < data.getSize(); i++) {
			xArray[i] += data.getA()+i*data.getH();
		}
		
		getValues(data, xArray);
		
		return data;
	}
	
	public static void getValues(Data data, double[] xArray) {
		
		double[] yArray = new double[data.getSize()];
		
		System.out.println("Adja meg az értékeket: ");
		
		for(int i = 0; i < data.getSize(); i++) {
			System.out.print("x(" + xArray[i] + "): ");
			yArray[i] = sc.nextDouble();
			sc.nextLine();
			System.out.println("");
		}
		
		/*Random random = new Random();
		
		for(int i = 0; i < data.getSize(); i++) {
			yArray[i] = 1 + (random.nextDouble() * (2 - 1));
		}*/
		
		threadMethod(data, xArray, yArray);
	}
	
	public static void threadMethod(Data data, double[] xArray, double[] yArray) {
		
		final int threadCount = 3;
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
	    		calcIntegral(threadNumber, startNumber, endNumber, threadCount, data, xArray, yArray);
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
			Data data, double[] xArray, double[] yArray) 
	{
		double partialSum = 0;
		
		if(data.getMode() == 0) {
			for (int i = startNumber + threadNumber; i <= endNumber; i += threadCount) {
	            partialSum += yArray[i];
	        }
	
	        synchronized (Main.class) {
	            sum += data.getH()*partialSum;
	        }
		} else if (data.getMode() == 1) {
			for (int i = startNumber + threadNumber; i <= endNumber; i += threadCount) {
	            partialSum += yArray[i];
	        }
	
	        synchronized (Main.class) {
	            sum += data.getH()*partialSum;
	        }
		} else {
			for (int i = startNumber + threadNumber; i <= endNumber; i += threadCount) {
	            partialSum += ((xArray[i+1] - xArray[i]) / 2) * (yArray[i+1] + yArray[i]);
	        }
	
	        synchronized (Main.class) {
	            sum += partialSum;
	        }
		}
	        
	}
}