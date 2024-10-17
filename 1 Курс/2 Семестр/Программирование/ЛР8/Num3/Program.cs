/*8.3.2. Совершенные числа (число равно сумме всех своих собственных делителей).*/

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Num3
{
    class Program
    {
        static void Main()
        {
            var perfectNumbers = Enumerable.Range(1, 10000).Where(n => Enumerable.Range(1, n / 2).Where(d => n % d == 0).Sum() == n);

            Console.WriteLine($"Первые {perfectNumbers.Count()} совершенных чисел:");
            foreach (var number in perfectNumbers)
            {
                Console.WriteLine(number);
            }
            Console.ReadKey();
        }
    }
}
