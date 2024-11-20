public class LeVerrierSolver {
    private double[][] matrix, v;
    private int n;
    private double[] coefficients;

    public LeVerrierSolver(double[][] matrix) {
        this.matrix = matrix;
        this.n = matrix.length;
        this.coefficients = new double[n + 1];
    }

    public void computeCharacteristicPolynomial() {
        double[][] A_k = identityMatrix(n);
        coefficients[0] = 1.0;

        for (int k = 1; k <= n; k++) {
            A_k = multiplyMatrix(A_k, matrix);
            double trace = trace(A_k);
            coefficients[k] = -trace / k;

            for (int i = 0; i < n; i++) {
                A_k[i][i] -= coefficients[k];
            }
        }
    }

    private double[][] identityMatrix(int size) {
        double[][] identity = new double[size][size];
        for (int i = 0; i < size; i++) {
            identity[i][i] = 1.0;
        }
        return identity;
    }

    private double trace(double[][] matrix) {
        double sum = 0.0;
        for (int i = 0; i < n; i++) {
            sum += matrix[i][i];
        }
        return sum;
    }

    private double[][] multiplyMatrix(double[][] A, double[][] B) {
        double[][] result = new double[n][n];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                result[i][j] = 0.0;
                for (int k = 0; k < n; k++) {
                    result[i][j] += A[i][k] * B[k][j];
                }
            }
        }
        return result;
    }

    public void printEigenvalues() {
        computeCharacteristicPolynomial();

        System.out.println("\nСобственные значения:");
        for (int i = 1; i < coefficients.length; i++) {
            System.out.printf("%.10f\n", -coefficients[i]);
        }

        System.out.println("\nСобственные векторы:");
        for (int i = 0; i < coefficients.length; i++) {
            for (int j = 0; j < coefficients.length; j++) {
                System.out.printf("%.6f", v[i][j]);
            }
            System.out.println();
        }
    }
}