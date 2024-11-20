using System;

class Program
{
    static void Main(string[] args)
    {
        double[,] A = new double[,]
        {
            { 1.03, 0.995 },
            { 0.991, 0.949 }
        };

        double[] B = new double[]
        {
            2.51,
            2.45
        };

        double[] x = Givens(A, B);

        Console.WriteLine("Решение системы уравнений методом Гивенса:");
        for (int i = 0; i < x.Length; i++)
        {
            Console.WriteLine($"x[{i}] = {x[i]}");
        }

        double[] initialGuess = Gauss(A, B);
        double[] regularizedSolution = regul(2, A, B, initialGuess); // Задаем начальные приближения

        Console.WriteLine("\nРегуляризованное решение системы уравнений:");
        for (int i = 0; i < regularizedSolution.Length; i++)
        {
            Console.WriteLine($"x[{i}] = {regularizedSolution[i]}");
        }
    }

    static double[] Givens(double[,] A, double[] B)
    {
        int Nn = 2;
        double[] x = new double[Nn];

        double A_0_1 = A[0, 1];
        double M = 0.0;
        double L, R;

        for (int i = 0; i < Nn - 1; i++)
        {
            for (int k = i + 1; k < Nn; k++)
            {
                M = Math.Sqrt(A[i, i] * A[i, i] + A[k, i] * A[k, i]);
                L = A[k, i] / M;
                M = A[i, i] / M;

                for (int j = 0; j < Nn; j++)
                {
                    R = A[i, j];
                    A[i, j] = M * A[i, j] + L * A[k, j];
                    A[k, j] = M * A[k, j] - L * R;
                }

                R = B[i];
                B[i] = M * B[i] + L * B[k];
                B[k] = M * B[k] - L * R;
            }
        }

        Console.WriteLine("Матрица приняла вид после вращения Гивенса:");
        for (int i = 0; i < Nn; i++)
        {
            for (int j = 0; j < Nn; j++)
            {
                Console.Write("a[" + i + "," + j + "]=" + A[i, j] + " ");
            }
            Console.WriteLine("b[" + i + "]=" + B[i]);
        }

        x[1] = B[1] / A[1, 1];
        B[0] = 2.51;
        A[0, 0] = 1.03;
        x[0] = (B[0] - A_0_1 * x[1]) / A[0, 0];

        return x;
    }

    static double[] regul(int n, double[,] a, double[] b, double[] x0)
    {
        double[] result;
        double[,] a1 = new double[n, n], a2 = new double[n, n];
        double[] b1 = new double[n];
        double eps = 0.005;
        double s;
        int k;

        for (int i = 0; i < n; i++)
        {
            for (k = 0; k < n; k++)
            {
                s = 0;
                for (int j = 0; j < n; j++)
                {
                    s += a[j, i] * a[j, k];
                }
                a1[i, k] = s;
            }
        }

        for (int i = 0; i < n; i++)
        {
            s = 0;
            for (int j = 0; j < n; j++)
            {
                s += a[j, i] * b[j];
            }
            b1[i] = s;
        }

        double alfa = 0.001;
        k = 0;
        double[] b2 = vozm(n, eps, b1);
        double max;

        do
        {
            alfa += 0.0001;
            a2 = a1;
            for (int i = 0; i < n; i++)
            {
                a2[i, i] = a1[i, i] + alfa;
                b2[i] = b1[i] + alfa * x0[i];
            }
            a1 = a2;
            b1 = b2;

            b2 = Gauss(a2, b2);

            a2 = a1;
            result = b2;
            x0 = result;
            b2 = b1;

            b2 = Gauss(a2, b2);
            max = Math.Abs(b2[1] - result[1]);
            for (int i = 1; i < n; i++)
            {
                if (Math.Abs(b2[i] - result[i]) > max)
                {
                    max = Math.Abs(b2[i] - result[i]);
                }
            }
        } while (max > eps);

        return result;
    }

    static double[] Gauss(double[,] matrix, double[] vector)
    {
        int n = matrix.GetLength(0);
        double[] solution = new double[n];

        for (int i = 0; i < n; i++)
        {
            for (int j = i + 1; j < n; j++)
            {
                double factor = matrix[j, i] / matrix[i, i];
                for (int k = i; k < n; k++)
                {
                    matrix[j, k] -= factor * matrix[i, k];
                }
                vector[j] -= factor * vector[i];
            }
        }

        for (int i = n - 1; i >= 0; i--)
        {
            double sum = 0;
            for (int j = i + 1; j < n; j++)
            {
                sum += matrix[i, j] * solution[j];
            }
            solution[i] = (vector[i] - sum) / matrix[i, i];
        }

        return solution;
    }

    static double[] vozm(int n, double eps, double[] b)
    {
        double[] b2 = new double[n];
        for (int i = 0; i < n; i++)
        {
            b2[i] = b[i] + eps;
        }
        return b2;
    }
}