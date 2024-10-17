using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace _1
{
    public class Keep : TownHall
    {
        public override int HP
        {
            get { return base.hp; }
            set { base.hp = Math.Max(0, Math.Min(1400, value)); }
        }   

        public Keep(string Name, int HP) : base(Name, HP)
        {
            this.Name = Name;
            this.HP = HP + 200;
            this.Cost = 2000;
        }

        protected override void changehp(bool plus)
        {
            if (plus)
            {
                if (HP <= 1400 - HPChange)
                {
                    HP += HPChange;
                    return;
                }
                HP = 1400;
                MessageBox.Show($"Максимальное хп для {Name} достигнуто");
            }
            else { HP -= HPChange; }
            if (HP < 0) { HP = 0; }
        }

        public override void ChangeHP(bool plus)
        {
            changehp(plus);
        }

        public new Castle Upgrade()
        {
            return new Castle(Name, HP);
        }

        public override object Clone()
        {
            return MemberwiseClone();
        }

        public override int Repair(int money)
        {
            DialogResult result = MessageBox.Show($"Вы хотите потратить 250 золота на починку?", "Починка TownHall", MessageBoxButtons.YesNo);
            if (result == DialogResult.Yes)
            {
                if (HP >= 1400)
                {
                    MessageBox.Show("Здание не нуждается в починке");
                }
                else
                {
                    money -= 250;
                    HP = 1400;
                }
                return money;
            }
            return money;
        }
    }
}
