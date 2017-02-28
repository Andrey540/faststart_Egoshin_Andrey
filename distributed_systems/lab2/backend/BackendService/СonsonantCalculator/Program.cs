using System;
using System.Configuration;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Newtonsoft.Json;
using MassTransit;
using MassTransit.RabbitMqTransport;

using BestLineSelector;
using BackendService;

namespace СonsonantCalculator
{
    class Program
    {
        static void Main(string[] args)
        {
            IBusControl rabbitBusControl = Bus.Factory.CreateUsingRabbitMq(rabbit =>
            {
                IRabbitMqHost rabbitMqHost = rabbit.Host(new Uri(ConfigurationManager.AppSettings["rabbitHost"]), settings =>
                {
                    settings.Password(ConfigurationManager.AppSettings["rabbitPass"]);
                    settings.Username(ConfigurationManager.AppSettings["rabbitUser"]);
                });

                rabbit.ReceiveEndpoint(rabbitMqHost, ConfigurationManager.AppSettings["queueName"], e =>
                {
                    e.Consumer<СonsonantConsumer>();
                });
            });
            rabbitBusControl.Start();

            Console.WriteLine("Web Server is running.");
            Console.WriteLine("Press any key to quit.");
            Console.ReadKey();

            rabbitBusControl.Stop();
        }
    }
}
