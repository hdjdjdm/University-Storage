import java.util.Random;

public class ReaderThread extends Thread {
    private final MassiveInterface array;
    private final Random random = new Random();

    public ReaderThread(MassiveInterface array) {
        this.array = array;
    }

    @Override
    public void run() {
        for (int i = 0; i < array.getSize(); i++) {
            int value = random.nextInt(100) + 1;
            array.read(i);
            try {
                Thread.sleep(150);
            } catch (InterruptedException e) {
                throw new RuntimeException(e);
            }
        }
    }
}
