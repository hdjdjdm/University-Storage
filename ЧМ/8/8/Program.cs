using System;

class Program
{
    static double SQRN(double a, double b)
    {
        if (a != 0) return Math.Exp(b * Math.Log(a));
        return 0;
    }

    static double f1(double x, double y1, double y2)
    {
        return y2;
    }

    static double f2(double x, double y1, double y2)
    {
        return SQRN(2.71828182846, -x * y1);
    }

    static void Eiler(double a, double b, int n, Func<double, double, double, double> f1, Func<double, double, double, double> f2, double x, double[,] y_1)
    {
        double t = (b - a) / n;
        x = x + t;

        for (int i = 1; i <= n; i++)
        {
            Console.Write($"X = {x:F2} \t");
            for (int k = 0; k < 2; k++)
            {
                switch (k)
                {
                    case 0:
                        y_1[k, i] = y_1[k, i - 1] + t * f1(x, y_1[0, i - 1], y_1[1, i - 1]);
                        Console.Write($"Y1[{i}] = {y_1[k, i]:F2} \t");
                        break;
                    case 1:
                        y_1[k, i] = y_1[k, i - 1] + t * f2(x, y_1[0, i - 1], y_1[1, i - 1]);
                        Console.WriteLine($"Y2[{i}] = {y_1[k, i]:F2} \t");
                        break;
                }
            }
            x += t;
        }
    }

    static void Prognoz(double a, double b, int n, Func<double, double, double, double> f1, Func<double, double, double, double> f2, double x, double[,] y_1)
    {
        double t = (b - a) / n;
        x = x + t;

        for (int i = 1; i <= n; i++)
        {
            Console.Write($"X = {x:F2} \t");
            for (int k = 0; k < 2; k++)
            {
                switch (k)
                {
                    case 0:
                        y_1[k, i] = y_1[k, i - 1] + t * f1(x + 0.5 * t, y_1[0, i - 1] + 0.5 * t * y_1[0, i - 1], y_1[1, i - 1] + 0.5 * t * y_1[1, i - 1]);
                        Console.Write($"Y1[{i}] = {y_1[k, i]:F2} \t");
                        break;
                    case 1:
                        y_1[k, i] = y_1[k, i - 1] + t * f2(x + 0.5 * t, y_1[0, i - 1] + 0.5 * t * y_1[0, i - 1], y_1[1, i - 1] + 0.5 * t * y_1[1, i - 1]);
                        Console.WriteLine($"Y2[{i}] = {y_1[k, i]:F2} \t");
                        break;
                }
            }
            x += t;
        }
    }

    static double[,] RungeKut(double a, double h, int n, double x, double[,] y_1, Func<double, double, double, double> f1, Func<double, double, double, double> f2)
    {
        double[] k = new double[4];

        for (int i = 1; i <= n; i++)
        {
            Console.Write($"X = {x:F2} \t");
            for (int j = 0; j < 2; j++)
            {
                k[0] = f1(x, y_1[0, i - 1], y_1[1, i - 1]);
                k[1] = f1(x + h / 2, y_1[0, i - 1] + h / 2 * k[0], y_1[1, i - 1] + h / 2 * k[0]);
                k[2] = f1(x + h / 2, y_1[0, i - 1] + h / 2 * k[1], y_1[1, i - 1] + h / 2 * k[1]);
                k[3] = f1(x + h, y_1[0, i - 1] + h * k[2], y_1[1, i - 1] + h * k[2]);

                y_1[j, i] = y_1[j, i - 1] + h / 6 * (k[0] + 2 * k[1] + 2 * k[2] + k[3]);
                Console.Write($"Y{j}[{i}] = {y_1[j, i]:F2} \t");
            }
            Console.WriteLine();
            x += h;
        }

        return y_1;
    }

    static void Main(string[] args)
    {
        const int n = 10; 
        const double a = 1;
        const double b = 4;
        const double x = 0;
        var y_1 = new double[2, n + 1];

        Console.WriteLine("Метод Эйлера");
        Eiler(a, b, n, (x, y1, y2) => y2, (x, y1, y2) => Math.Exp(-x * y1), x, y_1);

        Console.WriteLine("\nМетод прогноза");
        Prognoz(a, b, n, (x, y1, y2) => y2, (x, y1, y2) => Math.Exp(-x * y1), x, y_1);

        Console.WriteLine("\nМетод Рунге-Кутты");
        RungeKut(a, (b - a) / n, n, x, y_1, (x, y1, y2) => y2, (x, y1, y2) => Math.Exp(-x * y1));
    }
}