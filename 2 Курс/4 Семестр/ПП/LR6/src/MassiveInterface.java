import java.util.Iterator;

public interface MassiveInterface extends Iterable<Integer> {
    void print();
    int getSize();
    void write(int value, int position);
    int read(int position);
    int getElm(int currentIndex);
}
