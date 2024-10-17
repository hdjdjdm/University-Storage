public class MassiveFactory implements MassiveInterfaceFactory<Massive> {
    @Override
    public Massive createInstance(int size) {
        return new Massive(size);
    }
}
