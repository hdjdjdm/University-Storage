using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _2
{
    internal class Employee : Person
    {
        public int EmployeeId { get; set; }
        public decimal Salary { get; set; }
        public Department Department { get; set; }

    }
}
