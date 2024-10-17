using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _4
{
    internal class Shuttle : IComparable<Shuttle>, IEnumerable<string>
    {
        public string Name { get; set; }
        public int Capacity { get; set; }
        public double Speed { get; set; }

        public Shuttle(string name, int capacity, double speed)
        {
            Name = name;
            Capacity = capacity;
            Speed = speed;
        }

        public int CompareTo(Shuttle other)
        {
            if (other == null) 
			{
				return 1;
			}

            return this.Speed.CompareTo(other.Speed);
        }

        public IEnumerator<string> GetEnumerator()
        {
            yield return $"Shuttle Name: {Name}";
            yield return $"Capacity: {Capacity}";
            yield return $"Speed: {Speed}";
        }

        IEnumerator IEnumerable.GetEnumerator()
        {
            return GetEnumerator();
        }
    }
}
