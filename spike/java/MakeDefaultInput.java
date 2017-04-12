import java.io.PrintWriter;
import java.io.File;
import java.util.Random;
 
class Point {
	public float x;
	public float y;

	public Point(float x, float y) {
		this.x = x;
		this.y = y;
	}
}

class MakeDefaultInput {
	public static Random random = new Random();

	// File directories
	public static String inputOrg = "../../data/input.csv";
	public static String outputPoly = "../../data/output_poly.csv";
	public static String outputExp = "../../data/output_exp.csv";
	public static String outputLog = "../../data/output_log.csv";
	public static String outputSin = "../../data/output_sin.csv";

	/**
	* Make default test data graphing the following functions with matplotlib:
	*
	*  f(x) = x^2
	*  f(x) = 2^x
	*  f(x) = log(x)
	*  f(x) = sin(x)
	*
	*/
	public static void main(String[] args) throws Exception {

		// Domain for f(x)
	 	int a = 1;
		int b = 360;

		// Get all the points
		Point[] org = sinusoidal(a, b);
		Point[] poly = polynomial(a, b);
		Point[] exp = exponential(a, b);
		Point[] log = logarithmic(a, b);
		Point[] sin = sinusoidal(a, b);

		// Open all the files
		File inputOrgFile = new File(inputOrg);
		File outputPolyFile = new File(outputPoly);
		File outputExpFile = new File(outputExp);
		File outputLogFile = new File(outputLog);
		File outputSinFile = new File(outputSin);

		// Open all the print writers
		PrintWriter pwOrg = new PrintWriter(inputOrgFile);
		PrintWriter pwPoly = new PrintWriter(outputPolyFile);
		PrintWriter pwExp = new PrintWriter(outputExpFile);
		PrintWriter pwLog = new PrintWriter(outputLogFile);
		PrintWriter pwSin = new PrintWriter(outputSinFile);

		// Write to all the files
		for (int x = a; x < b ; x++) {
			pwOrg.println(org[x].x + "," + org[x].y);

			/*
			pwPoly.println(poly[x].x + "," + poly[x].y);
			pwExp.println(exp[x].x + "," + exp[x].y);
			pwLog.println(log[x].x + "," + log[x].y);
			pwSin.println(sin[x].x + "," + sin[x].y);
			*/

		}

		// Close all the files
		pwOrg.close();
		pwPoly.close();
		pwExp.close();
		pwLog.close();
		pwSin.close();
	}

//-------------------------------------------------------------------


/**
	* f(x) = sin(x) + x
	*
	* @param a low bound of domain
	* @param b upper bound of domain
	* @return points = {<x,f(x)> | ∀x (a ≤ x ≤ b)}
	*/
public static Point[] input(int a, int b) {
	Point[] points = new Point[b];
	Point p;

	for (int x = a; x < b; x++) {
		p = new Point(x, (float) (Math.sin(x) + x));

		points[x] = p;
	}

	return points;	
}


//-------------------------------------------------------------------

	/**
	* f(x) = x^2
	*
	* @param a low bound of domain
	* @param b upper bound of domain
	* @return points = {<x,f(x)> | ∀x (a ≤ x ≤ b)}
	*/
	public static Point[] polynomial(int a, int b) {
		Point[] points = new Point[b];
		Point p;

		for (int x = a; x < b; x++) {
			p = new Point(x, (float) Math.pow(x, 2));
			points[x] = p;
		}

		return points;	
	}

//-------------------------------------------------------------------

	/**
	* f(x) = 3^x
	*
	* @param a low bound of domain
	* @param b upper bound of domain
	* @return points = {<x,f(x)> | ∀x (a ≤ x ≤ b)}
	*/
	public static Point[] exponential(int a, int b) {
		Point[] points = new Point[b];
		Point p;
		float y;
	
		for (int x = a; x < b; x++) {
			y = (float) (3 * Math.pow(2, x));
			p = new Point(x, y);
			points[x] = p;
		}
		
		return points;
	}

//-------------------------------------------------------------------

	/**
	* f(x) = log(x)
	*
	* @param a low bound of domain
	* @param b upper bound of domain
	* @return points = {<x,f(x)> | ∀x (a ≤ x ≤ b)}
	*/
	public static Point[] logarithmic(int a, int b) {
		Point[] points = new Point[b];
		Point p;
		float y;
		
		for (int x = a; x < b; x++) {

			y = (float) Math.log(x);

			int upper = (int) 1;
			int lower = (int) 0;

			y = y + random.nextInt(upper - lower) + lower;

			y = y * -1;

			p = new Point(x, y);
			points[x] = p;
		}

		return points;
	}

//-------------------------------------------------------------------

	/**
	* f(x) = sin(x)
	*
	* @param a low bound of domain
	* @param b upper bound of domain
	* @return points = {<x,f(x)> | ∀x (a ≤ x ≤ b)}
	*/
	public static Point[] sinusoidal(int a, int b) {
		Point[] points = new Point[b];
		Point p;
		float y;

		for (int x = a; x < b; x++) {
			p = new Point((float)x, (float) (Math.toDegrees(Math.sin(Math.toRadians((2*x)-14))) + 20));
			points[x] = p;			
		}
		
		return points;
	}
}






