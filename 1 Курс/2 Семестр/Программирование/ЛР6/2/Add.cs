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

namespace Lr6Num2
{
    public partial class Add : Form
    {
        

        private void textBox2_TextChanged(object sender, EventArgs e)
        {

        }

        private void Add_Resize(object sender, EventArgs e)
        {

        }

        private Rectangle formOrigSize;

        private Storage storage = new Storage();
        List<Product> products = new List<Product>();
        private Form1 form;

        public Add(Form1 form)
        {
            InitializeComponent();
            this.form = form;
            products = storage.GetProducts();
        }

        private void Add_Load(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            string name = textBox1.Text;
            int id, count;
            double price;

            if (int.TryParse(textBox2.Text, out id)) 
            {
                foreach(Product product in products)
                {
                    if (product.Id == id)
                    {
                        MessageBox.Show("Товар с таким ID уже существует");
                        textBox2.Clear();
                    }
                }
            }
            else
            {
                textBox2.Clear();
            }
            if (int.TryParse(textBox3.Text, out count) && count >= 0) { }
            else
            {
                textBox3.Clear();
            }
            if (double.TryParse(textBox4.Text, out price) && price >= 0) { }
            else
            {
                textBox4.Clear();
            }

            if (string.IsNullOrEmpty(textBox1.Text) || string.IsNullOrEmpty(textBox2.Text) || string.IsNullOrEmpty(textBox3.Text) || string.IsNullOrEmpty(textBox4.Text))
            {
                return;
            }

            Product pr = new Product(name, id, count, price);
            storage.AddProduct(pr);
            form.RefreshListView();
            this.Close();
        }
    }
}
