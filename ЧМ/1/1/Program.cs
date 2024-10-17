using System;

public class Lr1
{
    public static double[] Gauss(double[][] A, double[] B)
    {
        int row = A.Length;
        int col = A[0].Length;
        double[] rightPart = new double[row];
        double[] answer = new double[row];
        double[][] matrix = new double[row][];

        for (int i = 0; i < row; i++)
        {
            matrix[i] = new double[col];
            Array.Copy(A[i], matrix[i], col);
            rightPart[i] = B[i];
        }

        // Прямой ход
        for (int i = 0; i < row - 1; i++)
        {
            SortRows(matrix, rightPart, i);
            for (int j = i + 1; j < row; j++)
            {
                if (matrix[i][i] != 0)
                {
                    double multElement = matrix[j][i] / matrix[i][i];
                    for (int k = i; k < col; k++)
                    {
                        matrix[j][k] -= matrix[i][k] * multElement;
                    }
                    rightPart[j] -= rightPart[i] * multElement;
                }
            }
        }

        // Обратный ход
        for (int i = row - 1; i >= 0; i--)
        {
            answer[i] = rightPart[i];
            for (int j = row - 1; j > i; j--)
            {
                answer[i] -= matrix[i][j] * answer[j];
            }
            answer[i] /= matrix[i][i];
        }

        return answer;
    }

    private static void SortRows(double[][] matrix, double[] rightPart, int currentRow)
    {
        int maxRow = currentRow;
        for (int i = currentRow + 1; i < matrix.Length; i++)
        {
            if (Math.Abs(matrix[i][currentRow]) > Math.Abs(matrix[maxRow][currentRow]))
            {
                maxRow = i;
            }
        }

        if (maxRow != currentRow)
        {
            double[] temp = matrix[currentRow];
            matrix[currentRow] = matrix[maxRow];
            matrix[maxRow] = temp;

            double tempValue = rightPart[currentRow];
            rightPart[currentRow] = rightPart[maxRow];
            rightPart[maxRow] = tempValue;
        }
    }

    public static double[] Cholesky(double[][] A, double[] b)
    {
        int n = b.Length;
        double[][] c = new double[n][];
        double[][] L = new double[n][];
        double[] y = new double[n];
        double[] x = new double[n];
        double sum;

        // Инициализация массивов
        for (int i = 0; i < n; i++)
        {
            y[i] = 0;
            c[i] = new double[n];
            L[i] = new double[n];
        }

        // Умножение матрицы на её транспонированную версию
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                sum = 0.0;
                for (int t = 0; t < n; t++)
                {
                    sum += A[t][j] * A[t][i];
                }
                c[i][j] = sum;
            }
        }

        // Умножение вектора b на транспонированную матрицу
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                y[i] += A[j][i] * b[j];
            }
        }

        // Обновление матрицы A и вектора b
        for (int i = 0; i < n; i++)
        {
            Array.Copy(c[i], A[i], n);
            b[i] = y[i];
        }

        // Разложение Холецкого
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j <= i; j++)
            {
                sum = 0;
                for (int t = 0; t < j; t++)
                {
                    sum += L[i][t] * L[j][t];
                }
                if (i != j)
                {
                    L[i][j] = (A[i][j] - sum) / L[j][j];
                }
                else
                {
                    L[i][i] = Math.Sqrt(A[i][i] - sum);
                    if (L[i][i] <= 0)
                    {
                        throw new Exception("Матрица не является положительно определённой.");
                    }
                }
            }
        }

        // Решение системы L * y = b (прямой ход)
        for (int i = 0; i < n; i++)
        {
            double sumY = 0;
            for (int j = 0; j < i; j++)
            {
                sumY += L[i][j] * y[j];
            }
            y[i] = (b[i] - sumY) / L[i][i];
        }

        // Решение системы L^T * x = y (обратный ход)
        for (int i = n - 1; i >= 0; i--)
        {
            double sumX = 0;
            for (int j = i + 1; j < n; j++)
            {
                sumX += L[j][i] * x[j];
            }
            x[i] = (y[i] - sumX) / L[i][i];
        }

        return x;
    }

    public static void Main()
    {
        double[][] A = new double[][]
        {
            new double[] { 2.16, 1.96, 1.56 },
            new double[] { 3.55, 3.23, 2.78 },
            new double[] { 4.85, 4.47, 3.97 }
        };
        double[] B = new double[] { 13.16, 21.73, 29.75 };

        double[] ans1 = Gauss(A, B);
        double[] ans2 = null;

        Console.WriteLine("\nМетод Гаусса: ");
        for (int i = 0; i < ans1.Length; i++)
        {
            Console.WriteLine($"x{i} = {ans1[i]:F3}");
        }

        try
        {
            ans2 = Cholesky(A, B);
            Console.WriteLine("\nМетод Холецкого: ");
            for (int i = 0; i < ans2.Length; i++)
            {
                Console.WriteLine($"x{i} = {ans2[i]:F3}");
            }
        }
        catch (Exception e)
        {
            Console.WriteLine("Произошла ошибка: " + e.Message);
        }

        Console.WriteLine("\nНажмите любую клавишу для выхода...");
        Console.ReadKey();
    }
}
