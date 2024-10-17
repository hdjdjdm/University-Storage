using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using static System.Net.Mime.MediaTypeNames;

namespace Lr6Num2
{
    class Storage
    {
        private static List<Product> products = new List<Product>
        {
            new Product("Рузик", 1, 26, 47.9),
            new Product("Колбаса Докторская Вязанка", 2, 31, 139.9),
            new Product("Яйца", 3, 3, 81.9),
            new Product("Палочкм Кузя Лакомкин", 4, 44, 39.9),
            new Product("Шоколад Alpen Gold, Молочный, Фундук-изюм", 5, 8, 45.9),
            new Product("Батончик Picnic Big", 6, 12, 47.9),
            new Product("Йогурт ЧУДО, Клубника-земляника", 7, 14, 69.9),
            new Product("Мини-кексы ЮБИЛЕЙНОЕ с кусочками молочного шоколада", 8, 18, 109.99),
            new Product("Мармелад жевательный БОН ПАРИ, Кислые червячки", 9, 24, 59.99)
        };

        public void AddProduct(Product product)
        {
            products.Add(product);
        }

        public void RemoveProduct(int index)
        {
            foreach (Product product in products)
            {
                if (product.Id == index)
                {
                    products.Remove(product);
                    return;
                }
            }
            MessageBox.Show("Такого товара не существует");
        }

        public void ChangeProduct(Product changeProduct, int id)
        {
            foreach(Product product in products)
            {
                if (product.Id == id)
                {
                    product.Count = changeProduct.Count;
                    product.Price = changeProduct.Price;
                }
            }
        }

        public List<Product> GetProducts()
        {
            return products;
        }

        public Product SearchId(int index)
        {
            foreach (Product product in products)
            {
                if (product.Id == index)
                {
                    return product;
                }
            }
            MessageBox.Show("Такого товара не существует");
            return null;
        }

        public Product SearchName(string ProductName)
        {
            foreach (Product product in products)
            {
                if (product.Name == ProductName)
                {
                    return product;
                }
            }
            MessageBox.Show("Такого товара не существует");
            return null;
        }
        public List<Product> SortByName(bool reverseSort)
        {
            if (reverseSort == false)
            {
                products.Sort((x, y) => x.Name.CompareTo(y.Name));
            }
            else
            {
                products.Sort((x, y) => y.Name.CompareTo(x.Name));
            }
            return products;
        }

        public List<Product> SortByCount(bool reverseSort)
        {
            if (reverseSort == false)
            {
                products.Sort((x, y) => x.Count.CompareTo(y.Count));
            }
            else
            {
                products.Sort((x, y) => y.Count.CompareTo(x.Count));
            }
            return products;
        }

        public List<Product> SortByPrice(bool reverseSort)
        {
            if (reverseSort == false)
            {
                products.Sort((x, y) => x.Price.CompareTo(y.Price));
            }
            else
            {
                products.Sort((x, y) => y.Price.CompareTo(x.Price));
            }
            return products;
        }

    }
}
