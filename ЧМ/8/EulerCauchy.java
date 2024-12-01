public class EulerCauchy {
    public static void solve(double a, double b, int n, Function2[] TFMas, double[] y) {
        double h = (b - a) / n;
        double x = a;
        double[][] TFunZnach = new double[n + 1][2];
        TFunZnach[0][0] = y[0];
        TFunZnach[0][1] = y[1];

        for (int i = 0; i < n; i++) {
            double xNext = x + h;
            double[] yNext = new double[2];
            yNext[0] = y[0] + h * TFMas[0].apply(y[0] + h / 2 * TFMas[0].apply(y[0], y[1]), y[1]);
            yNext[1] = y[1] + h * TFMas[1].apply(y[0] + h / 2 * TFMas[0].apply(y[0], y[1]), y[1]);
            TFunZnach[i + 1][0] = yNext[0];
            TFunZnach[i + 1][1] = yNext[1];
            x = xNext;
            y = yNext;
        }

        for (int i = 0; i <= n; i++) {
            double xi = a + i * h;
            System.out.printf("x = %.2f, y1 = %.6f, y2 = %.6f%n", xi, TFunZnach[i][0], TFunZnach[i][1]);
        }
    }
}
