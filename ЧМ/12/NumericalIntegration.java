import java.util.function.DoubleUnaryOperator;

public class NumericalIntegration {
    private static final DoubleUnaryOperator function = (x) -> Math.exp(-(x + 1/x));

    public static double rectangleMethod(DoubleUnaryOperator func, double a, double b, int n) {
        double h = (b - a) / n;
        double sum = 0.0;
        for (int i = 0; i < n; i++) {
            double x = a + i * h;
            sum += func.applyAsDouble(x);
        }
        return sum * h;
    }

    public static double trapezoidMethod(DoubleUnaryOperator func, double a, double b, int n) {
        double h = (b - a) / n;
        double sum = (func.applyAsDouble(a) + func.applyAsDouble(b)) / 2.0;
        for (int i = 1; i < n; i++) {
            double x = a + i * h;
            sum += func.applyAsDouble(x);
        }
        return sum * h;
    }

    public static double simpsonMethod(DoubleUnaryOperator func, double a, double b, int n) {
        if (n % 2 != 0) {
            n++;
        }
        double h = (b - a) / n;
        double sum = func.applyAsDouble(a) + func.applyAsDouble(b);

        for (int i = 1; i < n; i += 2) {
            double x = a + i * h;
            sum += 4 * func.applyAsDouble(x);
        }
        for (int i = 2; i < n - 1; i += 2) {
            double x = a + i * h;
            sum += 2 * func.applyAsDouble(x);
        }
        return sum * h / 3.0;
    }
	
    public static double gaussMethod(DoubleUnaryOperator func, double a, double b) {

        double[] points = { -1.0 / Math.sqrt(3), 1.0 / Math.sqrt(3) };
        double[] weights = { 1.0, 1.0 };

        double mid = (a + b) / 2.0;
        double halfLength = (b - a) / 2.0;

        double integral = 0.0;
        for (int i = 0; i < points.length; i++) {
            double x = mid + halfLength * points[i];
            integral += weights[i] * func.applyAsDouble(x);
        }
        return integral * halfLength;
    }

    public static void main(String[] args) {
        double a = 1;
        double b = 2;
        int n = 1000;

        double rectangleResult = rectangleMethod(function, a, b, n);
        double trapezoidResult = trapezoidMethod(function, a, b, n);
        double simpsonResult = simpsonMethod(function, a, b, n);
		double gaussResult = gaussMethod(function, a, b);

        System.out.printf("Значение интеграла методом прямоугольников: %.6f%n", rectangleResult);
        System.out.printf("Значение интеграла методом трапеций: %.6f%n", trapezoidResult);
        System.out.printf("Значение интеграла Симпсона: %.6f%n", simpsonResult);
		System.out.printf("Значение интеграла Гаусса: %.6f%n", gaussResult);
    }
}
