
public class BoundedBuff {
	public static void main(String[] args){
		System.out.println("starting");
		Buff buff = new Buff();
		Producer p = new Producer(buff);
		Consumer c = new Consumer(buff);
		p.start();
		c.start();
		//System.out.println(buff.bufferValueCounter);
		try{
			p.join();
			//System.out.println(buff.bufferValueCounter);
			c.interrupt();
		} catch (InterruptedException e){
			System.out.println("End of program");
		}
		//System.out.println(buff.bufferValueCounter);
	}
}
