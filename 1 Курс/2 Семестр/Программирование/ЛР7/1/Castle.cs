using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace _1
{
    public class Castle : Keep
    {
        public override int HP
        {
            get { return base.hp; }
            set { base.hp = Math.Max(0, Math.Min(1600, value)); }
        }

        public Castle(string Name, int HP) : base(Name, HP)
        {
            this.Name = Name;
            this.HP = HP + 200;
            this.Cost = 2500;
        }

        protected override void changehp(bool plus)
        {
            if (plus)
            {
                if (HP <= 1600 - HPChange)
                {
                    HP += HPChange;
                    return;
                }
                HP = 1600;
                MessageBox.Show($"Максимальное хп для {Name} достигнуто");
            }
            else { HP -= HPChange; }
            if (HP < 0) { HP = 0; }
        }

        public override void ChangeHP(bool plus)
        {
            changehp(plus);
        }

        public override object Clone()
        {
            return MemberwiseClone();
        }

        public override int Repair(int money)
        {
            DialogResult result = MessageBox.Show($"Вы хотите потратить 500 золота на починку?", "Починка TownHall", MessageBoxButtons.YesNo);
            if (result == DialogResult.Yes)
            {
                if (HP >= 1600)
                {
                    MessageBox.Show("Здание не нуждается в починке");
                }
                else
                {
                    money -= 500;
                    HP = 1600;
                }
                return money;
            }
            return money;
        }
    }
}
