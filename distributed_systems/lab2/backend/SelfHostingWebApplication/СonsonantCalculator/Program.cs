using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using RabbitMQ.Client;
using RabbitMQ.Client.Events;
using Newtonsoft.Json;

namespace СonsonantCalculator
{
    class Program
    {
        const string QUEUE_VOWEL_NAME = "queueVowelData";

        const string EXCHANGE_CONSONANT_NAME = "exchangeСonsonantData";
        const string QUEUE_CONSONANT_NAME = "queueСonsonantData";
        const string ROUTING_CONSONANT_KEY = "superstars";

        static void Main(string[] args)
        {
            IModel model = RabbitMQManager.Connection().CreateModel();

            model.ExchangeDeclare(EXCHANGE_CONSONANT_NAME, ExchangeType.Direct);
            model.QueueDeclare(QUEUE_CONSONANT_NAME, false, false, false, null);
            model.QueueBind(QUEUE_CONSONANT_NAME, EXCHANGE_CONSONANT_NAME, ROUTING_CONSONANT_KEY, null);

            var consumer = new EventingBasicConsumer(model);
            consumer.Received += (m, ea) =>
            {
                var body = ea.Body;
                var message = System.Text.Encoding.UTF8.GetString(body);
                Console.WriteLine(" [x] Received {0}", message);

                BestLinesMessage newMessage = JsonConvert.DeserializeObject<BestLinesMessage>(message);
                var properties = model.CreateBasicProperties();
                properties.Persistent = true;
                newMessage.СonsonantCount = CalculateСonsonantCount(newMessage.Text);

                string jsonified = JsonConvert.SerializeObject(newMessage);
                byte[] messageBodyBytes = System.Text.Encoding.UTF8.GetBytes(jsonified);
                model.BasicPublish(EXCHANGE_CONSONANT_NAME, ROUTING_CONSONANT_KEY, properties, messageBodyBytes);             

                Console.WriteLine(" [x] Done");
            };
            string consumerTag = model.BasicConsume(QUEUE_VOWEL_NAME, true, consumer);

            Console.WriteLine("Web Server is running.");
        }

        private static int[] CalculateСonsonantCount(string poem)
        {
            char delimiter = '\n';
            char[] vowels = {'a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U',
                             'а', 'у', 'о', 'ы', 'и', 'э', 'я', 'ю', 'ё', 'е', 'А', 'У', 'О', 'Ы', 'И', 'Э', 'Я', 'Ю', 'Ё', 'Е'};
            string[] substrings = poem.Split(delimiter);

            var result = new int[substrings.Length];
            int index = 0;
            foreach (var substring in substrings)
            {
                int counter = 0;
                char[] split = substring.ToCharArray();
                foreach (char consonant in split)
                {
                    if (Char.IsLetter(consonant) && !vowels.Contains(consonant))
                    {
                        ++counter;
                    }
                }
                result[index] = counter;
                ++index;
            }
            return result;
        }
    }
}
