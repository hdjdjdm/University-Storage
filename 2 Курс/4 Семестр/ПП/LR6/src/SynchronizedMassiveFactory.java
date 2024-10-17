public class SynchronizedMassiveFactory implements MassiveInterfaceFactory<SynchronizedMassive> {
    @Override
    public SynchronizedMassive createInstance(int size) {
        MassiveInterface array = new Massive(size);
        return new SynchronizedMassive(array);
    }
}
