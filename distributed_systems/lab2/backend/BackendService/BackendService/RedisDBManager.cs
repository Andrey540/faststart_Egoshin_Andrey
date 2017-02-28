using System;
using System.Configuration;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using StackExchange.Redis;

namespace BackendService
{
    public class RedisDBManager
    {
        private static IDatabase _db;
        private static Lazy<ConnectionMultiplexer> lazyConnection;

        static RedisDBManager()
        {
            RedisDBManager.lazyConnection = new Lazy<ConnectionMultiplexer>(() =>
            {
                string address = ConfigurationManager.AppSettings["redisAddress"];
                ConnectionMultiplexer connection = ConnectionMultiplexer.Connect(address);
                RedisDBManager._db = connection.GetDatabase();
                return connection;
            });
        }

        public static IDatabase GetDatabase()
        {
            ConnectionMultiplexer connection = lazyConnection.Value;
            return RedisDBManager._db;
        }
    }
}
