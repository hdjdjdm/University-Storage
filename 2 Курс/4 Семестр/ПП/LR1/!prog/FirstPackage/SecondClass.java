package FirstPackage;

public class SecondClass {
    private int a, b;
    
    public SecondClass(int a, int b){
        this.a = a;
        this.b = b;
    }

    public int getA(){
        return a;
    }

    public void setA(int a){
        this.a = a;
    }

    public int getB(){
        return b;
    }

    public void setB(int b){
        this.b = b;
    }

    public int Sum(int a, int b){
        return a + b;
    }
}