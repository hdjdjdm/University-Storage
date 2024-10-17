using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text.Json;
using System.IO;
using System.Linq;
using System.Reflection.Emit;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace _1
{
    public partial class Main : Form
    {
        private int money = 20000;
        List<TownHall> townhalls = new List<TownHall>();
        List<Keep> keeps = new List<Keep>();
        List<Castle> castles = new List<Castle>();

        public Main()
        {
            InitializeComponent();
        }

        private void dataGridView1_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {
            
        }

        private void button5_Click(object sender, EventArgs e)
        {

            using (var fs = new FileStream("TownHalls.json", FileMode.Create))
            {
                if (townhalls.Count > 0)
                { 
                    JsonSerializer.Serialize<List<TownHall>>(fs, townhalls); 
                }
            }
            using (var fs = new FileStream("Keeps.json", FileMode.Create))
            {
                if (keeps.Count > 0)
                {
                    JsonSerializer.Serialize<List<Keep>>(fs, keeps);
                }
            }
            using (var fs = new FileStream("Castles.json", FileMode.Create))
            {
                if (castles.Count > 0)
                { 
                    JsonSerializer.Serialize<List<Castle>>(fs, castles); 
                }
            }
            using (StreamWriter writer = new StreamWriter("Save.txt"))
            {
                writer.Write(money);
            }


            MessageBox.Show("Данные были сохранены");
            this.Close();
        }

        private void Main_FormClosed(object sender, FormClosedEventArgs e)
        {
            Form form = Application.OpenForms[0];
            form.Close();

        }

        private void Main_Load(object sender, EventArgs e)
        {
            if (File.Exists("TownHalls.json"))
            {
                string json1 = File.ReadAllText("TownHalls.json");
                if (json1.Length != 0)
                    townhalls = JsonSerializer.Deserialize<List<TownHall>>(json1);
            }
            if (File.Exists("Keeps.json"))
            {
                string json2 = File.ReadAllText("Keeps.json");
                if (json2.Length != 0)
                    keeps = JsonSerializer.Deserialize<List<Keep>>(json2);
            }
            if (File.Exists("Castles.json"))
            {
                string json3 = File.ReadAllText("Castles.json");
                if (json3.Length != 0)
                    castles = JsonSerializer.Deserialize<List<Castle>>(json3);
            }
            if (File.Exists("Save.txt"))
            {
                money = Convert.ToInt32(File.ReadAllText("Save.txt"));
            }
            label1.Text = "Деньги: " + money;

            foreach (TownHall townhall in townhalls)
            {
                dataGridView1.Rows.Add(townhall.Name, townhall.HP, townhall.Cost);
            }
            foreach (Keep keep in keeps)
            {
                dataGridView1.Rows.Add(keep.Name, keep.HP, keep.Cost);
            }
            foreach (Castle castle in castles)
            {
                dataGridView1.Rows.Add(castle.Name, castle.HP, castle.Cost);
            }

        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (money < 1200)
            {
                MessageBox.Show("Недостаточно денег!");
                return;
            }
            money -= 1200;
            label1.Text = "Деньги " + money;

            int i = 1;
            while (true)
            {
                string name = "TownHall" + i;
                bool nameExists = false;
                foreach (TownHall townhall in townhalls)
                {
                    if (name == townhall.Name)
                    {
                        nameExists = true;
                        break;
                    }
                }
                if (!nameExists)
                {
                    break;
                }
                i++;
            }

            TownHall building = new TownHall("TownHall" + i, 1200);
            townhalls.Add(building);
            dataGridView1.Rows.Add(building.Name, building.HP, building.Cost);

        }

        private void button2_Click(object sender, EventArgs e)
        {
            foreach (DataGridViewRow row in dataGridView1.SelectedRows)
            {
                money += Convert.ToInt32(dataGridView1.Rows[dataGridView1.SelectedRows[0].Index].Cells[2].Value) / 2;
                label1.Text = "Деньги " + money;

                string buildingName = dataGridView1.Rows[dataGridView1.SelectedRows[0].Index].Cells[0].Value.ToString();
                dataGridView1.Rows.Remove(row);

                if (buildingName.Substring(0, 3) == "Tow")
                {
                    foreach (TownHall item in townhalls)
                    {
                        if (item.Name == buildingName)
                        {
                            townhalls.Remove(item);
                            break;
                        }
                    }
                }
                else if (buildingName.Substring(0, 3) == "Kee")
                {
                    foreach (Keep item in keeps)
                    {
                        if (item.Name == buildingName)
                        {
                            keeps.Remove(item);
                            break;
                        }
                    }
                }
                else
                {
                    foreach (var item in castles)
                    {
                        if (item.Name == buildingName)
                        {
                            castles.Remove(item);
                            break;
                        }
                    }
                }
            }
            
        }

        private void button3_Click(object sender, EventArgs e)
        {
            foreach (DataGridViewRow row in dataGridView1.SelectedRows)
            {
                string buildingName = dataGridView1.Rows[dataGridView1.SelectedRows[0].Index].Cells[0].Value.ToString();
                

                if (buildingName.Substring(0, 3) == "Tow")
                {
                    if (money >= 2000)
                    {
                        money -= 2000;
                        label1.Text = "Деньги " + money;
                        dataGridView1.Rows.Remove(row);
                        int i = 1;
                        while (true)
                        {
                            string name = "Keep" + i;
                            bool nameExists = false;
                            foreach (Keep keep in keeps)
                            {
                                if (name == keep.Name)
                                {
                                    nameExists = true;
                                    break;
                                }
                            }
                            if (!nameExists)
                            {
                                break;
                            }
                            i++;
                        }
                        foreach (TownHall item in townhalls)
                        {
                            if (item.Name == buildingName)
                            {
                                townhalls.Remove(item);
                                Keep keep = item.Upgrade();
                                keep.Name = "Keep" + i;
                                keeps.Add(keep);
                                dataGridView1.Rows.Add(keep.Name, keep.HP, keep.Cost);
                                break;
                            }
                        }
                    }
                    else
                    {
                        MessageBox.Show("Недостаточно денег");
                    }
                }
                else if (buildingName.Substring(0, 3) == "Kee")
                {
                    if (money >= 2500)
                    {
                        money -= 2500;
                        label1.Text = "Деньги " + money;
                        dataGridView1.Rows.Remove(row);
                        int i = 1;
                        while (true)
                        {
                            string name = "Castle" + i;
                            bool nameExists = false;
                            foreach (Castle castle in castles)
                            {
                                if (name == castle.Name)
                                {
                                    nameExists = true;
                                    break;
                                }
                            }
                            if (!nameExists)
                            {
                                break;
                            }
                            i++;
                        }
                        foreach (Keep item in keeps)
                        {
                            if (item.Name == buildingName)
                            {
                                keeps.Remove(item);
                                Castle castle = item.Upgrade();
                                castle.Name = "Castle" + i;
                                castles.Add(castle);
                                dataGridView1.Rows.Add(castle.Name, castle.HP, castle.Cost);
                                break;
                            }
                        }
                    }
                    else
                    {
                        MessageBox.Show("Недостаточно денег");
                    }
                }
                else
                {
                    MessageBox.Show("Постройка уже максимального уровня");
                }
            }
        }

        private void button4_Click(object sender, EventArgs e)
        {
            foreach (DataGridViewRow row in dataGridView1.SelectedRows)
            {
                string buildingName = dataGridView1.Rows[dataGridView1.SelectedRows[0].Index].Cells[0].Value.ToString();

                if (buildingName.Substring(0, 3) == "Tow")
                {
                    foreach (TownHall item in townhalls)
                    {
                        if (item.Name == buildingName)
                        {
                            item.ChangeHP(true);
                            dataGridView1.Rows[dataGridView1.SelectedRows[0].Index].Cells[1].Value = item.HP;
                        }
                    }
                }
                else if (buildingName.Substring(0, 3) == "Kee")
                {
                    foreach (Keep item in keeps)
                    {
                        if (item.Name == buildingName)
                        {
                            item.ChangeHP(true);
                            dataGridView1.Rows[dataGridView1.SelectedRows[0].Index].Cells[1].Value = item.HP;
                        }
                    }
                }
                else
                {
                    foreach (var item in castles)
                    {
                        if (item.Name == buildingName)
                        {
                            item.ChangeHP(true);
                            dataGridView1.Rows[dataGridView1.SelectedRows[0].Index].Cells[1].Value = item.HP;
                        }
                    }
                }
            }
        }

        private void button6_Click(object sender, EventArgs e)
        {
            foreach (DataGridViewRow row in dataGridView1.SelectedRows)
            {
                //if (Convert.ToInt32(dataGridView1.Rows[dataGridView1.SelectedRows[0].Index].Cells[1].Value) - 100 < 0)
                //    dataGridView1.Rows[dataGridView1.SelectedRows[0].Index].Cells[1].Value = 0.ToString();
                //else
                //    dataGridView1.Rows[dataGridView1.SelectedRows[0].Index].Cells[1].Value = (Convert.ToInt32(dataGridView1.Rows[dataGridView1.SelectedRows[0].Index].Cells[1].Value) - 100).ToString();
                

                string buildingName = dataGridView1.Rows[dataGridView1.SelectedRows[0].Index].Cells[0].Value.ToString();

                if (buildingName.Substring(0, 3) == "Tow")
                {
                    foreach (TownHall item in townhalls)
                    {
                        if (item.Name == buildingName)
                        {
                            item.ChangeHP(false);
                            dataGridView1.Rows[dataGridView1.SelectedRows[0].Index].Cells[1].Value = item.HP;
                        }
                    }
                }
                else if (buildingName.Substring(0, 3) == "Kee")
                {
                    foreach (Keep item in keeps)
                    {
                        if (item.Name == buildingName)
                        {
                            item.ChangeHP(false);
                            dataGridView1.Rows[dataGridView1.SelectedRows[0].Index].Cells[1].Value = item.HP;
                        }
                    }
                }
                else
                {
                    foreach (var item in castles)
                    {
                        if (item.Name == buildingName)
                        {
                            item.ChangeHP(false);
                            dataGridView1.Rows[dataGridView1.SelectedRows[0].Index].Cells[1].Value = item.HP;
                        }
                    }
                }
            }
        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void button7_Click(object sender, EventArgs e)
        {
            foreach (DataGridViewRow row in dataGridView1.SelectedRows)
            {
                string buildingName = dataGridView1.Rows[dataGridView1.SelectedRows[0].Index].Cells[0].Value.ToString();

                if (buildingName.Substring(0, 3) == "Tow")
                {
                    foreach (TownHall item in townhalls)
                    {
                        if (item.Name == buildingName)
                        {
                            money = item.Repair(money);
                            dataGridView1.Rows[dataGridView1.SelectedRows[0].Index].Cells[1].Value = item.HP;
                            label1.Text = "Деньги " + money;
                        }
                    }
                }
                else if (buildingName.Substring(0, 3) == "Kee")
                {
                    foreach (Keep item in keeps)
                    {
                        if (item.Name == buildingName)
                        {
                            money = item.Repair(money);
                            dataGridView1.Rows[dataGridView1.SelectedRows[0].Index].Cells[1].Value = item.HP;
                            label1.Text = "Деньги " + money;
                        }
                    }
                }
                else
                {
                    foreach (var item in castles)
                    {
                        if (item.Name == buildingName)
                        {
                            money = item.Repair(money);
                            dataGridView1.Rows[dataGridView1.SelectedRows[0].Index].Cells[1].Value = item.HP;
                            label1.Text = "Деньги " + money;
                        }
                    }
                }
            }
        }

        private void button8_Click(object sender, EventArgs e)
        {
            foreach (DataGridViewRow row in dataGridView1.SelectedRows)
            {
                string buildingName = dataGridView1.Rows[dataGridView1.SelectedRows[0].Index].Cells[0].Value.ToString();

                if (buildingName.Substring(0, 3) == "Tow")
                {
                    List<TownHall> buildingsToAdd = new List<TownHall>();

                    foreach (TownHall item in townhalls)
                    {
                        if (item.Name == buildingName)
                        {
                            TownHall building = (TownHall)item.Clone();
                            building.Name = buildingName + " Copy";
                            buildingsToAdd.Add(building);
                            dataGridView1.Rows.Add(building.Name, building.HP, building.Cost);
                        }
                    }

                    foreach (TownHall building in buildingsToAdd)
                    {
                        townhalls.Add(building);
                    }

                }
                else if (buildingName.Substring(0, 3) == "Kee")
                {
                    List<Keep> buildingsToAdd = new List<Keep>();

                    foreach (Keep item in keeps)
                    {
                        if (item.Name == buildingName)
                        {
                            Keep building = (Keep)item.Clone();
                            building.Name = buildingName + " Copy";
                            buildingsToAdd.Add(building);
                            dataGridView1.Rows.Add(building.Name, building.HP, building.Cost);
                        }
                    }

                    foreach (Keep building in buildingsToAdd)
                    {
                        keeps.Add(building);
                    }
                }
                else
                {
                    List<Castle> buildingsToAdd = new List<Castle>();

                    foreach (Castle item in castles)
                    {
                        if (item.Name == buildingName)
                        {
                            Castle building = (Castle)item.Clone();
                            building.Name = buildingName + " Copy";
                            buildingsToAdd.Add(building);
                            dataGridView1.Rows.Add(building.Name, building.HP, building.Cost);
                        }
                    }

                    foreach (Castle building in buildingsToAdd)
                    {
                        castles.Add(building);
                    }
                }
            }
        }
    }
}
