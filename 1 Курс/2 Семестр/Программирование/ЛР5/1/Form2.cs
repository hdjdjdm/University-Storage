using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using Lr5;

namespace WindowsFormsApp1
{
    public partial class Form2 : Form
    {
        int page = 0;
        bool gender = false;
        private List<Groom> grooms;
        private List<Bride> brides;

        public Form2(List<Groom> grooms, List<Bride> brides)
        {
            InitializeComponent();

            button1.Enabled = false;
            this.grooms = grooms;
            this.brides = brides;
            Couples(grooms, brides);
        }

        private void listView1_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            page--;
            if (page == 0)
            {
                button1.Enabled = false;
            }
            else
            {
                button1.Enabled = true;
                button2.Enabled = true;
            }
            Couples(grooms, brides);
        }

        private void button2_Click(object sender, EventArgs e)
        {
            page++;
            if (page == grooms.Count + brides.Count - 1)
            {
                button2.Enabled = false;
            }
            else
            {
                button1.Enabled = true;
                button2.Enabled = true;
            }
            Couples(grooms, brides);
        }

        private void Couples(List<Groom> grooms, List<Bride> brides)
        {
            listView1.Items.Clear();
            listView2.Items.Clear();
            List<ScoreBrides> topbrides = new List<ScoreBrides>();
            List<ScoreGrooms> topgrooms = new List<ScoreGrooms>();

            if (page == grooms.Count)
            {
                gender = true;
            }
            else if (page < grooms.Count)
            {
                gender = false;
            }


            if (gender == false)
            {
                ListViewItem man = new ListViewItem("Мужской");
                man.SubItems.Add(grooms[page].Name);
                man.SubItems.Add(string.Join(", ", grooms[page].Prefers));
                man.SubItems.Add(string.Join(", ", grooms[page].Dislikes));
                listView1.Items.Add(man);

                //Список жен
                int score = 0;
                foreach (Bride bride in brides)
                {
                    var positive = grooms[page].Prefers.Intersect(bride.Properties); //Положительные
                    score += positive.Count();
                    var negative = grooms[page].Dislikes.Intersect(bride.Properties); //Отрицательные
                    score -= negative.Count();
                    ScoreBrides sb = new ScoreBrides(bride.Name, bride.Properties, score);
                    topbrides.Add(sb);
                    score = 0;
                }
                topbrides.Sort((x, y) => y.Score.CompareTo(x.Score)); //Топ

                foreach (ScoreBrides bride in topbrides)
                {
                    ListViewItem brds = new ListViewItem(bride.Name);
                    brds.SubItems.Add(Convert.ToString(bride.Score));
                    brds.SubItems.Add(string.Join(", ", bride.Properties));
                    listView2.Items.Add(brds);
                }

                //Очистка
                topbrides.Clear();
            }
            else
            {
                ListViewItem woman = new ListViewItem("Женский");
                woman.SubItems.Add(brides[page-grooms.Count].Name);
                woman.SubItems.Add(string.Join(", ", brides[page - grooms.Count].Prefers));
                woman.SubItems.Add(string.Join(", ", brides[page - grooms.Count].Dislikes));
                listView1.Items.Add(woman);

                //Список парней
                int score = 0;
                foreach (Groom groom in grooms)
                {
                    var positive = brides[page - grooms.Count].Prefers.Intersect(groom.Properties); //Положительные
                    score += positive.Count();
                    var negative = brides[page - grooms.Count].Dislikes.Intersect(groom.Properties); //Отрицательные
                    score -= negative.Count();
                    ScoreGrooms sb = new ScoreGrooms(groom.Name, groom.Properties, score);
                    topgrooms.Add(sb);
                    score = 0;
                }

                topgrooms.Sort((x, y) => y.Score.CompareTo(x.Score)); //Топ
                foreach (ScoreGrooms groom in topgrooms)
                {
                    ListViewItem grms = new ListViewItem(groom.Name);
                    grms.SubItems.Add(Convert.ToString(groom.Score));
                    grms.SubItems.Add(string.Join(", ", groom.Properties));
                    listView2.Items.Add(grms);
                }

                //Очистка
                topgrooms.Clear();
            }
        }
    }
}
