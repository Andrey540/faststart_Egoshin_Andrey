using System;
using System.Configuration;
using System.Collections.Generic;
using Newtonsoft.Json.Linq;
using Newtonsoft.Json;
using Microsoft.Owin.Hosting;
using System.Reflection;
using System.Net.Http;
using System.Web;

namespace Middleware
{
    class Program
    {
        public static List<ServiceItem> services = new List<ServiceItem>();
        public static readonly string currentServiceName = ConfigurationManager.AppSettings["serviceName"];
        public static readonly string currentServiceAddress = ConfigurationManager.AppSettings["serviceAddress"];
        private static HttpClient _httpClient = new HttpClient(new RetryDelegatingHandler.RetryDelegatingHandler());

        public static string GetServiceUrl(string name)
        {
            var service = GetService(name);
            return (service != null) ? service.Url : null;
        }

        public static int GetServiceWeight(string name)
        {
            var service = GetService(name);
            return (service != null) ? service.Weight : 0;
        }

        public static ServiceItem GetService(string name)
        {
            return Program.services.Find(x => x.Name == name);
        }

        private static void InitServiceData()
        {
            var assembly = Assembly.GetExecutingAssembly();
            using (var stream = assembly.GetManifestResourceStream("Middleware.manifest.json"))
            using (var reader = new System.IO.StreamReader(stream))
            {
                string servicesString = reader.ReadToEnd();
                JObject servicesObj = JObject.Parse(servicesString);
                JArray servicesArr = (JArray)servicesObj["services"];

                for (var i = 0; i < servicesArr.Count; ++i)
                {
                    JObject service = (JObject)servicesArr[i];
                    var item = new ServiceItem() { Name = (string)service["Name"], Url = (string)service["Url"], Weight = (int)service["Weight"], Active = (bool)service["Active"] };
                    services.Add(item);
                }
            }
        }

        private static void InitStartupState()
        {
            Program.services.ForEach(delegate (ServiceItem service)
            {
                if ((service.Name.IndexOf(Program.currentServiceName) == -1) && service.Active)
                {
                    HttpResponseMessage httpResponseMessage = null;
                    var query = HttpUtility.ParseQueryString(string.Empty);
                    query["serviceName"] = Program.currentServiceName;
                    try
                    {
                        httpResponseMessage = _httpClient.GetAsync(service.Url + "?" + query.ToString()).Result;
                    }
                    catch(Exception)
                    {
                        service.Active = false;
                    }

                    if (httpResponseMessage != null)
                    {
                        var formattedResponse = httpResponseMessage.Content.ReadAsStringAsync().Result;
                        var appsState = JsonConvert.DeserializeObject<AppsHash>(formattedResponse);
                        ProcessAppsSate(appsState, service);
                    }
                }
            });
        }

        private static void ProcessAppsSate(AppsHash appsState, ServiceItem service)
        {
            foreach (KeyValuePair<string, AppInfoEx> entry in appsState)
            {
                entry.Value.Weight = (entry.Value.ServiceName == Program.currentServiceName) ? 0 : GetServiceWeight(entry.Value.ServiceName);
                AppInfoStorageController.CheckAndSetAppInfo(entry.Value, Program.currentServiceAddress, service.Url);
            }
        }

        static void Main(string[] args)
        {
            InitServiceData();
            InitStartupState();

            using (WebApp.Start<Startup>(Program.currentServiceAddress))
            {
                Console.WriteLine("Web Service is running.");
                Console.WriteLine("Press any key to quit.");
                Console.ReadLine();
            }
        }
    }
}
