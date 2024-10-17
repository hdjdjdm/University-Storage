public class GirlLock extends Thread{
    public GirlLock(String name){
        super(name);
    }

    public void run(){
        try {
            Deadlock.girlLockMethod();
        } catch (InterruptedException e) {
            System.out.println(getName() + " was interrupted");
        }
    }
}
