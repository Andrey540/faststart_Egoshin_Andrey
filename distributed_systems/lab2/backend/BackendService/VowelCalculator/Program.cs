using Microsoft.Owin.Hosting;
using System;
using System.Configuration;
using System.Net.Http;

namespace VowelCalculator
{
    class Program
    {
        static void Main(string[] args)
        {
            string address = ConfigurationManager.AppSettings["serviceAddress"];
            using (WebApp.Start<Startup>(address))
            {
                Console.WriteLine("Web Server is running.");
                Console.WriteLine("Press any key to quit.");
                Console.ReadLine();
            }
        }
    }
}
