using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BackendService
{
    public interface IStorage
    {
        void Save(string id, string value);
        string Get(string id);
        void Append(string id, string value);
    }
}
