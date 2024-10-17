import FirstPackage.*;

class FirstClass {
    public static void main(String[] s){
        SecondClass o = new SecondClass(0, 0);
        int i, j;
        for (i = 1; i <= 8; i++){
            for (j = 1; j <= 8; j++){
                o.setA(i);
                o.setB(j);
                System.out.print(o.Sum(i, j) + "\t");
            }
            System.out.println();
        }
    }
}
