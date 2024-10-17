using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace _1
{
    public class TownHall : Building, ICloneable
    {
        public string Name
        {
            get { return name; }
            set { name = value; }
        }
        public int Cost
        {
            get { return cost; }
            set { cost = value; }
        }
        public virtual int HP
        {
            get { return hp; }
            set { base.hp = Math.Max(0, Math.Min(1200, value)); } 
        }


        public TownHall(string Name, int HP)
        {
            this.Name = Name;
            this.HP = HP;
            this.Cost = 1200;
        }

        protected override void changehp(bool plus)
        {
            if (plus)
            { 
                if (HP <= 1200 - HPChange)
                {
                    HP += HPChange;
                    return;
                }
                HP = 1200;
                MessageBox.Show($"Максимальное хп для {Name} достигнуто");
            }
            else { HP -= HPChange; }
            if (HP < 0) { HP = 0; }
        }
        
        public virtual void ChangeHP(bool plus)
        {
            changehp(plus);
        }

        public Keep Upgrade()
        {
            return new Keep(Name, HP);
        }

        public virtual object Clone()
        {
            return MemberwiseClone();
        }


        public virtual int Repair(int money)
        {
            DialogResult result = MessageBox.Show($"Вы хотите потратить 100 золота на починку?", "Починка TownHall", MessageBoxButtons.YesNo);
            if (result == DialogResult.Yes)
            {
                if (HP >= 1200)
                {
                    MessageBox.Show("Здание не нуждается в починке");
                }
                else
                {
                    money -= 100;
                    HP = 1200;
                }
                return money;
            }
            return money;
        }
    }
}
