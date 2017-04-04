import java.util.Random;

public class Producer extends Thread{
	private final Buff buff;

	
	public Producer(Buff b){
		buff = b;
		
	}
	
	public void run(){
		while(!Thread.currentThread().isInterrupted()){
			Random random = new Random();
			Double bufferElement = random.nextDouble() * 100.0;
			buff.insert(bufferElement);
			System.out.println("Inserted: " + bufferElement);
			buff.bufferValueCounter++;
		}
	}
}
