using Microsoft.Owin.Hosting;
using System;
using System.Net.Http;

namespace SelfHostingWebApplication
{
    class Program
    {
        private const string HOST = "http://localhost:8081/";

        static void Main(string[] args)
        {
            using (WebApp.Start<Startup>(HOST))
            {
                Console.WriteLine("Web Server is running.");
                Console.WriteLine("Press any key to quit.");
                Console.ReadLine();
            }
        }
    }
}
