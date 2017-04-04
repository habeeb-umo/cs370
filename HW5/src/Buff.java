
public class Buff extends Thread {
	int MAX_SIZE = 1000;
	private int buffEnd;
	private int buffStart;
	private int buffSize;
	int bufferValueCounter;

	double[] buffArray;
	
	public Buff(){

		bufferValueCounter = 0;
		buffStart = 0;
		buffEnd = -1;
		buffSize = 0;
		buffArray = new double[MAX_SIZE];
	}
	public synchronized void insert(double d){
		try{
			while(buffSize == MAX_SIZE){
				wait();
			}
		buffEnd = (buffEnd + 1) % MAX_SIZE;
		buffArray[buffEnd]= d;
		buffSize++;
		notifyAll();
		
		}catch(InterruptedException e){
			Thread.currentThread().interrupt();
		}
	}
	
	public synchronized double extract(){
		try{
			while(buffSize == 0){
				wait();
			}
		double d = buffArray[buffStart];
		buffStart = (buffStart + 1) % MAX_SIZE;
		buffSize --;
		notifyAll();
		return d;
		
		}catch(InterruptedException e){
			Thread.currentThread().interrupt();
			return -1;
		}
	}
	
}
