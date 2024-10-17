import java.util.Scanner;

public class Lr3 {
    public static double[] regul(int n, double[][] a, double[] b) {
        double[] result = new double[n];
        double[][] a1 = new double[n][n];
        double[][] a2 = new double[n][n];
        double[] b1 = new double[n];
        double[] x0 = new double[n];
        double eps = 0.005;
        double s;
        int k;

        // Initialize A1 and B1
        for (int i = 0; i < n; i++) {
            for (k = 0; k < n; k++) {
                s = 0;
                for (int j = 0; j < n; j++) {
                    s += a[j][i] * a[j][k];
                }
                a1[i][k] = s;
            }
        }
        for (int i = 0; i < n; i++) {
            s = 0;
            for (int j = 0; j < n; j++) {
                s += a[j][i] * b[j];
            }
            b1[i] = s;
        }

        double alfa = 0;
        k = 0;
        double[] b2 = new double[n];
        System.arraycopy(b1, 0, b2, 0, n);

        double max;
        do {
            alfa += 1e-8;
            k++;
            for (int i = 0; i < n; i++) {
                System.arraycopy(a1[i], 0, a2[i], 0, n);
                a2[i][i] = a1[i][i] + alfa;
                b2[i] = b1[i] + alfa * x0[i];
            }

            // Solve the regularized system
            b2 = solveGauss(a2, b2);
            System.arraycopy(b2, 0, result, 0, n);
            System.arraycopy(result, 0, x0, 0, n);

            b2 = solveGauss(a2, b2);
            max = Math.abs(b2[0] - result[0]);
            for (int i = 1; i < n; i++) {
                double diff = Math.abs(b2[i] - result[i]);
                if (diff > max) {
                    max = diff;
                }
            }

            // Отладочное сообщение для отслеживания значений на каждой итерации
            System.out.println("Iteration " + k + ": max difference = " + max);

            // Добавим ограничение на количество итераций, чтобы избежать бесконечного цикла
            if (k > 1000000) {
                System.out.println("Превышено количество итераций.");
                break;
            }
        } while (max > eps);

        return result;
    }

    public static double[] solveGauss(double[][] a, double[] b) {
        int n = b.length;
        for (int i = 0; i < n; i++) {
            // Partial pivoting
            int max = i;
            for (int j = i + 1; j < n; j++) {
                if (Math.abs(a[j][i]) > Math.abs(a[max][i])) {
                    max = j;
                }
            }
            double[] temp = a[i];
            a[i] = a[max];
            a[max] = temp;

            double t = b[i];
            b[i] = b[max];
            b[max] = t;

            // Forward elimination
            for (int j = i + 1; j < n; j++) {
                double factor = a[j][i] / a[i][i];
                b[j] -= factor * b[i];
                for (int k = i; k < n; k++) {
                    a[j][k] -= factor * a[i][k];
                }
            }
        }

        // Back substitution
        double[] x = new double[n];
        for (int i = n - 1; i >= 0; i--) {
            double sum = 0.0;
            for (int j = i + 1; j < n; j++) {
                sum += a[i][j] * x[j];
            }
            x[i] = (b[i] - sum) / a[i][i];
        }
        return x;
    }

    private static void printSystem(double[][] A, double[] B) {
        int n = A.length;
        System.out.println("Исходная система:");
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (A[i][j] != 0) {
                    System.out.printf("%+.2fx%d ", A[i][j], j + 1);
                }
            }
            System.out.printf("= %.2f\n", B[i]);
        }
        System.out.println();
    }

    public static void main(String[] args) {
        double[][] A = null;
        double[] B = null;

        System.out.println("1. Задание по варианту\n2. Тест из методички");
        Scanner scanner = new Scanner(System.in);
        int choice;
        do {
            choice = Integer.parseInt(scanner.nextLine());
            switch (choice) {
                case 1:
                    A = new double[][]{
                            {1.030, 0.995},
                            {0.991, 0.949}
                    };
                    B = new double[]{2.51, 2.45};
                    break;
                case 2:
                    A = new double[][]{
                            {1.030, 0.991},
                            {0.991, 0.943}
                    };
                    B = new double[]{2.51, 2.45};
                    break;
                default:
                    System.out.println("Некорректный выбор");
                    break;
            }
        } while (choice != 1 && choice != 2);
        printSystem(A, B);

        double[] reg = regul(2, A, B);
        for (double v : reg) {
            System.out.println(v);
        }
        System.out.println();
    }
}
