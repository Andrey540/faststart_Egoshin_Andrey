using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Web.Http;
using Newtonsoft.Json;
using RabbitMQ.Client;

namespace SelfHostingWebApplication
{
    public class PoemController : ApiController
    {
        const string EXCHANGE_NAME = "exchangeVowelData";
        const string QUEUE_NAME = "queueVowelData";
        const string ROUTING_KEY = "superstars";

        private IModel m_model = RabbitMQManager.Connection().CreateModel();

        public PoemController()
        {
            m_model.ExchangeDeclare(EXCHANGE_NAME, ExchangeType.Direct);
            m_model.QueueDeclare(QUEUE_NAME, false, false, false, null);
            m_model.QueueBind(QUEUE_NAME, EXCHANGE_NAME, ROUTING_KEY, null);
        }

        public void Post(Poem poem)
        {
            Console.WriteLine(poem.TaskId);
            Console.WriteLine(poem.Text);

            var properties = m_model.CreateBasicProperties();
            properties.Persistent = true;

            var vowelCount = CalculateVovelCount(poem.Text);
            BestLinesMessage message = new BestLinesMessage()
            {
                TaskId = poem.TaskId,
                Text = poem.Text,
                VowelCount = vowelCount,
                СonsonantCount = new int[] {}
            };

            string jsonified = JsonConvert.SerializeObject(message);
            byte[] messageBodyBytes = System.Text.Encoding.UTF8.GetBytes(jsonified);
            m_model.BasicPublish(EXCHANGE_NAME, ROUTING_KEY, properties, messageBodyBytes);
        }

        private static int[] CalculateVovelCount(string poem)
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
                foreach (char vowel in split)
                {
                    if (vowels.Contains(vowel))
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