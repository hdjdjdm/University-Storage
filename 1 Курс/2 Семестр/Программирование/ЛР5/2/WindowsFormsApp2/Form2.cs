using System;
using System.Collections;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Numerics;
using System.Runtime.Remoting;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using TaylorSeries;
using static System.Windows.Forms.VisualStyles.VisualStyleElement;
using static System.Windows.Forms.VisualStyles.VisualStyleElement.ToolBar;

namespace WindowsFormsApp2
{
    public partial class Form2 : Form
    {
        public Taylor tlr = new Taylor();
        Complex x1, x2, delta;
        double epsilon;

        private void Form2_Load(object sender, EventArgs e)
        {

        }
        public Form2(Complex x1, Complex x2, Complex delta, double epsilon)
        {
            InitializeComponent();
            this.x1 = x1;
            this.x2 = x2;
            this.delta = delta;
            this.epsilon = epsilon;

            Taylor taylor = new Taylor();
            List<taylordata> data = taylor.CalculateCosin(x1, x2, delta, epsilon);

            foreach (taylordata obj in data)
            {
                ListViewItem item = new ListViewItem();
                if (obj.x.Imaginary >= 0)
                {
                    item.Text = obj.x.Real.ToString("G2") + " + " + obj.x.Imaginary.ToString("G2") + "i";
                }
                else
                {
                    item.Text = obj.x.Real.ToString("G2") + obj.x.Imaginary.ToString("G2") + "i";
                }

                if (obj.result.Imaginary >= 0)
                {
                    item.SubItems.Add(obj.result.Real.ToString("G2") + " + " + obj.result.Imaginary.ToString("G2") + "i");
                }
                else
                {
                    item.SubItems.Add(obj.result.Real.ToString("G2") + obj.result.Imaginary.ToString("G2") + "i");
                }

                if (obj.mathResult.Imaginary >= 0)
                {
                    item.SubItems.Add(obj.mathResult.Real.ToString("G2") + " + " + obj.mathResult.Imaginary.ToString("G2") + "i");
                }
                else
                {
                    item.SubItems.Add(obj.mathResult.Real.ToString("G2") + obj.mathResult.Imaginary.ToString("G2") + "i");
                }

                if (obj.diff.Imaginary >= 0)
                {
                    item.SubItems.Add(obj.diff.Real.ToString("G2") + " + " + obj.diff.Imaginary.ToString("G2") + "i");
                }
                else
                {
                    item.SubItems.Add(obj.diff.Real.ToString("G2") + obj.diff.Imaginary.ToString("G2") + "i");
                }

                item.SubItems.Add(obj.num.ToString());
                listView1.Items.Add(item);

            }
        }

        private void listView1_SelectedIndexChanged(object sender, EventArgs e)
        {
            
        }
    }
}
