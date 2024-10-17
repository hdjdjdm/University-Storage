using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Reflection.Emit;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;
using System.Windows.Forms;
using static System.Windows.Forms.LinkLabel;

namespace _3
{
    public partial class Form1 : Form
    {
        private Rectangle OriginalFormSize, OriginalButtonSize, OriginalTextBoxSize, OriginalLabelSize;
        string Filename;

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Resize(object sender, EventArgs e)
        {
            resizeControl(OriginalButtonSize, button1);
            resizeControl(OriginalTextBoxSize, textBox1);
            resizeControl(OriginalLabelSize, label1);
        }

        private void resizeControl(Rectangle r, Control c)
        {
            float xRatio = (float)(this.Width) / (float)(OriginalFormSize.Width);
            float yRatio = (float)(this.Height) / (float)(OriginalFormSize.Height);

            int newX = (int)(r.Location.X * xRatio);
            int newY = (int)(r.Location.Y * yRatio);

            int newWidth = (int)(r.Width * xRatio);
            int newHeight = (int)(r.Height * yRatio);

            if (newWidth < c.MinimumSize.Width)
            {
                newWidth = c.MinimumSize.Width;
            }

            if (newHeight < c.MinimumSize.Height)
            {
                newHeight = c.MinimumSize.Height;
            }

            c.Location = new Point(newX, newY);
            c.Size = new Size(newWidth, newHeight);
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            OriginalFormSize = new Rectangle(this.Location.X, this.Location.Y, this.Size.Width, this.Size.Height);
            OriginalButtonSize = new Rectangle(button1.Location.X, button1.Location.Y, button1.Width, button1.Height);
            OriginalTextBoxSize = new Rectangle(textBox1.Location.X, textBox1.Location.Y, textBox1.Width, textBox1.Height);
            OriginalLabelSize = new Rectangle(label1.Location.X, label1.Location.Y, label1.Width, label1.Height);
        }
        private void textBox1_TextChanged(object sender, EventArgs e)
        {
            Filename = textBox1.Text;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (File.Exists(Filename))
            {
                string ClassFile = File.ReadAllText(Filename);

                int start = ClassFile.IndexOf("class");
                int end = ClassFile.LastIndexOf("}");

                if (start == -1 || end == -1)
                {
                    MessageBox.Show("В файле не найден класс", "Ошибка");
                    return;
                }

                string Class = ClassFile.Substring(start, end - start + 1);

                MatchCollection methods = Regex.Matches(Class, @"(public|private|protected)\s+([\w<>\[\], ]+)\s+(\w+)\s*\(([\w\s,]*)\)");



                string[] DescriptionMethods = new string[methods.Count];
                for (int i = 0; i < methods.Count; i++)
                {
                    Match match = methods[i];

                    string accessModifier = match.Groups[1].Value;
                    string returnType = match.Groups[2].Value;
                    string methodName = match.Groups[3].Value;
                    string parameters = match.Groups[4].Value.Trim();

                    string description = $"Имя метода: {methodName}, Модификатор доступа: {accessModifier}, Тип возвращаемого значения: {returnType}, Параметры: {parameters}";
                    DescriptionMethods[i] = description;
                }

                File.WriteAllLines("Description.txt", DescriptionMethods);
                MessageBox.Show("Данные сохранены в Description.txt", "Выполнено");
                this.Close();
            }
            else
            {
                MessageBox.Show("Файл с таким именем не найден", "Ошибка");
            }
        }
    }
}
