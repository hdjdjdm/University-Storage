import java.util.concurrent.locks.ReentrantLock;

public class Deadlock {
    private static final ReentrantLock lock1 = new ReentrantLock();
    private static final ReentrantLock lock2 = new ReentrantLock();

    private static final Object sorryResource = new Object();
    private static final Object acceptMistakeResource = new Object();

    public static void girlMethod() throws InterruptedException {
        synchronized (sorryResource) {
            System.out.println("Girl: sorry:(");
            Thread.sleep(1000);
            synchronized (acceptMistakeResource) {
                System.out.println("Girl: i accept mistake");
            }
        }
    }

    public static void boyMethod() throws InterruptedException {
        synchronized (acceptMistakeResource) {
            System.out.println("Boy: i accept mistake");
            Thread.sleep(1000);
            synchronized (sorryResource) {
                System.out.println("Boy: sorry");
            }
        }
    }

    public static void girlLockMethod() throws InterruptedException {
        try {
            Thread.sleep(1000);
            lock1.lockInterruptibly();
            System.out.println("Lock1 locked sorry");
            synchronized (sorryResource) {
                System.out.println("Girl: sorry:(");
                try {
                    lock2.lockInterruptibly();
                    System.out.println("Lock2 locked accept mistake");
                    synchronized (acceptMistakeResource) {
                        System.out.println("Girl: i accept mistake");
                    }
                } finally {
                    lock2.unlock();
                    System.out.println("Lock2 unlocked accept mistake");
                }
            }
        } finally {
            lock1.unlock();
            System.out.println("Lock1 unlocked sorry");

        }
    }

    public static void boyLockMethod() throws InterruptedException {
        try {
            Thread.sleep(1000);
            lock1.lockInterruptibly();
            System.out.println("Lock1 locked accept mistake");
            synchronized (acceptMistakeResource) {
                System.out.println("Boy: i accept mistake");
                try {
                    lock2.lockInterruptibly();
                    System.out.println("Lock2 locked sorry");
                    synchronized (sorryResource) {
                        System.out.println("Boy: sorry");
                    }
                } finally {
                    lock2.unlock();
                    System.out.println("Lock2 unlocked sorry");
                }
            }
        } finally {
            lock1.unlock();
            System.out.println("Lock1 unlocked accept mistake");

        }
    }
}
