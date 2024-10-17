public class ReaderRunnable implements Runnable {
    private final MassiveSynchronizer synchronizer;

    public ReaderRunnable(MassiveSynchronizer synchronizer) {
        this.synchronizer = synchronizer;
    }

    @Override
    public void run() {
        for (int i = 0; i < synchronizer.getArray().getSize(); i++) {
            try {
                synchronizer.read(i);
            } catch (InterruptedException e) {
                throw new RuntimeException(e);
            }
            try {
                Thread.sleep(150);
            } catch (InterruptedException e) {
                throw new RuntimeException(e);
            }
//            if (i == synchronizer.getArray().getSize() - 1) {
//                synchronizer.getArray().print();
//            }
        }
    }
}
