import java.util.Random;

public class WriterRunnable implements Runnable {
    private final MassiveSynchronizer synchronizer;

    public WriterRunnable(MassiveSynchronizer synchronizer) {
        this.synchronizer = synchronizer;
    }

    @Override
    public void run() {
        Random random = new Random();
        for (int i = 0; i < synchronizer.getArray().getSize(); i++) {
            int value = random.nextInt(100) + 1;
            synchronizer.write(value, i);
            try {
                Thread.sleep(100);
            } catch (InterruptedException e) {
                throw new RuntimeException(e);
            }
        }
    }
}
