using System;
using System.Configuration;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Web.Http;
using Newtonsoft.Json;
using MassTransit;
using MassTransit.RabbitMqTransport;

using СonsonantCalculator;
using BackendService;

namespace VowelCalculator
{
    public class VowelController : ApiController
    {
        private readonly IBusControl _rabbitBusControl;

        public VowelController()
        {
            _rabbitBusControl = Bus.Factory.CreateUsingRabbitMq(rabbit =>
            {
                IRabbitMqHost rabbitMqHost = rabbit.Host(new Uri(ConfigurationManager.AppSettings["rabbitHost"]), settings =>
                {
                    settings.Password(ConfigurationManager.AppSettings["rabbitPass"]);
                    settings.Username(ConfigurationManager.AppSettings["rabbitUser"]);
                });

             /*   rabbit.ReceiveEndpoint(rabbitMqHost, "vowelQueue", e =>
                {
                    e.Consumer<VowelConsumer>();
                });*/
            });
            _rabbitBusControl.Start();
        }

        ~VowelController()
        {
            _rabbitBusControl.Stop();
        }

        public void Post(Poem poem)
        {
            var vowelCount = CalculateVovelCount(poem.Text);
            _rabbitBusControl.Publish<СonsonantMessage>(new
            {
                TaskId = poem.TaskId,
                Text = poem.Text,
                VowelCount = vowelCount,
            });
        }

        private static int[] CalculateVovelCount(string poem)
        {
            char delimiter = '\n';
            string[] substrings = poem.Split(delimiter);

            var result = new int[substrings.Length];
            int index = 0;
            foreach (var substring in substrings)
            {
                result[index] = VowelCharsCalculator.GetVowelCharsCount(substring);
                ++index;
            }
            return result;
        }
    }
}