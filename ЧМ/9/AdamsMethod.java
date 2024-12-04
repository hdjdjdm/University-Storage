
public class AdamsMethod {
    public static void main(String[] args) {
        double a = 1.0;
        double b = 4.0;
        int n = 10;
        double h = (b - a) / n;

        double y1 = 1.0; 
        double y2 = 1.0;

        double[][] ys = new double[n + 1][2];
        ys[0][0] = y1;
        ys[0][1] = y2;

        for (int i = 1; i <= 3; i++) {
            double k11 = h * f1(y1, y2);
            double k21 = h * f2(y1, y2);

            double k12 = h * f1(y1 + 0.5 * k11, y2 + 0.5 * k21);
            double k22 = h * f2(y1 + 0.5 * k11, y2 + 0.5 * k21);

            double k13 = h * f1(y1 + 0.5 * k12, y2 + 0.5 * k22);
            double k23 = h * f2(y1 + 0.5 * k12, y2 + 0.5 * k22);

            double k14 = h * f1(y1 + k13, y2 + k23);
            double k24 = h * f2(y1 + k13, y2 + k23);

            y1 += (k11 + 2 * k12 + 2 * k13 + k14) / 6;
            y2 += (k21 + 2 * k22 + 2 * k23 + k24) / 6;

            ys[i][0] = y1;
            ys[i][1] = y2;
        }

        for (int i = 3; i < n; i++) {
            double f1n = f1(ys[i][0], ys[i][1]);
            double f1n1 = f1(ys[i - 1][0], ys[i - 1][1]);
            double f1n2 = f1(ys[i - 2][0], ys[i - 2][1]);

            double f2n = f2(ys[i][0], ys[i][1]);
            double f2n1 = f2(ys[i - 1][0], ys[i - 1][1]);
            double f2n2 = f2(ys[i - 2][0], ys[i - 2][1]);

            y1 = ys[i][0] + h * (23 * f1n - 16 * f1n1 + 5 * f1n2) / 12;
            y2 = ys[i][1] + h * (23 * f2n - 16 * f2n1 + 5 * f2n2) / 12;

            ys[i + 1][0] = y1;
            ys[i + 1][1] = y2;
        }

        for (int i = 0; i <= n; i++) {
            System.out.printf("Шаг %d: y1 = %.6f, y2 = %.6f%n", i, ys[i][0], ys[i][1]);
        }
    }

    public static double f1(double y1, double y2) {
        return Math.atan(1 / (1 + Math.pow(y1, 2)) + Math.pow(y2, 2));
    }

    public static double f2(double y1, double y2) {
        return Math.sin(y1 * y2);
    }
}
