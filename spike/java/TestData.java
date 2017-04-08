import java.util.*;
import java.io.*;

// Give TimerTask a varialble
abstract class MyTimerTask extends TimerTask {
	int x;
	double pi = 3.14159265;

	public MyTimerTask(int i) {
		super();
		this.x = x;
	}
}

/**
Simulate live data updates to a csv every 5 seconds
*/
class TestData {
	public static void main(String[] args) throws Exception {
		String fileName = "../../data/input1.csv";

		File file = new File(fileName);
		PrintWriter printWriter = new PrintWriter(file);
		printWriter.write("");
		printWriter.close();

		int interval = 1000;
		int x = 0;
		

		Timer t = new Timer();
		t.schedule(new MyTimerTask(x) {
			@Override
			public void run() {
				try {	   
					double y = Math.sin(x) + x;
					String line = x + "," + y + "\n";
					appendLine(line);
					System.out.print(line);
					x++;
				
				} catch (Exception e) {
					;					
				}
			}
		}, 0, interval);
	}

	public static void appendLine(String line) throws Exception {
		File file = new File("../../data/input1.csv");
		FileWriter fw = new FileWriter(file,true);
    	BufferedWriter bw = new BufferedWriter(fw);
		PrintWriter printWriter = new PrintWriter(bw);

		printWriter.append(line);

		printWriter.close();
	}
}
