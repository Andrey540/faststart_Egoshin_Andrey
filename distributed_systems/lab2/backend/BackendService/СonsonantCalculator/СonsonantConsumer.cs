using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using MassTransit;

using BestLineSelector;

namespace СonsonantCalculator
{
    public class СonsonantConsumer : IConsumer<СonsonantMessage>
    {
        public Task Consume(ConsumeContext<СonsonantMessage> context)
        {
            СonsonantMessage message = context.Message;
            var consonantCount = CalculateСonsonantCount(message.Text);

            BestLinesMessage newMessage = new BestLinesMessage()
            {
                TaskId = message.TaskId,
                Text = message.Text,
                VowelCount = message.VowelCount,
                СonsonantCount = consonantCount
            };
            context.Publish<BestLinesMessage>(newMessage);
            return Task.FromResult(context.Message);
        }

        private static int[] CalculateСonsonantCount(string poem)
        {
            char delimiter = '\n';
            string[] substrings = poem.Split(delimiter);

            var result = new int[substrings.Length];
            int index = 0;
            foreach (var substring in substrings)
            {
                result[index] = СonsonantCharsCalculator.GetСonsonantCharsCount(substring);
                ++index;
            }
            return result;
        }
    }
}
