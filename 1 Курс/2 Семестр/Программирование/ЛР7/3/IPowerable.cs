using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _3
{
    internal interface IPowerable
    {
        bool IsOn { get; set; }
        bool IsCharging { get; set; }
        int BatteryLevel { get; set; }
		bool Charged { get; set; }

        void TurnOn();
        void TurnOff();
        void Charge();

    }
}
