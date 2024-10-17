using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Lr5;
using System.Windows.Forms;
using System.Collections;
using static System.Windows.Forms.VisualStyles.VisualStyleElement;

namespace WindowsFormsApp1
{
    public partial class Form1 : Form
    {
        public List<Groom> grooms = new List<Groom>
            {
                new Groom("Johan", new List<Property> { Property.GoodLooking, Property.Smart, Property.Kind },
                new List<Property> { Property.Shy, Property.Smart, Property.Kind, Property.Soft }, new List<Property> { Property.Funny }),
                new Groom("David", new List<Property> { Property.Funny, Property.Kind, Property.Smart },
                new List<Property> { Property.GoodLooking, Property.Funny, Property.Soft }, new List<Property> { Property.Smart, Property.Shy }),
                new Groom("Karl", new List<Property> {Property.Shy, Property.Soft, Property.GoodLooking},
                new List<Property> {Property.Kind, Property.Smart, Property.GoodLooking}, new List<Property> { Property.Shy })
            };

        public List<Bride> brides = new List<Bride>
            {
                new Bride("Mary", new List<Property> {Property.GoodLooking, Property.Smart, Property.Kind},
                new List<Property> {Property.GoodLooking, Property.Funny, Property.Soft}, new List<Property> { Property.Shy, Property.Funny }),
                new Bride("Lisa", new List<Property> {Property.Shy, Property.Smart, Property.Kind},
                new List<Property> {Property.GoodLooking, Property.Smart, Property.Kind}, new List<Property> { Property.Shy, Property.Soft }),
                new Bride("Kate", new List<Property> {Property.Kind, Property.Funny, Property.GoodLooking},
                new List<Property> {Property.Smart, Property.Soft, Property.Kind}, new List<Property> { Property.Shy })
            };

        public Form1()
        {
            InitializeComponent();

            foreach (Groom groom in grooms)
            {
                listView1.Items.Add(groom.Name);
            }
            foreach (Bride bride in brides)
            {
                listView2.Items.Add(bride.Name);
            }
        }


        private void button1_Click(object sender, EventArgs e)
        {
            bool gend = false;
            Add add = new Add(gend, this);
            add.Owner = this;
            add.Show();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            bool gend = true;
            Add add = new Add(gend, this);
            add.Show();
        }


        private void button3_Click_1(object sender, EventArgs e)
        {
            Form2 couples = new Form2(grooms, brides);
            couples.Show();
        }


        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void button4_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void listView1_SelectedIndexChanged_1(object sender, EventArgs e)
        {
            
        }
        public void AddItemsToListView(List<string> items)
        {
            foreach (string item in items)
            {
                listView1.Items.Add(item);
            }
        }
        
        public void AddGroom(Groom groom)
        {
            grooms.Add(groom);
            ListViewItem item = new ListViewItem(groom.Name);
            listView1.Items.Add(item);
        }

        public void AddBride(Bride bride)
        {
            brides.Add(bride);
            ListViewItem item = new ListViewItem(bride.Name);
            listView2.Items.Add(item);
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }
    }
}
