using Microsoft.VisualBasic;
using System;
using System.Collections.Generic;
using System.Linq;

class Program
{
    static void Main(string[] args)
    {
        Console.WriteLine($"Метод Ньютона:");
        NewtonMethodSolve();

        Console.WriteLine($"Метод простых итераций:");
        SimpleIterationMethodSolve();
    }

    private static void NewtonMethodSolve()
    {
        const int n = 2;
        const double epsilon = 1e-7;
        const int maxIterations = 100;

        double[] x = { 0, 0 };
        double[] deltaX = new double[n];
        double[] F = new double[n];
        double[,] J = new double[n, n];

        int iteration = 0;

        do
        {
            F[0] = Math.Cos(x[0] + 0.5) + x[1] - 0.8;
            F[1] = Math.Sin(x[1]) - 2 * x[0] - 1.6;

            J[0, 0] = -Math.Sin(x[0] + 0.5);
            J[0, 1] = 1;
            J[1, 0] = -2;
            J[1, 1] = Math.Cos(x[1]);

            deltaX = Gauss(J, F);

            for (int i = 0; i < n; ++i)
                x[i] -= deltaX[i];

            Console.WriteLine($"{iteration + 1}:\tx = ({x[0]:F10}, {x[1]:F10})");

            iteration++;
        } while (MaxAbs(deltaX) > epsilon && iteration < maxIterations);

        Console.WriteLine($"\nРешение найдено за {iteration} итераций.");

        Console.WriteLine($"x = ({x[1]:F10}, {x[0]:F10})\n");
    }

    private static void SimpleIterationMethodSolve()
    {
        const int maxIterations = 100;
        const double epsilon = 1e-7;

        double x = 0, y = 0;
        double newX, newY;

        for (int i = 0; i < maxIterations; ++i)
        {
            newX = 0.8 - Math.Cos(y + 0.5);
            newY = (Math.Sin(x) - 1.6) / 2;

            if (Math.Abs(newX - x) < epsilon && Math.Abs(newY - y) < epsilon)
            {
                Console.WriteLine($"\nРешение найдено за {i + 1} итераций.");
                Console.WriteLine($"x = {newX:F10}, y = {newY:F10}");
                return;
            }

            x = newX;
            y = newY;

            Console.WriteLine($"{i + 1}:\tx = {x:F10}, y = {y:F10}");
        }

        Console.WriteLine("Максимальное число итераций достигнуто без достижения требуемой точности.");
    }

    private static double MaxAbs(double[] array)
    {
        return array.Max(Math.Abs);
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
}