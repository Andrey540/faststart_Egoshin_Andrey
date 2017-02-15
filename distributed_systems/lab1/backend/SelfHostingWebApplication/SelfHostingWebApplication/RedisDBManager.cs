using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using StackExchange.Redis;

namespace SelfHostingWebApplication
{
    public class RedisDBManager
    {
        private const string HOST = "localhost:6379";

        private static IDatabase m_db;
        private static Lazy<ConnectionMultiplexer> lazyConnection;

        static RedisDBManager()
        {
            RedisDBManager.lazyConnection = new Lazy<ConnectionMultiplexer>(() => {
                ConnectionMultiplexer connection = ConnectionMultiplexer.Connect(HOST);
                RedisDBManager.m_db = connection.GetDatabase();
                return connection;
            });
        }

        public static IDatabase GetDatabase()
        {
            ConnectionMultiplexer connection = lazyConnection.Value;
            return RedisDBManager.m_db;
        }
    }
}
