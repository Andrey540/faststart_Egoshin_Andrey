using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using StackExchange.Redis;

namespace BackendService
{
    public class RedisStorage : IStorage
    {
        const int MAX_FAILURES = 5;
        const int CIRCUIT_RESET_TIMEOUT = 10000;
        const int INVOCATION_TIMEOUT = 100;

        private IDatabase _db;
        private CircuitBreaker.Net.CircuitBreaker _circuitBreaker;

        public RedisStorage(IDatabase db)
        {
            _db = db;
            _circuitBreaker = new CircuitBreaker.Net.CircuitBreaker(
                TaskScheduler.Default,
                maxFailures: MAX_FAILURES,
                invocationTimeout: TimeSpan.FromMilliseconds(INVOCATION_TIMEOUT),
                circuitResetTimeout: TimeSpan.FromMilliseconds(CIRCUIT_RESET_TIMEOUT)
            );
        }

        public void Save(string id, string value)
        {
            _circuitBreaker.Execute(() => {
                _db.StringSet(id, value);
            });
        }

        public string Get(string id)
        {
            return _circuitBreaker.Execute(() => {
                return _db.StringGet(id);
            });
        }

        public void Append(string id, string value)
        {
            _circuitBreaker.Execute(() => {
                _db.StringAppend(id, value);
            });
        }
    }
}
