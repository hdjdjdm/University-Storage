public class Vect{
    private double[] elements;
    private int size;

    public Vect(int size){
        this.size = size;
        elements = new double[size];
    }

    public double getElem(int i){
        return elements[i];
    }

    public void setElem(int i, double num){
        this.elements[i] = num;
    }

    public void printVect(){
        for (double element : elements){
            System.out.print(element + " ");
        }
        System.out.println();
    }

    public int getSize(){
        return size;
    }

    public double getMax(){
        double Max = Double.MIN_VALUE;
        for (double element : elements) {
            if (element > Max) {
                Max = element;
            }
        }
        return Max;
    }

    public double getMin(){
        double Min = Double.MAX_VALUE;
        for (double element : elements) {
            if (element < Min) {
                Min = element;
            }
        }
        return Min;
    }

    public void Sort(){
        for (int i = 0; i < size - 1; i++){
            for (int j = 0; j < size - i - 1; j++){
                if (elements[j] > elements[j + 1]){
                    double temp = elements[j];
                    elements[j] = elements[j + 1];
                    elements[j + 1] = temp;
                }
            }
        }
    }

    public double getEuclid(){
        double SumOfSquares = 0;
        for (double element : elements){
            SumOfSquares += element * element;
        }
        return Math.sqrt(SumOfSquares);
    }

    public void multiplyByX(double x){
        for (int i = 0; i < size; i++){
            elements[i] *= x;
        }
    }

    public void add(Vect other){
        if (this.size != other.size){
            System.out.println("Vectors must have the same size");
        }
        for (int i = 0; i < size; i++){
            elements[i] += other.getElem(i);
        }
    }

    public double ScalarMultiply(Vect other){
        if (this.size != other.size){
            System.out.println("Vectors must have the same size");
        }
        double result = 0.0;
        for (int i = 0; i < size; i++){
            result += elements[i] * other.getElem(i);
        }
        return result;
    }
}