
public class BoundedBuff {
	public static void main(String[] args){
		Buff buff = new Buff();
		Producer p = new Producer(buff);
		Consumer c = new Consumer(buff);
		p.start();
		c.start();
		try{
			p.join();
			c.interrupt();
		} catch (InterruptedException e){
		}
		System.out.println("Exiting!");
	}
}
