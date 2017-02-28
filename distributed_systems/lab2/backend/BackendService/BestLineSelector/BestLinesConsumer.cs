using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using MassTransit;
using Ninject;

using BackendService;

namespace BestLineSelector
{
    public class BestLinesConsumer : IConsumer<BestLinesMessage>
    {
        const double BEST_LINE_COEFFICIENT_COUNT = 0.5;

        IStorage _storage;

        public BestLinesConsumer()
        {
            var kernel = NinjectConfig.CreateKernel();
            _storage = kernel.Get<IStorage>(); ;
        }

        public Task Consume(ConsumeContext<BestLinesMessage> context)
        {
            BestLinesMessage message = context.Message;
            saveBestLines(message);
            return Task.FromResult(context.Message);
        }

        private void saveBestLines(BestLinesMessage message)
        {
            char delimiter = '\n';
            string[] substrings = message.Text.Split(delimiter);
            for (int i = 0; i < substrings.Length; ++i)
            {
                if (System.Convert.ToDouble(message.VowelCount[i]) / System.Convert.ToDouble(message.СonsonantCount[i]) >= BEST_LINE_COEFFICIENT_COUNT)
                {
                    _storage.Append(message.TaskId, substrings[i]);
                }
            }
        }
    }
}
