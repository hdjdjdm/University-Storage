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
    public partial class Form1 : Form
    {
        string TextBox;
        Storage storage = new Storage();
        List<Product> products = new List<Product>();
        bool reverseSortByName = false, reverseSortByCount = false, reverseSortByPrice = false;

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {

            RefreshListView();

        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {
            TextBox = textBox1.Text;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            int searchid;
            if (int.TryParse(TextBox, out searchid))
            {
                Product product = storage.SearchId(searchid);
                if (product == null) 
                {
                    return;
                }
                Search search = new Search(this, product);
                search.Show();
            }
            else
            {
                MessageBox.Show("Введите целое число");
            }            
        }

        private void button7_Click(object sender, EventArgs e)
        {
            Add add = new Add(this);
            add.Show();

        }

        public void RefreshListView()
        {
            products = storage.GetProducts();
            listView1.Items.Clear();
            foreach (Product product in products)
            {
                ListViewItem item = new ListViewItem(product.Id.ToString());
                item.SubItems.Add(product.Name.ToString());
                item.SubItems.Add(product.Count.ToString());
                item.SubItems.Add(product.Price.ToString("F2") + " руб.");
                listView1.Items.Add(item);
            }
        }

        private void button3_Click(object sender, EventArgs e)
        {
            products = storage.SortByName(reverseSortByName);
            RefreshListView();
            reverseSortByName = !reverseSortByName;
        }

        private void button6_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void button8_Click(object sender, EventArgs e)
        {
            int delete;
            if (int.TryParse(TextBox, out delete)) 
            {
                storage.RemoveProduct(delete);
                RefreshListView();
            }
            else
            {
                MessageBox.Show("Введите целое число");
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            string searchname = TextBox;
            Product product = storage.SearchName(searchname);
            if (product == null)
            {
                return;
            }
            Search search = new Search(this, product);
            search.Show();
        }

        private void button4_Click(object sender, EventArgs e)
        {
            products = storage.SortByCount(reverseSortByCount);
            RefreshListView();
            reverseSortByCount = !reverseSortByCount;
        }

        private void button5_Click(object sender, EventArgs e)
        {
            products = storage.SortByPrice(reverseSortByPrice);
            RefreshListView();
            reverseSortByPrice = !reverseSortByPrice;
        }
    }
}
