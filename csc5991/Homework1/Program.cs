/*
 *  Problem 3.24 
 *  Write an app that reads an integer then determines and displays if it's odd or even 
 *  Written by Caleb Latimer
 *  ej1297
 */
using System;

namespace OddOrEven
{
    class Program
    {
        static void Main()
        {
            Console.Write("Please enter a number for input: ");
            int input = int.Parse(Console.ReadLine());
            if (input % 2 == 0)
                Console.WriteLine($"The number {input} is even");
            else
                Console.WriteLine($"The number {input} is odd");
        }
    }
}
