/* 5.1.2. “Женихи и невесты". Есть N женихов и M невест. Каждый хочет найти свою пару.
У каждого есть свои предпочтения.
Девушка хочет найти жениха. Кандидатов достаточно много. Известен список бинарных свойств, которые
девушка хочет знать о своих женихах. Часть из этих свойств девушка относит к положительным, часть —
к отрицательным. Девушка хочет из списка кандидатов составить список предпочтительных кандидатов,
упорядоченный по степени предпочтения. Предложите ей разумный алгоритм и реализуйте его.
Указание: список свойств следует задать перечислением, представляющим шкалу.
Следует определить класс Groom, среди полей которого будет поле properties, заданное
перечислением.
Юноша хочет найти невесту. Кандидатов достаточно много. Известен список бинарных свойств, которые
молодой человек хочет знать о претендентках. Часть из этих свойств юноша относит к положительным,
часть — к отрицательным. Юноше требуется из списка претенденток составить список предпочтительных
невест, упорядоченный по степени предпочтения. Предложите разумный алгоритм и реализуйте его.
Указание: список свойств следует задать перечислением, представляющим шкалу.
Следует определить класс Bride, среди полей которого будет поле properties, заданное
перечислением.
Необходимо создать Windows-проект, моделирующий решение задачи создания пар. Эту задачу можно
рассматривать как вариацию известной задачи "об устойчивом бракосочетании". */

using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Text.RegularExpressions;
using System.Threading;
using WindowsFormsApp1;

namespace Lr5
{
    internal static class Num1
    {
        /// <summary>
        /// Главная точка входа для приложения.
        /// </summary>
        [STAThread]
        static void Main()
        {
            //Вариант
            int variant = (14 - 1) % 3 + 1; // = 2
            Console.WriteLine($"Вариант {variant}\n");


            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new Form1());

            List<Groom> grooms = new List<Groom>
            {
                new Groom("Johan", new List<Property> { Property.GoodLooking, Property.Smart, Property.Kind },
                new List<Property> { Property.Shy, Property.Smart, Property.Kind, Property.Soft }, new List<Property> { Property.Funny }),
                new Groom("David", new List<Property> { Property.Funny, Property.Kind, Property.Smart },
                new List<Property> { Property.GoodLooking, Property.Funny, Property.Soft }, new List<Property> { Property.Smart, Property.Shy }),
                new Groom("Karl", new List<Property> {Property.Shy, Property.Soft, Property.GoodLooking},
                new List<Property> {Property.Kind, Property.Smart, Property.GoodLooking}, new List<Property> { Property.Shy })
            };

            List<Bride> brides = new List<Bride>
            {
                new Bride("Mary", new List<Property> {Property.GoodLooking, Property.Smart, Property.Kind},
                new List<Property> {Property.GoodLooking, Property.Funny, Property.Soft}, new List<Property> { Property.Shy, Property.Funny }),
                new Bride("Lisa", new List<Property> {Property.Shy, Property.Smart, Property.Kind},
                new List<Property> {Property.GoodLooking, Property.Smart, Property.Kind}, new List<Property> { Property.Shy, Property.Soft }),
                new Bride("Kate", new List<Property> {Property.Kind, Property.Funny, Property.GoodLooking},
                new List<Property> {Property.Smart, Property.Soft, Property.Kind}, new List<Property> { Property.Shy })
            };

        

        }

    }

    public class Groom // Муж
    {
        public string Name;
        public List<Property> Properties;
        public List<Property> Prefers;
        public List<Property> Dislikes;
        public Groom(String name, List<Property> properties, List<Property> prefers, List<Property> dislikes)
        {
            Name = name;
            Properties = properties;
            Prefers = prefers;
            Dislikes = dislikes;
        }
    }

    public class Bride // Невеста
    {
        public string Name;
        public List<Property> Properties;
        public List<Property> Prefers;
        public List<Property> Dislikes;
        public Bride(String name, List<Property> properties, List<Property> prefers, List<Property> dislikes)
        {
            Name = name;
            Properties = properties;
            Prefers = prefers;
            Dislikes = dislikes;
        }
    }

    public class ScoreGrooms
    {
        public string Name;
        public List<Property> Properties;
        public int Score;
        public ScoreGrooms(String name, List<Property> properties, int score)
        {
            Name = name;
            Score = score;
            Properties = properties;
        }
    }

    public class ScoreBrides
    {
        public string Name;
        public List<Property> Properties;
        public int Score;
        public ScoreBrides(String name, List<Property> properties, int score)
        {
            Name = name;
            Score = score;
            Properties = properties;
        }
    }


    public enum Property
    {
        GoodLooking,
        Kind,
        Soft,
        Funny,
        Shy,
        Smart
    };
}
