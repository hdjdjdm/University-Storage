using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _3
{
    internal class Toaster : IPowerable
    {
        public bool IsOn { get; set; }
        public bool IsCharging { get; set; }
        public int BatteryLevel { get; set; }
		public bool Charged { get; set; }

        public void TurnOn()
        {
            IsOn = true;
        }

        public void TurnOff()
        {
            IsOn = false;
        }

        public void Charge()
        {
            IsCharging = true;
			if (BatteryLevel == 100)
			{
				Charged = true;
			}
        }

    }
}
