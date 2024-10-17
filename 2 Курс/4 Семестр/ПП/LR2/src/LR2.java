public class LR2 {
    public static void main(String[] args){
        Vect vect1 = new Vect(5);
        vect1.setElem(0, 5.2);
        vect1.setElem(1, 1.4);
        vect1.setElem(2, 2.6);
        vect1.setElem(3, 4.8);
        vect1.setElem(4, 3.0);

        Vect vect2 = new Vect(5);
        vect2.setElem(0, 1.2);
        vect2.setElem(1, 4.4);
        vect2.setElem(2, 2.6);
        vect2.setElem(3, 3.8);
        vect2.setElem(4, 5.0);

        System.out.print("vect1: ");
        vect1.printVect();
        System.out.print("vect2: ");
        vect2.printVect();
        System.out.println();

        System.out.println("Last vect1's element is " + vect1.getElem(4));
        System.out.println("Size of vect1 is " + vect1.getSize());
        System.out.println("Max element in vect1 is " + vect1.getMax());
        System.out.println("Min element in vect2 is " + vect2.getMin());

        vect1.Sort();
        System.out.print("Sorted vect1: ");
        vect1.printVect();

        System.out.println("Euclid in vect1 is " + vect1.getEuclid());

        System.out.print("vect1 * 5 = ");
        vect1.multiplyByX(5);
        vect1.printVect();

        System.out.print("vect1 + vect2 = ");
        vect1.add(vect2);
        vect1.printVect();

        System.out.print("vect1 * vect2 = " + vect1.ScalarMultiply(vect2));
    }
}
