using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Lr6Num1
{
    public partial class Form2 : Form
    {
        int n, m;

        public Form2(int n, int m)
        {
            InitializeComponent();
            this.n = n;
            this.m = m;
        }

        private void dataGridView1_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {

        }

        private void Form2_Load(object sender, EventArgs e)
        {
            int[,] matr = new int[n, m];

            int k = 0;
            for (int d = 0; d < n + m - 1; d++)
            {
                for (int i = 0; i < n; i++)
                {
                    int r = d - i;
                    if (r >= 0 && r < m)
                    {
                        matr[i, r] = k++;
                    }
                }
            }

            dataGridView1.ColumnCount = m;
            for (int i = 0; i < n; i++)
            {
                dataGridView1.Rows.Add();
                for (int j = 0; j < m; j++)
                {
                    dataGridView1.Rows[i].Cells[j].Value = matr[i, j].ToString();
                }
            }

        }
    }
}
/*
 0  1   3   6   10  14 
 2  4   7   11  15  18
 5  8   12  16  19  21
 9  13  17  20  22  23

*/
