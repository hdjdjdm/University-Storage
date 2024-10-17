using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Remoting.Messaging;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Lr6Num2
{
    public class Product
    {
        private string name;
        private int id;
        private int count;
        private double price;
        public Product(string name, int id, int count, double price)
        {
            this.name = name;
            this.id = id;
            this.count = count;
            this.price = price;
        }

        public string Name
        {
            get { return name; }
            set { name = value; }
        }

        public int Id
        {
            get { return id; }
            set {  id = value; }
        }

        public int Count
        {
            get { return count; }
            set { count = value; }
        }

        public double Price
        {
            get { return price; }
            set { price = value; }
        }
    }

}
