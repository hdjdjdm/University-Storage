import java.util.Iterator;

public class UnmodifiableMassive implements MassiveInterface {
    private final MassiveInterface delegate;

    public UnmodifiableMassive(MassiveInterface delegate) {
        this.delegate = delegate;
    }

    @Override
    public void print() {
        delegate.print();
    }

    @Override
    public int getSize() {
        return delegate.getSize();
    }

    @Override
    public void write(int value, int position) {
        throw new UnsupportedOperationException("Cannot modify");
    }

    @Override
    public int read(int position) {
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
