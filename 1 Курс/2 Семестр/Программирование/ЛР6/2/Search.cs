using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using static System.Windows.Forms.VisualStyles.VisualStyleElement;

namespace Lr6Num2
{
    public partial class Search : Form
    {
        private Form1 form;
        Storage storage = new Storage();
        Product product;
        int newCount;
        double NewPrice;

        public Search(Form1 form, Product product)
        {
            InitializeComponent();
            this.form = form;
            this.product = product;
        }


        private void Search_Load(object sender, EventArgs e)
        {
            textBox1.ReadOnly = true;
            textBox2.ReadOnly = true;
            textBox1.Text = product.Name;
            textBox2.Text = Convert.ToString(product.Id);
            textBox3.Text = Convert.ToString(product.Count);
            textBox4.Text = Convert.ToString(product.Price);
        }

        private void button1_Click(object sender, EventArgs e)
        {
            product.Price = NewPrice;
            product.Count = newCount;
            storage.ChangeProduct(product, product.Id);
            form.RefreshListView();
            this.Close();
        }

        private void textBox4_TextChanged(object sender, EventArgs e)
        {
            if (double.TryParse(textBox4.Text, out NewPrice) || textBox4.Text == "") { }
            else
            {
                textBox4.Clear();
                MessageBox.Show("Введите положительное число");
            }
        }

        private void textBox3_TextChanged(object sender, EventArgs e)
        {
            if (int.TryParse(textBox3.Text, out newCount) || textBox3.Text == "") { }
            else
            {
                textBox3.Clear();
                MessageBox.Show("Введите целое положительное число");
            }
        }
    }
}
