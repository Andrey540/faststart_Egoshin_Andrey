using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace VowelCalculator
{
    public static class VowelCharsCalculator
    {
        private static char[] _vowels = {'a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U',
                                         'а', 'у', 'о', 'ы', 'и', 'э', 'я', 'ю', 'ё', 'е', 'А', 'У', 'О', 'Ы', 'И', 'Э', 'Я', 'Ю', 'Ё', 'Е'};

        public static int GetVowelCharsCount(string text)
        {
            int result = 0;
            char[] split = text.ToCharArray();
            foreach (char consonant in split)
            {
                if (_vowels.Contains(consonant))
                {
                    ++result;
                }
            }
            return result;
        }
    }
}
