using System;
using System.Web.Http;
using System.Web.Http.SelfHost;

namespace SelfHostingWebApplication
{
    class Program
    {
        private const string HOST = "http://localhost:8081/";

        static void Main(string[] args)
        {
            var selfHostConfiguraiton = new HttpSelfHostConfiguration(HOST);

            selfHostConfiguraiton.Routes.MapHttpRoute(
                name: "DefaultApi",
                routeTemplate: "api/{controller}/{id}",
                defaults: new { id = RouteParameter.Optional }
            );

            using (var server = new HttpSelfHostServer(selfHostConfiguraiton))
            {
                server.OpenAsync().Wait();
                Console.WriteLine("Started...");

                Console.ReadKey();
            }
        }
    }
}
