using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace СonsonantCalculator
{
    public class BestLinesMessage
    {
        public string TaskId { get; set; }
        public string Text { get; set; }
        public int[] VowelCount { get; set; }
        public int[] СonsonantCount { get; set; }
    }
}
