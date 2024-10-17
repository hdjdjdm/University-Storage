using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _3
{
    class Person
    {
        string name;
        int age;

        public bool Teen(string name, int age)
        {
            if (person.age < 18)
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        public void PrintPerson(Person person)
        {
            Console.WriteLine($"Имя: {person.name}, Возраст: {person.age}");
        }

        public void TrueAge(int age)
        {
            if (age >= 0 && age < 110)
            {
                Console.WriteLine("Возраст правильный");
            }
            else
            {
                Console.WriteLine("Возраст неправильный");
            }
        }
    }
}
