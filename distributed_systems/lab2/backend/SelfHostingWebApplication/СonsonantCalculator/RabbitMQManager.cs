using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using RabbitMQ.Client;

namespace СonsonantCalculator
{
    public class RabbitMQManager
    {
        private const string HOST = "localhost";
        private const string USER = "guest";
        private const string PASS = "guest";

        private static ConnectionFactory m_factory;
        private static Lazy<IConnection> lazyConnection;

        static RabbitMQManager()
        {
            m_factory = new ConnectionFactory();
            m_factory.HostName = HOST;
            m_factory.UserName = USER;
            m_factory.Password = PASS;
            RabbitMQManager.lazyConnection = new Lazy<IConnection>(() =>
            {
                return m_factory.CreateConnection();
            });
        }

        public static IConnection Connection()
        {
            return lazyConnection.Value;
        }
    }
}
