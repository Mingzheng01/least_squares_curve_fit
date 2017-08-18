import java.io.PrintWriter;
import java.io.File;
import java.util.Random;

/**
	To compile to bin folder:

	javac -d ../bin MakeDefaultInput.java
	java -cp ../bin MakeDefaultInput

*/

class Point {
	public float x;
	public float y;

	public Point(float x, float y) {
		this.x = x;
		this.y = y;
	}
}

//==================================================================

class MakeDefaultInput {
	/**
	* Make default test data graphing the following functions with matplotlib:
	*
	*  f(x) = x^2
	*  f(x) = 2^x
	*  f(x) = log(x)
	*  f(x) = sin(x)
	*
	*/

	public static Random random = new Random();

	public static void main(String[] args) {
		PrintWriter pwOrg = null;

		// File directory
	 	String inputOrg = "../data/input.csv";

		// Open all the input
		File inputOrgFile = new File(inputOrg);

		// Instantiate the print writer
		try {
			pwOrg = new PrintWriter(inputOrgFile);
		} catch (Exception e) {

			System.out.println("file not found, print writer failed to initialize");
		}

		// Domain for f(x)
	 	int a = 1;
		int b = 360;

		// Get all the points
		Point[] org = polynomial(a, b);

		if (org == null) {
			System.out.println("No points to plot");
			System.exit(1);
		}

		// Write to all the files
		for (int x = a; x < b ; x++) {
			pwOrg.println(org[x].x + "," + org[x].y);
		}

		// Close all the files
		pwOrg.close();
    System.exit(0);
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
		int upper = 5;
		int lower = -5;
		float y;

		for (int x = a; x < b; x++) {
			y = (float) Math.pow(x, 2);
			y = y + random.nextInt(upper - lower) + lower;

			p = new Point(x, y);
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
		float t;

		for (int x = a; x < b; x++) {
			t = (float) Math.toRadians(x);

			float m = (float) 23.58;

			y = (float) (3 * Math.sin(2 * t) + Math.toRadians(m));

			p = new Point((float)t, (float)y);
			points[x] = p;
		}

		return points;
	}
}
