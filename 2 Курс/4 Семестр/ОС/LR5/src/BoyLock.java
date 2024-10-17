public class BoyLock extends Thread{
    public BoyLock(String name){
        super(name);
    }

    public void run(){
        try {
            Deadlock.boyLockMethod();
        } catch (InterruptedException e) {
            System.out.println(getName() + " was interrupted");
        }
    }
}
