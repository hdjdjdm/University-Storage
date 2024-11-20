public class Main {
    public static void main(String[] args) {
        int n = 20;
        double[] x = new double[n];
        for (int i = 0; i < x.length; i++) {
            x[i] = i + 1;
        }

        double[] y = {2.15, 2.41, 2.58, 2.84, 3.28, 3.46, 4.02, 4.11, 4.61, 5.03,
                5.34, 5.86, 6.33, 6.81, 7.21, 7.67, 8.23, 8.68, 9.35, 9.93};

        CubicSplineInterpolation splineInterpolation = new CubicSplineInterpolation(x, y);
        NewtonPolynomial newtonPolynomial = new NewtonPolynomial(x, y);
        LeastSquaresApproximation approximation = new LeastSquaresApproximation(x, y);

        System.out.printf("Интерполяционный полином Лагранжа:\n");
        for (double q = 1.0; q <= 20.0; q += 0.5) {
            double lagrangeResult = LagrangeInterpolation.interpolate(x, y, q);
            System.out.printf("f(%.2f) = %.4f%n", q, lagrangeResult);
        }

        System.out.printf("Интерполирование функций с помощью кубического сплайна:\n");
        for (double q = 1.0; q <= 20.0; q += 0.5) {
            double cubicResult = splineInterpolation.interpolate(q);
            System.out.printf("f(%.2f) = %.4f%n", q, cubicResult);
        }

        System.out.printf("Приближение полиномами Ньютона:\n");
        for (double q = 1.0; q <= 20.0; q += 0.5) {
            double newtonResult = newtonPolynomial.interpolate(q);
            System.out.printf("f(%.2f) = %.4f%n", q, newtonResult);
        }

        System.out.printf("Аппроксимация функций методом наименьших квадратов многочленом второй степени:\n");
        for (double q = 1.0; q <= 20.0; q += 0.5) {
            double approximateResult = approximation.approximate(q);
            System.out.printf("f(%.2f) = %.4f%n", q, approximateResult);
        }
    }
}
