import java.util.Arrays;
import java.util.Iterator;

public class Massive implements MassiveInterface {
    private final int[] array;
    private final int size;

    public Massive(int size){
        array = new int[size];
        this.size = size;
    }

    @Override
    public int getSize() {
        return size;
    }

    @Override
    public void print() {
        System.out.println(Arrays.toString(array));
    }

    @Override
    public void write(int value, int position) {
        array[position] = value;
        System.out.println("Write: " + value + " to position " + position);
    }

    @Override
    public int read(int position) {
        int value = array[position];
        System.out.println("Read: " + value + " to position " + position);
        return value;
    }

    public int getElm(int currentIndex) {
        return array[currentIndex];
    }

    @Override
    public Iterator<Integer> iterator() {
        return new MassiveIterator(this);
    }
}
