public class KrylovSolver {
    private double[][] matrix, v;
    private int n;
    private double[] coefficients;

    public KrylovSolver(double[][] matrix) {
        this.matrix = matrix;
        this.n = matrix.length;
        if (n == 0 || matrix[0].length != n) {
            throw new IllegalArgumentException("Матрица должна быть квадратной и не пустой");
        }
        this.coefficients = new double[n + 1];
    }

    public double[] computeCharacteristicPolynomial() {
        double[][] krylovMatrix = new double[n][n];
        double[] b = new double[n];
        b[0] = 1.0;

        for (int i = 0; i < n; i++) {
            if (i > 0) {
                b = multiplyMatrixVector(matrix, b);
            }
            for (int j = 0; j < n; j++) {
                if (j < b.length) {
                    krylovMatrix[j][i] = b[j];
                } else {
                    krylovMatrix[j][i] = 0.0;
                }
            }
        }

        double[] lastVector = multiplyMatrixVector(matrix, b);
        for (int i = 0; i < n; i++) {
            lastVector[i] = -lastVector[i];
        }

        coefficients = solveLinearSystem(krylovMatrix, lastVector);

        return coefficients;
    }

    private double[] multiplyMatrixVector(double[][] A, double[] x) {
        double[] result = new double[A.length];
        for (int i = 0; i < A.length; i++) {
            result[i] = 0.0;
            for (int j = 0; j < A[i].length; j++) {
                result[i] += A[i][j] * x[j];
            }
        }
        return result;
    }

    private double[] solveLinearSystem(double[][] A, double[] b) {
        int n = A.length;
        double[] x = new double[n];

        for (int i = 0; i < n; i++) {
            int maxRow = i;
            for (int k = i + 1; k < n; k++) {
                if (Math.abs(A[k][i]) > Math.abs(A[maxRow][i])) {
                    maxRow = k;
                }
            }

            double[] temp = A[i];
            A[i] = A[maxRow];
            A[maxRow] = temp;

            double t = b[i];
            b[i] = b[maxRow];
            b[maxRow] = t;

            for (int k = i + 1; k < n; k++) {
                double factor = A[k][i] / A[i][i];
                b[k] -= factor * b[i];
                for (int j = i; j < n; j++) {
                    A[k][j] -= factor * A[i][j];
                }
            }
        }

        for (int i = n - 1; i >= 0; i--) {
            double sum = 0.0;
            for (int j = i + 1; j < n; j++) {
                sum += A[i][j] * x[j];
            }
            x[i] = (b[i] - sum) / A[i][i];
        }

        return x;
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