using System;
using System.Collections.Generic;
using System.Numerics;

namespace TaylorSeries
{
    public class Taylor
    {
        public List<taylordata> CalculateCosin(Complex x1, Complex x2, Complex delta, double epsilon)
        {
            List<taylordata> data = new List<taylordata>();
            
            for (Complex x = x1; x.Real <= x2.Real && x.Imaginary <= x2.Imaginary; x += delta)
            {
                int n;
                Complex result = 0;
                Complex term = 1;
                double error = double.MaxValue;
                n = 0;
                while (Math.Abs(error) > epsilon)
                {
                    result += term;
                    n++;
                    term *= Complex.Pow((-1), n) * Complex.Pow(x, 2 * n) / Factorial(2 * n);
                    error = (term / result).Magnitude;
                }
                Complex mathResult = Complex.Cos(x);
                Complex diff = result - mathResult;
                data.Add(new taylordata(x, result, mathResult, diff, n));
            }
            return data;
        }
        public static int Factorial(int n)
        {
            int result = 1;
            for (int i = 2; i <= n; i++)
            {
                result *= i;
            }
            return result;
        }
    }

    public class taylordata
    {
        public Complex x, result, mathResult, diff;
        public int num;
        public taylordata(Complex x, Complex result, Complex mathResult, Complex diff, int num)
        {
            this.x = x;
            this.result = result;
            this.mathResult = mathResult;
            this.diff = diff;
            this.num = num;
        }
    }
}
