using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Drawing.Text;
using System.Linq;
using System.Numerics;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using static System.Windows.Forms.VisualStyles.VisualStyleElement;

namespace WindowsFormsApp2
{
    public partial class Form1 : Form
    {
        private Rectangle buttonOrigSize, textBox1Orig, textBox2Orig, textBox3Orig, textBox4Orig, label2Orig, label3Orig, label4Orig, label5Orig, pictureBox1Orig;
        private Rectangle formOrigSize;

        Complex x1, x2, delta;
        double epsilon;

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            formOrigSize = new Rectangle(this.Location.X, this.Location.Y, this.Size.Width, this.Size.Height);
            buttonOrigSize = new Rectangle(button1.Location.X, button1.Location.Y, button1.Width, button1.Height);
            textBox1Orig = new Rectangle(textBox1.Location.X, textBox1.Location.Y, textBox1.Width, textBox1.Height);
            textBox2Orig = new Rectangle(textBox2.Location.X, textBox2.Location.Y, textBox2.Width, textBox2.Height);
            textBox3Orig = new Rectangle(textBox3.Location.X, textBox3.Location.Y, textBox3.Width, textBox3.Height);
            textBox4Orig = new Rectangle(textBox4.Location.X, textBox4.Location.Y, textBox4.Width, textBox4.Height);
            label2Orig = new Rectangle(label2.Location.X, label2.Location.Y, label2.Width, label2.Height);
            label3Orig = new Rectangle(label3.Location.X, label3.Location.Y, label3.Width, label3.Height);
            label4Orig = new Rectangle(label4.Location.X, label4.Location.Y, label4.Width, label4.Height);
            label5Orig = new Rectangle(label5.Location.X, label5.Location.Y, label5.Width, label5.Height);
            pictureBox1Orig = new Rectangle(pictureBox1.Location.X, pictureBox1.Location.Y, pictureBox1.Width, pictureBox1.Height);
        }

        private void label5_Click(object sender, EventArgs e)
        {

        }

        private void label4_Click(object sender, EventArgs e)
        {

        }

        private void label3_Click(object sender, EventArgs e)
        {

        }

        private void resizeControl(Rectangle r, Control c)
        {
            float xRatio = (float)(this.Width) / (float)(formOrigSize.Width);
            float yRatio = (float)(this.Width) / (float)(formOrigSize.Height);

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

        private void Form1_Resize(object sender, EventArgs e)
        {
            resizeControl(buttonOrigSize, button1);
            resizeControl(textBox1Orig, textBox1);
            resizeControl(textBox2Orig, textBox2);
            resizeControl(textBox3Orig, textBox3);
            resizeControl(textBox4Orig, textBox4);
            resizeControl(label2Orig, label2);
            resizeControl(label3Orig, label3);
            resizeControl(label4Orig, label4);
            resizeControl(label5Orig, label5);
            resizeControl(pictureBox1Orig, pictureBox1);
        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void label2_Click(object sender, EventArgs e)
        {

        }

        private void pictureBox1_Click(object sender, EventArgs e)
        {

        }

        private void textBox2_TextChanged(object sender, EventArgs e)
        {
            x2 = InpComplex(textBox2);
        }

        private void textBox3_TextChanged(object sender, EventArgs e)
        {
            delta = InpComplex(textBox3);
        }

        private void textBox4_TextChanged(object sender, EventArgs e)
        {
            string inp = textBox4.Text;

            if (double.TryParse(inp, out epsilon))
            {

            }
            else
            {
                textBox4.Clear();
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            Form2 table = new Form2(x1, x2, delta, epsilon);
            //this.Hide();
            table.Show();
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {
            x1 = InpComplex(textBox1);

        }
        private Complex InpComplex(System.Windows.Forms.TextBox textbox)
        {
            string inp = textbox.Text;

            bool znak = inp.StartsWith("-");
            if (znak == true)
            {
                inp = inp.Remove(0, 1);
            }

            string[] parts = inp.Split('+', '-');
            double real = 0;
            double imaginary = 0;


            if (parts.Length == 2)
            {

                if (double.TryParse(parts[0], out real))
                {
                    if (znak == true)
                    {
                        real = -real;
                    }

                    if (double.TryParse(parts[1].TrimEnd('i'), out imaginary))
                    {

                        if (inp.IndexOf('+') >= 0)
                        {
                            imaginary = Math.Abs(imaginary);
                        }
                        else if (inp.IndexOf('-') >= 0)
                        {
                            imaginary = -Math.Abs(imaginary);
                        }

                        Complex num = new Complex(real, imaginary);
                        return num;
                    }
                }
            }
            else
            {
                if (inp.Contains("i"))
                {
                    real = 0;

                    if (double.TryParse(parts[0].TrimEnd('i'), out imaginary))
                    {
                        if (znak == false)
                        {
                            imaginary = Math.Abs(imaginary);
                        }
                        else
                        {
                            imaginary = -Math.Abs(imaginary);
                        }

                        Complex num = new Complex(real, imaginary);
                        return num;
                    }
                }
                else
                {
                    if (double.TryParse(parts[0], out real))
                    {
                        if (znak == true)
                        {
                            real = -real;
                        }
                        imaginary = 0;
                        Complex num = new Complex(real, imaginary);
                        return num;
                    }
                }
            }
            return 0;
        }
        
    }
}
