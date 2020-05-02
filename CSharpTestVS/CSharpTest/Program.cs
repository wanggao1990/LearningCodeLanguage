using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CSharpTest
{

    class Dog
    {
        private String name;
        private String color;

        public delegate void Handeler(Dog dog); //定义委托
        public static event Handeler NewDog;  //定义事件

        public Dog(String Name, String Color)
        {
            name = Name;
            color = Color;
            if (NewDog != null)
            {
                Console.WriteLine("新进了一只狗");
                NewDog(this);  //调用事件
            }
        }

        public String toString()
        {
            return String.Format("Dog {0} {1}", name, color);
        }
    }

    class Test
    {
        public static void Main()
        {
            Dog d = new Dog("Tony", "yellow"); //因为还没有添加订阅，所以不能触发事件


            Dog.NewDog += new Dog.Handeler(Client1); //Client1添加订阅
            Dog.NewDog += new Dog.Handeler(Client2);//Client2添加订阅

            Dog d2 = new Dog("Tom", "white");
        }
        static void Client1(Dog dog)
        {
            Console.WriteLine("我喜欢这条狗！" + dog.toString());
        }
        static void Client2(Dog dog)
        {
            Console.WriteLine("我非常想要！" + dog.toString());
        }
    }

}
