using System;
using System.Collections;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Security.AccessControl;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using Lr5;
using static System.Windows.Forms.VisualStyles.VisualStyleElement;

namespace WindowsFormsApp1
{
    public partial class Add : Form
    {
        private bool gender;
        private Form1 Mainform;
        public Add(bool gend, Form1 form)
        {
            InitializeComponent();
            gender = gend;
            Mainform = form;

        }

        private void Add_Load(object sender, EventArgs e)
        {

        }

        private void checkedListBox1_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }
        private void checkedListBox1_ItemCheck(object sender, ItemCheckEventArgs e)
        {
            
        }
        


        private void button1_Click(object sender, EventArgs e)
        {
            if (string.IsNullOrEmpty(textBox1.Text))
            {
                return;
            }
            string Name = textBox1.Text; //Имя

            //Свойства
            List<Property> Properties = new List<Property>();
            List<Property> Prefers = new List<Property>();
            List<Property> Dislikes = new List<Property>();

            foreach (object item in checkedListBox1.CheckedItems)
            {
                if (Enum.TryParse(item.ToString(), out Property property))
                {
                    Properties.Add(property);
                }
            }
            foreach (object item in checkedListBox2.CheckedItems)
            {
                if (Enum.TryParse(item.ToString(), out Property property))
                {
                    Prefers.Add(property);
                }
            }
            foreach (object item in checkedListBox3.CheckedItems)
            {
                if (Enum.TryParse(item.ToString(), out Property property))
                {
                    Dislikes.Add(property);
                }
            }
            if (gender == false)
            {
                Groom gr = (new Groom(Name, Properties, Prefers, Dislikes));
                Mainform.AddGroom(gr);
            }
            else
            {
                Bride br = new Bride(Name, Properties, Prefers, Dislikes);
                Mainform.AddBride(br);
            }
            this.Close();
        }

        private void listBox2_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void checkedListBox1_SelectedIndexChanged_1(object sender, EventArgs e)
        {

        }
    }
}
