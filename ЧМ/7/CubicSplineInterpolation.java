public class CubicSplineInterpolation {

    private double[] x;
    private double[] y;
    private double[] a, b, c, d;

    public CubicSplineInterpolation(double[] x, double[] y) {
        int n = x.length;
        this.x = x;
        this.y = y;
        this.a = new double[n];
        this.b = new double[n - 1];
        this.c = new double[n];
        this.d = new double[n - 1];
        computeSplineCoefficients();
    }

    private void computeSplineCoefficients() {
        int n = x.length - 1;
        double[] h = new double[n];
        double[] alpha = new double[n];

        for (int i = 0; i < n; i++) {
            h[i] = x[i + 1] - x[i];
            if (i > 0) {
                alpha[i] = (3 / h[i]) * (y[i + 1] - y[i]) - (3 / h[i - 1]) * (y[i] - y[i - 1]);
            }
        }

        double[] l = new double[n + 1];
        double[] mu = new double[n];
        double[] z = new double[n + 1];

        l[0] = 1;
        mu[0] = 0;
        z[0] = 0;

        for (int i = 1; i < n; i++) {
            l[i] = 2 * (x[i + 1] - x[i - 1]) - h[i - 1] * mu[i - 1];
            mu[i] = h[i] / l[i];
            z[i] = (alpha[i] - h[i - 1] * z[i - 1]) / l[i];
        }

        l[n] = 1;
        z[n] = 0;
        c[n] = 0;

        for (int j = n - 1; j >= 0; j--) {
            c[j] = z[j] - mu[j] * c[j + 1];
            b[j] = (y[j + 1] - y[j]) / h[j] - h[j] * (c[j + 1] + 2 * c[j]) / 3;
            d[j] = (c[j + 1] - c[j]) / (3 * h[j]);
            a[j] = y[j];
        }
    }

    public double interpolate(double q) {
        int i = findSegment(q);
        double dx = q - x[i];
        return a[i] + b[i] * dx + c[i] * dx * dx + d[i] * dx * dx * dx;
    }

    private int findSegment(double q) {
        int i = 0, j = x.length - 1;
        while (i < j) {
            int mid = (i + j) / 2;
            if (q < x[mid]) j = mid;
            else i = mid + 1;
        }
        return Math.max(i - 1, 0);
    }
}
