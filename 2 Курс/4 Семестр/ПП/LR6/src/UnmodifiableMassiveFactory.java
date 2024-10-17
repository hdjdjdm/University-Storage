public class UnmodifiableMassiveFactory implements MassiveInterfaceFactory<UnmodifiableMassive> {
    @Override
    public UnmodifiableMassive createInstance(int size) {
        MassiveInterface array = new Massive(size);
        return new UnmodifiableMassive(array);
    }
}
