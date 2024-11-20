public class LeastSquaresApproximation {
    private double a;
    private double b;
    private double c;

    public LeastSquaresApproximation(double[] x, double[] y) {
        calculateCoefficients(x, y);
    }

    private void calculateCoefficients(double[] x, double[] y) {
        int n = x.length;

        double sumX = 0, sumY = 0, sumX2 = 0, sumX3 = 0, sumX4 = 0;
        double sumXY = 0, sumX2Y = 0;

        for (int i = 0; i < n; i++) {
            sumX += x[i];
            sumY += y[i];
            sumX2 += x[i] * x[i];
            sumX3 += x[i] * x[i] * x[i];
            sumX4 += x[i] * x[i] * x[i] * x[i];
            sumXY += x[i] * y[i];
            sumX2Y += x[i] * x[i] * y[i];
        }

        double[][] matrix = {
                {n, sumX, sumX2},
                {sumX, sumX2, sumX3},
                {sumX2, sumX3, sumX4}
        };

        double[] constants = {sumY, sumXY, sumX2Y};

        double[] solution = solveSystem(matrix, constants);
        this.c = solution[0];
        this.b = solution[1];
        this.a = solution[2];
    }

    private double[] solveSystem(double[][] matrix, double[] constants) {
        double d = determinant(matrix);
        double[] solution = new double[3];

        for (int i = 0; i < 3; i++) {
            double[][] tempMatrix = new double[3][3];
            for (int j = 0; j < 3; j++) {
                for (int k = 0; k < 3; k++) {
                    tempMatrix[j][k] = (k == i) ? constants[j] : matrix[j][k];
                }
            }
            solution[i] = determinant(tempMatrix) / d;
        }

        return solution;
    }

    private double determinant(double[][] matrix) {
        return matrix[0][0] * (matrix[1][1] * matrix[2][2] - matrix[1][2] * matrix[2][1])
                - matrix[0][1] * (matrix[1][0] * matrix[2][2] - matrix[1][2] * matrix[2][0])
                + matrix[0][2] * (matrix[1][0] * matrix[2][1] - matrix[1][1] * matrix[2][0]);
    }

    public double approximate(double q) {
        return a * q * q + b * q + c;
    }
}
