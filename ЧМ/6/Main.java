public class Main {
    public static void main(String[] args) {
        double[][] matrixData = {
            {0.070954, -0.00009936, 0.0037446, -0.000035194},
            {-35.012, 22.264, 25.177, -0.78859},
            {232.36, 147.75, 167.09, -52.335},
            {-0.016032, -0.002245, -0.084609, 0.0079521}
        };
        System.out.println("Решение методом QR-разложения:\n");
        Matrix matrix = new Matrix(matrixData);

        QRDecomposition qr = new QRDecomposition();
        qr.findEigenvaluesAndEigenvectors(matrix);
    }
}
