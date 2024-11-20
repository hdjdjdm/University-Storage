public class NewtonPolynomial {
    private double[] x;
    private double[] y;
    private double[][] dividedDifferences;

    public NewtonPolynomial(double[] x, double[] y) {
        this.x = x;
        this.y = y;
        this.dividedDifferences = computeDividedDifferences();
    }

    private double[][] computeDividedDifferences() {
        int n = x.length;
        double[][] dd = new double[n][n];

        for (int i = 0; i < n; i++) {
            dd[i][0] = y[i];
        }

        for (int j = 1; j < n; j++) {
            for (int i = 0; i < n - j; i++) {
                dd[i][j] = (dd[i + 1][j - 1] - dd[i][j - 1]) / (x[i + j] - x[i]);
            }
        }

        return dd;
    }

    public double interpolate(double q) {
        double result = dividedDifferences[0][0];
        double term = 1;

        for (int i = 1; i < x.length; i++) {
            term *= (q - x[i - 1]);
            result += dividedDifferences[0][i] * term;
        }

        return result;
    }
}
