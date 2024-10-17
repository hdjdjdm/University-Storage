using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Collections;
using System.Xml.Linq;
using static System.Net.Mime.MediaTypeNames;
using System.Reflection;

namespace _1
{
    public partial class Form1 : Form
    {
        ArrayList list = new ArrayList();

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            RefreshListView();
        }

        private void listView1_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            string text = textBox1.Text;
            list.Add(text);
            RefreshListView();
            textBox1.Text = "";
        }

        private void button2_Click(object sender, EventArgs e)
        {
            string text = textBox1.Text;
            list.Insert(0, text);
            RefreshListView();
            textBox1.Text = "";
        }

        private void button3_Click(object sender, EventArgs e)
        {
            string text = textBox1.Text;
            int index;
            if (int.TryParse(textBox2.Text, out index))
            {
                list.Insert(index, text);
                listView1.Items.Add(text);
                textBox1.Text = "";
                textBox2.Text = "";
                RefreshListView();
            }
            else
            {
                MessageBox.Show("Введите в поле 'Индекс' число");
            }
        }

        private void RefreshListView()
        {
            listView1.Clear();
            foreach (string element in list)
            {
                ListViewItem item = new ListViewItem(element);
                listView1.Items.Add(item);
            }
            label3.Text = "Кол-во элементов: " + Convert.ToString(list.Count);
            label4.Text = "Емкость: " + list.Capacity.ToString();
        }

        private static string ReplaceSpaces(string str)
        {
            return str.Replace(" ", "_");
        }

        private static string ReplaceSlash(string str)
        {
            return str.Replace("/", "\\");
        }

        private static string ReplaceDoubleSlash(string str)
        {
            return str.Replace("/", "//");
        }

        private static string ToUpper(string str)
        {
            return str.ToUpper();
        }


        private void button4_Click(object sender, EventArgs e)
        {
            for (int i = 0; i < list.Count; i++)
            {
                list[i] = ReplaceSpaces(Convert.ToString(list[i]));
            }
            RefreshListView();
        }

        private void button5_Click(object sender, EventArgs e)
        {
            for (int i = 0; i < list.Count; i++)
            {
                list[i] = ReplaceSlash(Convert.ToString(list[i]));
            }
            RefreshListView();
        }

        private void button6_Click(object sender, EventArgs e)
        {
            for (int i = 0; i < list.Count; i++)
            {
                list[i] = ReplaceDoubleSlash(Convert.ToString(list[i]));
            }
            RefreshListView();
        }

        private void button7_Click(object sender, EventArgs e)
        {
            for (int i = 0; i < list.Count; i++)
            {
                list[i] = ToUpper(Convert.ToString(list[i]));
            }
            RefreshListView();
        }

        private void button9_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void button8_Click(object sender, EventArgs e)
        {
            int Capacity;
            if (int.TryParse(textBox2.Text, out Capacity))
            {
                if (Capacity < list.Count)
                {
                    MessageBox.Show("Введите число больше, чем количество элементов");
                    textBox2.Text = "";
                    return;
                }
                list.Capacity = Capacity;
                textBox2.Text = "";
                RefreshListView();
            }
            else
            {
                MessageBox.Show("Введите в поле 'Индекс' число");
            }
        }

        private void textBox2_TextChanged(object sender, EventArgs e)
        {

        }
    }
}
