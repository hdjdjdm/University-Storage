public class Main {
    public static void main(String[] args) {
        int size = 10;
        SynchronizedMassiveFactory synchronizedMassiveFactory = new SynchronizedMassiveFactory();
        IOUtils.setMassiveIntefaceFactory(synchronizedMassiveFactory);
        MassiveInterface synchronizedMassive = IOUtils.createInstance(size);
        MassiveSynchronizer synchronizer = new MassiveSynchronizer(synchronizedMassive);

        WriterRunnable writerRunnable = new WriterRunnable(synchronizer);
        ReaderRunnable readerRunnable = new ReaderRunnable(synchronizer);

        Thread writerThread = new Thread(writerRunnable);
        Thread readerThread = new Thread(readerRunnable);

        writerThread.start();
        readerThread.start();

        try {
            writerThread.join();
            readerThread.join();
        } catch (InterruptedException e) {
            throw new RuntimeException(e);
        }

        System.out.print("\nArray: ");
        MassiveIterator iterator = new MassiveIterator(synchronizedMassive);
        while (iterator.hasNext()) {
            Integer element = iterator.next();
            System.out.print(element + " ");
        }

        System.out.println("\n\nUnmodifiable:\narray.write(100, 0)");
        UnmodifiableMassiveFactory unmodifiableFactory = new UnmodifiableMassiveFactory();
        IOUtils.setMassiveIntefaceFactory(unmodifiableFactory);
        MassiveInterface unmodifiableMassive = IOUtils.createInstance(size);
        try {
            unmodifiableMassive.write(100, 0);
        } catch (UnsupportedOperationException e) {
            System.out.println("Caught UnsupportedOperationException: " + e.getMessage());
        }

    }
}
