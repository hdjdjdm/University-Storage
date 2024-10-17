using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _1
{
    public abstract class Building : Object
    {
        protected const int HPChange = 100;
        protected abstract void changehp(bool plus);
    }
}
