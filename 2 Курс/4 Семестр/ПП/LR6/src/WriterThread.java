import java.util.Random;

public class WriterThread extends Thread {
    private final MassiveInterface array;
    private final Random random = new Random();

    public WriterThread(MassiveInterface array) {
        this.array = array;
    }

    @Override
    public void run() {
        for (int i = 0; i < array.getSize(); i++) {
            int value = random.nextInt(100) + 1;
            array.write(value, i);
            try {
                Thread.sleep(100);
            } catch (InterruptedException e) {
                throw new RuntimeException(e);
            }
        }
    }
}
