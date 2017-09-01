/*
 * Problem 3.26 
 * Write an app that inputs from the user the radius of the circle as an integer and displays the circle's diameter, circumference and area using the floating point value 3.14159 for PI 
 */
using System;


namespace Circle
{
    class Program
    {
        static void Main()
        {
            float PI = 3.14159F;
            Console.Write("Input a Radius: ");
            float radius = float.Parse(Console.ReadLine());
            float result;
            Console.WriteLine($"The Diameter: {result = 2*radius} \nThe Circumference: {result = 2 * PI * radius } \nThe Area: {result = PI * (radius * radius)}");
        }
    }
}
