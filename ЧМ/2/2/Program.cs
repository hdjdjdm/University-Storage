using System;

class Lr2
{
    public static double[] Yacobi(double[][] A, double[] B, double eps, int maxIterations)
    {
        int n = A.Length;
        double[] x = new double[n];
        double[] xNew = new double[n];
        int iterations = 0;

        if (!HasDiagonalDominance(A))
        {
            Console.WriteLine("Матрица не имеет диагонального преобладания.");
            return null;
        }

        while (iterations < maxIterations)
        {
            for (int i = 0; i < n; i++)
            {
                double sum = B[i];
                for (int j = 0; j < n; j++)
                {
                    if (j != i)
                    {
                        sum -= A[i][j] * x[j];
                    }
                }
                xNew[i] = sum / A[i][i];
            }

            bool converged = true;
            for (int i = 0; i < n; i++)
            {
                if (Math.Abs(xNew[i] - x[i]) > eps)
                {
                    converged = false;
                    break;
                }
            }

            Array.Copy(xNew, x, n);
            iterations++;
            if (converged)
            {
                break;
            }
        }

        Console.WriteLine("Количество итераций: " + iterations);
        return x;
    }

    public static double[] Zeidel(double[][] A, double[] B, double eps, int maxIterations)
    {
        int n = A.Length;
        double[] x = new double[n];
        double[] prevX = new double[n];
        int iterations = 0;

        if (!HasDiagonalDominance(A))
        {
            Console.WriteLine("Матрица не имеет диагонального преобладания.");
            return null;
        }

        for (int i = 0; i < n; i++)
        {
            x[i] = B[i] / A[i][i];
        }

        while (iterations < maxIterations)
        {
            Array.Copy(x, prevX, n);
            for (int i = 0; i < n; i++)
            {
                double sum = B[i];
                for (int j = 0; j < n; j++)
                {
                    if (i != j)
                    {
                        sum -= A[i][j] * x[j];
                    }
                }
                x[i] = sum / A[i][i];
            }

            bool converged = true;
            for (int i = 0; i < n; i++)
            {
                if (Math.Abs(x[i] - prevX[i]) > eps)
                {
                    converged = false;
                    break;
                }
            }

            iterations++;
            if (converged)
            {
                break;
            }
        }

        Console.WriteLine("Количество итераций: " + iterations);
        return x;
    }

    public static double[] ZeidelEx(double[][] A, double[] B, double w, double eps)
    {
        int n = A.Length;
        double[] x0 = new double[n];
        double[] x = new double[n];
        double e;
        int step = 0;

        if (!HasDiagonalDominance(A))
        {
            Console.WriteLine("Матрица не имеет диагонального преобладания.");
            return null;
        }

        for (int i = 0; i < n; i++)
        {
            x0[i] = B[i] / A[i][i];
        }

        do
        {
            for (int i = 0; i < n; i++)
            {
                x[i] = w * (B[i] / A[i][i]);
                for (int j = 0; j <= i - 1; j++)
                {
                    x[i] -= w * (A[i][j] * x[j] / A[i][i]);
                }
                for (int j = i + 1; j < n; j++)
                {
                    x[i] -= w * (A[i][j] * x0[j] / A[i][i]);
                }
                x[i] += (1 - w) * x0[i];
            }

            e = 0;
            for (int i = 0; i < n; i++)
            {
                if (Math.Abs(x[i] - x0[i]) > e)
                {
                    e = Math.Abs(x[i] - x0[i]);
                }
                x0[i] = x[i];
            }

            step++;
        } while (e >= eps);

        Console.WriteLine("Количество итераций: " + step);
        return x;
    }

    public static bool HasDiagonalDominance(double[][] A)
    {
        int n = A.Length;
        for (int i = 0; i < n; i++)
        {
            double sum = 0;
            for (int j = 0; j < n; j++)
            {
                if (i != j)
                {
                    sum += Math.Abs(A[i][j]);
                }
            }
            if (Math.Abs(A[i][i]) <= sum)
            {
                return false;
            }
        }
        return true;
    }

    public static void Main()
    {
        double[][] A = new double[][]
        {
            new double[] { 13.4000, 0.0581, 0.0702, 0.0822 },
            new double[] { 0.0408, 12.5000, 0.0650, 0.0770 },
            new double[] { 0.0356, 0.0477, 11.6000, 0.0718 },
            new double[] { 0.0304, 0.0425, 0.0546, 10.7000 }
        };

        double[] B = new double[] { 17.7828, 19.0599, 19.9744, 20.5261 };

        int maxIterations = 1000;
        double eps = 0.0001;

        Console.Write("Решение по методу Якоби: ");
        double[] ans1 = Yacobi(A, B, eps, maxIterations);
        if (ans1 != null)
        {
            for (int i = 0; i < ans1.Length; i++)
            {
                Console.Write($"x{i} = {ans1[i]:0.000} ");
            }
        }
        else
        {
            Console.Write("Решение не найдено ;((");
        }

        Console.Write("\nРешение по методу Зейделя: ");
        double[] ans2 = Zeidel(A, B, eps, maxIterations);
        if (ans2 != null)
        {
            for (int i = 0; i < ans2.Length; i++)
            {
                Console.Write($"x{i} = {ans2[i]:0.000} ");
            }
        }
        else
        {
            Console.Write("Решение не найдено;((");
        }

        Console.Write("\nРешение по обобщенному методу Зейделя: ");
        double w = 0.2;
        double[] ans3 = ZeidelEx(A, B, w, eps);
        if (ans3 != null)
        {
            for (int i = 0; i < ans3.Length; i++)
            {
                Console.Write($"x{i} = {ans3[i]:0.000} ");
            }
        }
        else
        {
            Console.Write("Решение не найдено;((");
        }

        Console.WriteLine("\nНажмите любую клавишу для выхода...");
        Console.ReadKey();
    }
}
