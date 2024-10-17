using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Reflection.Emit;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Lr6Num1
{
    public partial class Form1 : Form
    {
        private Rectangle OriginalFormSize, OriginalButtonSize, OriginalTextBox1Size, OriginalTextBox2Size, OriginalLabel1Size, OriginalLabel2Size;
        int n, m;

        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (string.IsNullOrEmpty(textBox1.Text) || string.IsNullOrEmpty(textBox2.Text))
            {
                MessageBox.Show("Ошибка! Не все поля заполнены!");
            }
            else
            {
                Form2 matrix = new Form2(n, m);
                matrix.Show();
            }
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            OriginalFormSize = new Rectangle(this.Location.X, this.Location.Y, this.Size.Width, this.Size.Height);
            OriginalButtonSize = new Rectangle(button1.Location.X, button1.Location.Y, button1.Width, button1.Height);
            OriginalTextBox1Size = new Rectangle(textBox1.Location.X, textBox1.Location.Y, textBox1.Width, textBox1.Height);
            OriginalTextBox2Size = new Rectangle(textBox2.Location.X, textBox2.Location.Y, textBox2.Width, textBox2.Height);
            OriginalLabel1Size = new Rectangle(label1.Location.X, label1.Location.Y, label1.Width, label1.Height);
            OriginalLabel2Size = new Rectangle(label2.Location.X, label2.Location.Y, label2.Width, label2.Height);
        }
        private void resizeControl(Rectangle r, Control c)
        {
            float xRatio = (float)(this.Width) / (float)(OriginalFormSize.Width);
            float yRatio = (float)(this.Width) / (float)(OriginalFormSize.Height);

            int newX = (int)(r.Location.X * xRatio);
            int newY = (int)(r.Location.Y * yRatio);

            int newWidth = (int)(r.Width * xRatio);
            int newHeight = (int)(r.Height * yRatio);

            c.Location = new Point(newX, newY);
            c.Size = new Size(newWidth, newHeight);
        }
        private void Form1_Resize(object sender, EventArgs e)
        {
            resizeControl(OriginalButtonSize, button1);
            resizeControl(OriginalTextBox1Size, textBox1);
            resizeControl(OriginalTextBox2Size, textBox2);
            resizeControl(OriginalLabel1Size, label1);
            resizeControl(OriginalLabel2Size, label2);
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {
            string inp = textBox1.Text;
            if (int.TryParse(inp, out int n))
            {
                this.n = n;
            }
            else
            {
                textBox1.Text = "";
                if (inp.Length > 0)
                {
                    MessageBox.Show("Ошибка! Введено не целое число!");
                }
            }
        }


        private void textBox2_TextChanged(object sender, EventArgs e)
        {
            string inp = textBox2.Text;
            if (int.TryParse(inp, out int m))
            {
                this.m = m;
            }
            else
            {
                textBox2.Text = "";
                if (inp.Length > 0)
                {
                    MessageBox.Show("Ошибка! Введено не целое число!");
                }
            }
        }
    }
}
