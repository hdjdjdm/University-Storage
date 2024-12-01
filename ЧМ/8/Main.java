public class Main {
    public static void main(String[] args) {
        double a = 1.0;
        double b = 4.0;
        int n = 10;
        double[] y = {1.0, 1.0};

        Function2[] TFMas = new Function2[2];
        TFMas[0] = (y1, y2) -> Math.atan(1 / (1 + Math.pow(y1, 2)) + Math.pow(y2, 2));
        TFMas[1] = (y1, y2) -> Math.sin(y1 * y2);

        System.out.println("Решение методом Эйлера:");
        Euler.solve(a, b, n, TFMas, y);

        System.out.println("\nРешение методом Эйлера-Коши:");
        EulerCauchy.solve(a, b, n, TFMas, y);

        System.out.println("\nРешение методом Рунге-Кутта:");
        RungeKutta.solve(a, b, n, TFMas, y);
    }
}
