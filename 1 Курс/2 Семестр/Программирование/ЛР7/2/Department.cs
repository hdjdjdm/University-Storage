using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _2
{
    internal class Department
    {
        public string DepartmentName { get; set; }
        public List<Employee> Employees { get; set; }
        public Boss DepartmentHead { get; set; }

    }
}
