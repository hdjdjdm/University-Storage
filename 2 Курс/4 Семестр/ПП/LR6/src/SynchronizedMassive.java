import java.util.Iterator;

public class SynchronizedMassive implements MassiveInterface {
    private final MassiveInterface delegate;

    public SynchronizedMassive(MassiveInterface delegate) {
        this.delegate = delegate;
    }

    @Override
    public synchronized void print() {
        delegate.print();
    }

    @Override
    public synchronized int getSize() {
        return delegate.getSize();
    }

    @Override
    public synchronized void write(int value, int position) {
        delegate.write(value, position);
    }

    @Override
    public synchronized int read(int position) {
        return delegate.read(position);
    }

    @Override
    public synchronized int getElm(int currentIndex) {
        return delegate.getElm(currentIndex);
    }

    @Override
    public synchronized Iterator<Integer> iterator() {
        return new MassiveIterator(this);
    }
}
