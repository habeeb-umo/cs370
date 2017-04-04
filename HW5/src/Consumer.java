
public class Consumer extends Thread{
	private final Buff buff;
	double cumsum;
	double consumed;
	
	public Consumer(Buff b){
		buff = b;
		consumed = 0;
		cumsum = 0;
	}
	
	public void run(){
		while(!Thread.currentThread().isInterrupted()){
			if(consumed == 10){
				System.exit(-1);
			}
			double extracted = buff.extract();
			cumsum += extracted;
			System.out.println("Extracted: " + extracted);
			if(extracted > -1){
			buff.bufferValueCounter--;
			consumed++;
			}else System.exit(-1);
		}
		System.out.println("total: cumsum");
	}
}
