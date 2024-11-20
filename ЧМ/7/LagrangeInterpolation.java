public class LagrangeInterpolation {
    public static double interpolate(double[] x, double[] y, double q) {
        int n = x.length;
        double result = 0.0;

        for (int i = 0; i < n; i++) {
            double term = y[i];
            for (int j = 0; j < n; j++) {
                if (j != i) {
                    term *= (q - x[j]) / (x[i] - x[j]);
                }
            }
            result += term;
        }

        return result;
    }
}
