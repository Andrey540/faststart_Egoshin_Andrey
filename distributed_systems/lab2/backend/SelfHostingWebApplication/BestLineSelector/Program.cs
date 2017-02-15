using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using RabbitMQ.Client;
using RabbitMQ.Client.Events;
using Newtonsoft.Json;

namespace BestLineSelector
{
    class Program
    {
        const string QUEUE_CONSONANT_NAME = "queueСonsonantData";

        const double BEST_LINE_COEFFICIENT_COUNT = 0.5;

        static void Main(string[] args)
        {
            IModel model = RabbitMQManager.Connection().CreateModel();

            var consumer = new EventingBasicConsumer(model);
            consumer.Received += (m, ea) =>
            {
                var body = ea.Body;
                var message = System.Text.Encoding.UTF8.GetString(body);
                Console.WriteLine(" [x] Received {0}", message);

                BestLinesMessage vowelMessage = JsonConvert.DeserializeObject<BestLinesMessage>(message);
                saveBestLines(vowelMessage);

                Console.WriteLine(" [x] Done");
            };
            string consumerTag = model.BasicConsume(QUEUE_CONSONANT_NAME, true, consumer);

            Console.WriteLine("Web Server is running.");
        }

        private static void saveBestLines(BestLinesMessage message)
        {
            char delimiter = '\n';
            string[] substrings = message.Text.Split(delimiter);
            var database = RedisDBManager.GetDatabase();
            for (int i = 0; i < substrings.Length; ++i)
            {
                if (System.Convert.ToDouble(message.VowelCount[i]) / System.Convert.ToDouble(message.СonsonantCount[i]) >= BEST_LINE_COEFFICIENT_COUNT)
                {
                    database.StringAppend(message.TaskId, substrings[i]);
                }
            }
        }
    }
}
