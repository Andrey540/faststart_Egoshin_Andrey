using System;
using System.Configuration;
using System.Collections.Generic;
using Newtonsoft.Json.Linq;
using Newtonsoft.Json;
using System.Reflection;

namespace Middleware
{
    public class ServicesCollector
    {
        private static ServicesCollector instance;

        private List<ServiceItem> _services = new List<ServiceItem>();
        private ServiceConfig _serviceConfig = ServiceConfig.Instance;

        private ServicesCollector()
        {
            try
            {
                using (var reader = new System.IO.StreamReader(_serviceConfig.GetManifestFilePath()))
                {
                    string servicesString = reader.ReadToEnd();
                    JObject servicesObj = JObject.Parse(servicesString);
                    JArray servicesArr = (JArray)servicesObj["services"];

                    for (var i = 0; i < servicesArr.Count; ++i)
                    {
                        JObject service = (JObject)servicesArr[i];
                        var item = new ServiceItem() { Name = (string)service["Name"], Url = (string)service["Url"], Weight = (int)service["Weight"], Active = (bool)service["Active"] };
                        _services.Add(item);
                    }
                }
            }
            catch (Exception e)
            {
                Console.WriteLine("The manifest file could not be read: " + _serviceConfig.GetManifestFilePath());
                Console.WriteLine(e.Message);
            }            
        }

        public static ServicesCollector Instance
        {
            get
            {
                if (instance == null)
                {
                    instance = new ServicesCollector();
                }
                return instance;
            }
        }

        public IReadOnlyList<ServiceItem> GetServices()
        {
            return _services;
        }

        public string GetServiceUrl(string name)
        {
            var service = GetService(name);
            return (service != null) ? service.Url : null;
        }

        public int GetServiceWeight(string name)
        {
            var service = GetService(name);
            return (service != null) ? service.Weight : 0;
        }

        public ServiceItem GetService(string name)
        {
            return _services.Find(x => x.Name == name);
        }
    }
}
