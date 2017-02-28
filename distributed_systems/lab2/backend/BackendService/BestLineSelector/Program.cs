using System;
using System.Configuration;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Newtonsoft.Json;
using StackExchange.Redis;
using Ninject;
using MassTransit;
using MassTransit.RabbitMqTransport;

using BackendService;

namespace BestLineSelector
{
    class Program
    {
        const double BEST_LINE_COEFFICIENT_COUNT = 0.5;

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
                    e.Consumer<BestLinesConsumer>();
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
