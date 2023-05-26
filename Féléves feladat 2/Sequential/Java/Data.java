package seq;

public class Data extends Thread {
	private double a;
	private double b;
	private double h;
	private int size;
	private int mode;
	private int func;
	
	public Data() {
		
	}

	public Data(double a, double b, double h, int size, int mode, int func) {
		super();
		this.a = a;
		this.b = b;
		this.h = h;
		this.size = size;
		this.mode = mode;
		this.func = func;
	}



	public int getFunc() {
		return func;
	}

	public void setFunc(int func) {
		this.func = func;
	}

	public double getA() {
		return a;
	}

	public void setA(double a) {
		this.a = a;
	}

	public double getB() {
		return b;
	}

	public void setB(double b) {
		this.b = b;
	}

	public double getH() {
		return h;
	}

	public void setH(double h) {
		this.h = h;
	}

	public int getSize() {
		return size;
	}

	public void setSize(int size) {
		this.size = size;
	}
	
	public void setMode(int mode) {
		this.mode = mode;
	}
	
	public int getMode() {
		return mode;
	}
}
