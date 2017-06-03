using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Configuration;

namespace Middleware
{
    public class ServiceConfig
    {
        private static ServiceConfig instance;

        private string _currentServiceName;
        private string _currentServiceAddress;
        private string _manifestFilePath;

        private ServiceConfig()
        {
            _currentServiceName = ConfigurationManager.AppSettings["serviceName"];
            _currentServiceAddress = ConfigurationManager.AppSettings["serviceAddress"];
            _manifestFilePath = ConfigurationManager.AppSettings["manifestFilePath"];
        }

        public static ServiceConfig Instance
        {
            get
            {
                if (instance == null)
                {
                    instance = new ServiceConfig();
                }
                return instance;
            }
        }

        public string GetServiceName()
        {
            return _currentServiceName;
        }

        public string GetServiceAddress()
        {
            return _currentServiceAddress;
        }

        public string GetManifestFilePath()
        {
            return _manifestFilePath;
        }
    }
}
