public class CubicSplineDifferentiation {

    public static double f(double x) {
        return Math.exp(-(x + 1 / x));
    }

    public static double[] cubicSpline(double[] x, double[] y) {
        int n = x.length - 1;
        double[] h = new double[n];
        double[] a = new double[n + 1];
        double[] b = new double[n];
        double[] c = new double[n + 1];
        double[] d = new double[n];

        for (int i = 0; i < n; i++) {
            h[i] = x[i + 1] - x[i];
            a[i] = y[i];
        }
        a[n] = y[n];

        double[] alpha = new double[n];
        for (int i = 1; i < n; i++) {
            alpha[i] = (3.0 / h[i]) * (y[i + 1] - y[i]) - (3.0 / h[i - 1]) * (y[i] - y[i - 1]);
        }

        double[] l = new double[n + 1];
        double[] mu = new double[n];
        double[] z = new double[n + 1];

        l[0] = 1.0;
        for (int i = 1; i < n; i++) {
            l[i] = 2.0 * (x[i + 1] - x[i - 1]) - h[i - 1] * mu[i - 1];
            mu[i] = h[i] / l[i];
            z[i] = (alpha[i] - h[i - 1] * z[i - 1]) / l[i];
        }
        l[n] = 1.0;
        z[n] = 0.0;

        for (int j = n - 1; j >= 0; j--) {
            c[j] = z[j] - mu[j] * c[j + 1];
            b[j] = (y[j + 1] - y[j]) / h[j] - h[j] * (c[j + 1] + 2.0 * c[j]) / 3.0;
            d[j] = (c[j + 1] - c[j]) / (3.0 * h[j]);
        }

        double[] coefficients = new double[n * 4];
        for (int i = 0; i < n; i++) {
            coefficients[i * 4] = a[i];
            coefficients[i * 4 + 1] = b[i];
            coefficients[i * 4 + 2] = c[i];
            coefficients[i * 4 + 3] = d[i];
        }

        return coefficients;
    }

    public static double evaluateSplineDerivative(double[] x, double[] coefficients, double xVal) {
        int n = x.length - 1;
        int i = n - 1;
        while (i > 0 && x[i] > xVal) {
            i--;
        }

        int idx = i * 4;

        double dx = xVal - x[i];
        return coefficients[idx + 1] + 2 * coefficients[idx + 2] * dx + 3 * coefficients[idx + 3] * dx * dx;
    }

    public static void main(String[] args) {
        double start = 1.0;
        double end = 2.1;
        double step = 0.1;
        int nPoints = (int) ((end - start) / step) + 1;

        double[] x = new double[nPoints];
        double[] y = new double[nPoints];

        for (int i = 0; i < nPoints; i++) {
            x[i] = start + i * step;
            y[i] = f(x[i]);
        }

        double[] coefficients = cubicSpline(x, y);

        System.out.printf("%-5s %-10s %-15s%n", "x", "f(x)", "f'(x)");
        for (double xVal = start; xVal <= end; xVal += step) {
            double functionValue = f(xVal);
            double derivativeValue = evaluateSplineDerivative(x, coefficients, xVal);
            System.out.printf("%-5.1f %-10.5f %-15.5f%n", xVal, functionValue, derivativeValue);
        }
    }
}
