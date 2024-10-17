public class Main {
    public static void main(String[] args) {
        int size = 10;
        MassiveInterface array = new Massive(size);
        MassiveInterface synchronizedMassive = IOUtils.synchronizedInterface(array);
        MassiveSynchronizer synchronizer = new MassiveSynchronizer(synchronizedMassive);

        WriterRunnable writerRunnable = new WriterRunnable(synchronizer);
        ReaderRunnable readerRunnable = new ReaderRunnable(synchronizer);

        Thread writerThread = new Thread(writerRunnable);
        Thread readerThread = new Thread(readerRunnable);

        writerThread.start();
        readerThread.start();

    }
}