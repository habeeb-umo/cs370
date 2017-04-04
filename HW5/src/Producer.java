import java.util.Random;

public class Producer extends Thread{
	private final Buff buff;
	private int count;

	
	public Producer(Buff b){
		buff = b;
		count = 0;
		
	}
	
	public void run(){
		double cumsum = 0;
		while(count < 1000000){
			Random random = new Random();
			Double bufferElement = random.nextDouble() * 100.0;
			buff.insert(bufferElement);
			cumsum += bufferElement;
			if((count % 100000 == 0) && (count > 0)){
				System.out.printf("Producer: Generated %,d items, Cumulative value of generated items=%.3f\n", count, cumsum);
			}
			count++;
		}
		System.out.printf("Finished producing %,d items\n", count);
	}
}
