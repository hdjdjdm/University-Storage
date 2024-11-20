
public class FadeevSolver {
    private double[][] matrix, v;
    private int n;
    private double[] coefficients;

    public FadeevSolver(double[][] matrix) {
        this.matrix = matrix;
        this.n = matrix.length;
        this.coefficients = new double[n + 1];
    }

    public double[] computeCharacteristicPolynomial() {
        double[][] A = new double[n][n];
        double[] b = new double[n];

        coefficients[0] = 1.0;
        b[0] = 1.0;

        for (int k = 1; k <= n; k++) {
            for (int i = 0; i < n; i++) {
                b[i] = 0.0;
                for (int j = 0; j < n; j++) {
                    A[i][j] = matrix[i][j];
                }
            }

            double trace = 0.0;
            for (int i = 0; i < n; i++) {
                trace += A[i][i];
            }

            coefficients[k] = -trace / k;

            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (i == j) {
                        A[i][j] = A[i][j] - coefficients[k];
                    }
                }
            }

            double[][] nextA = new double[n-1][n-1];

            for (int i = 0; i < n - 1; i++) {
                for (int j = 0; j < n - 1; j++) {
                    nextA[i][j] = A[i + 1][j + 1];
                }
            }
            matrix = nextA;
            n--;
        }

        return coefficients;
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