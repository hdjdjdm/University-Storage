public class MassiveSynchronizer {
    private final MassiveInterface array;
    private boolean isWriteTurn = true;

    public MassiveSynchronizer(MassiveInterface array) {
        this.array = array;
    }

    public MassiveInterface getArray() {
        return array;
    }

    public synchronized void write(int value, int position) {
        while (!isWriteTurn) {
            try {
                wait();
            } catch (InterruptedException e) {
                throw new RuntimeException(e);
            }
        }
        array.write(value, position);
        isWriteTurn = false;
        notifyAll();
    }

    public synchronized int read(int position) throws InterruptedException {
        while (isWriteTurn) {
            try {
                wait();
            } catch (InterruptedException e) {
                throw new RuntimeException(e);
            }
        }
        int value = array.read(position);
        isWriteTurn = true;
        notifyAll();
        return value;
    }
}
