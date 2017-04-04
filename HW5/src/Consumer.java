
public class Consumer extends Thread{
	private final Buff buff;
	int count;
	
	public Consumer(Buff b){
		buff = b;
		count = 0;
	}
	
	public void run(){
		double cumsum = 0;
		while(count < 1000000){
			cumsum += buff.extract();
			if(((count % 100000) == 0) && (count > 0)){
				System.out.printf("Consumer: Consumed %,d items, Cumulative value of consumed items=%.3f\n", count, cumsum);
			}
			count++;
		}
		System.out.printf("Finished consuming %,d items\n", count);
	}
}
