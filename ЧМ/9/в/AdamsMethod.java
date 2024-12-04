public class AdamsMethod {
    
    interface Function {
        double evaluate(double y1, double y2);
    }

    public static void main(String[] args) {
        double a = 1.0;
        double b = 4.0;
        int n = 10;
        double x0 = a;
        double h = (b - a) / n; 

        Function[] TFMas = new Function[2];
        TFMas[0] = (y1, y2) -> Math.atan(1 / (1 + Math.pow(y1, 2)) + Math.pow(y2, 2));
        TFMas[1] = (y1, y2) -> Math.sin(y1 * y2);

        double[] y = new double[2];
        y[0] = 1.0; 
        y[1] = 1.0; 

        double[] result = adamsMethod(TFMas, y, x0, h, n);

        System.out.println("Приближенное решение:");
        for (int i = 0; i < result.length; i += 2) {
            System.out.printf("x = %.2f: y1 = %.4f; y2 = %.4f\n", a + i * h, result[i], result[i + 1]);
        }
    }

    public static double[] adamsMethod(Function[] f, double[] y, double x0, double h, int n) {
        double[] results = new double[2 * (n + 1)];
        results[0] = y[0];
        results[1] = y[1];

        for (int i = 1; i <= 2; i++) {
            double x = x0 + (i - 1) * h;
            double k1Y1 = h * f[0].evaluate(results[2 * (i - 1)], results[2 * (i - 1) + 1]);
            double k1Y2 = h * f[1].evaluate(results[2 * (i - 1)], results[2 * (i - 1) + 1]);
            results[2 * i] = results[2 * (i - 1)] + k1Y1;
            results[2 * i + 1] = results[2 * (i - 1) + 1] + k1Y2;
        }

        for (int i = 2; i < n; i++) {
            double f1Prev = f[0].evaluate(results[2 * (i - 1)], results[2 * (i - 1) + 1]);
            double f1Prev2 = f[0].evaluate(results[2 * (i - 2)], results[2 * (i - 2) + 1]);
            double f2Prev = f[1].evaluate(results[2 * (i - 1)], results[2 * (i - 1) + 1]);
            double f2Prev2 = f[1].evaluate(results[2 * (i - 2)], results[2 * (i - 2) + 1]);

            results[2 * (i + 1)] = results[2 * i] + (h / 2) * (f1Prev + f1Prev2);
            results[2 * (i + 1) + 1] = results[2 * i + 1] + (h / 2) * (f2Prev + f2Prev2);
        }

        return results;
    }
}
