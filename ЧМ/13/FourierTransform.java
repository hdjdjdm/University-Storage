import java.util.function.Function;

public class FourierTransform {

    public static void main(String[] args) {
        double a = -Math.PI;
        double b = Math.PI;
        int n = 100000;
        double startFrequency = -14.5;
        double endFrequency = 14.5;
        double frequencyStep = 1;

        Function<Double, Double> function = x -> {
            double underSqrt = x * x + 18 * x + 20;
            if (underSqrt < 0) {
                return 0.0;
            }
            return Math.sqrt(underSqrt) * Math.sin(x * x);
        };

        System.out.printf("%10s %15s %15s %15s\n", "Frequency", "Real Part", "Imag Part", "Magnitude");

        for (double frequency = startFrequency; frequency <= endFrequency; frequency += frequencyStep) {
            double freq = frequency;

            double realPart = computeIntegral(x -> function.apply(x) * Math.cos(freq * x), a, b, n);

            double imagPart = computeIntegral(x -> function.apply(x) * Math.sin(freq * x), a, b, n);

            double magnitude = Math.sqrt(realPart * realPart + imagPart * imagPart);

            System.out.printf("%10.2f %15.5f %15.5f %15.5f\n", frequency, realPart, imagPart, magnitude);
        }
    }

    public static double computeIntegral(Function<Double, Double> func, double a, double b, int n) {
        if (n % 2 != 0) {
            n++;
        }
        double h = (b - a) / n;
        double sum = func.apply(a) + func.apply(b);

        for (int i = 1; i < n; i++) {
            double x = a + i * h;
            if (i % 2 == 0) {
                sum += 2 * func.apply(x);
            } else {
                sum += 4 * func.apply(x);
            }
        }
        return sum * h / 3;
    }
}
