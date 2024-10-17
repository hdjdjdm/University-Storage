import java.util.Iterator;

class MassiveIterator implements Iterator<Integer> {
    private int currentIndex = 0;
    private final MassiveInterface array;

    public MassiveIterator(MassiveInterface array) {
        this.array = array;
    }

    @Override
    public boolean hasNext() {
        return currentIndex < array.getSize();
    }

    @Override
    public Integer next() {
        if (!hasNext()) {
            throw new IndexOutOfBoundsException("No more elements");
        }
        int value = array.getElm(currentIndex);
        currentIndex++;
        return value;
    }
}
