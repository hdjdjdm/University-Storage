public class RungeKutta {
    public static void solve(double a, double b, int n, Function2[] TFMas, double[] y) {
        double h = (b - a) / n;
        double x = a;
        double[][] TFunZnach = new double[n + 1][2];
        TFunZnach[0][0] = y[0];
        TFunZnach[0][1] = y[1];

        for (int i = 0; i < n; i++) {
            double xNext = x + h;
            double k1_0 = h * TFMas[0].apply(y[0], y[1]);
            double k1_1 = h * TFMas[1].apply(y[0], y[1]);

            double k2_0 = h * TFMas[0].apply(y[0] + k1_0 / 2, y[1] + k1_1 / 2);
            double k2_1 = h * TFMas[1].apply(y[0] + k1_0 / 2, y[1] + k1_1 / 2);

            double k3_0 = h * TFMas[0].apply(y[0] + k2_0 / 2, y[1] + k2_1 / 2);
            double k3_1 = h * TFMas[1].apply(y[0] + k2_0 / 2, y[1] + k2_1 / 2);

            double k4_0 = h * TFMas[0].apply(y[0] + k3_0, y[1] + k3_1);
            double k4_1 = h * TFMas[1].apply(y[0] + k3_0, y[1] + k3_1);

            double[] yNext = new double[2];
            yNext[0] = y[0] + (k1_0 + 2 * k2_0 + 2 * k3_0 + k4_0) / 6;
            yNext[1] = y[1] + (k1_1 + 2 * k2_1 + 2 * k3_1 + k4_1) / 6;

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
