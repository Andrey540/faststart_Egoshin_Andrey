using System;
using System.Configuration;
using System.Collections.Generic;
using Newtonsoft.Json.Linq;
using Newtonsoft.Json;
using Microsoft.Owin.Hosting;
using System.Reflection;
using System.Net.Http;
using System.Web;
using System.Threading.Tasks;

namespace Middleware
{
    class Program
    {
        private static HttpClient _httpClient = new HttpClient(new RetryDelegatingHandler.RetryDelegatingHandler());
        private static ServicesCollector _servicesCollector = ServicesCollector.Instance;
        private static ServiceConfig _serviceConfig = ServiceConfig.Instance;
        
        private static async Task<string[]> InitStartupState()
        {
            var tasks = new List<Task<string>>();
            var services = _servicesCollector.GetServices();
            for (var i = 0; i < services.Count; ++i)
            {
                if ((services[i].Name.IndexOf(_serviceConfig.GetServiceName()) == -1) && services[i].Active)
                {
                    var initServiceStateTask = GetInitServiceState(services[i]);
                    tasks.Add(initServiceStateTask);
                    var serviceState = await initServiceStateTask;
                    if (serviceState != null)
                    {
                        var appsState = JsonConvert.DeserializeObject<AppsHash>(serviceState);
                        ProcessAppsSate(appsState, services[i]);
                    }
                }
            }
            return await Task.WhenAll(tasks.ToArray());
        }

        private static async Task<string> GetInitServiceState(ServiceItem service)
        {
            HttpResponseMessage response = null;
            var query = HttpUtility.ParseQueryString(string.Empty);
            query["serviceName"] = _serviceConfig.GetServiceName();
            try
            {
                response =  await _httpClient.GetAsync(service.Url + "?" + query.ToString());
            }
            catch (Exception)
            {
                service.Active = false;
            }
            if (response != null)
            {
                return await response.Content.ReadAsStringAsync();
            }
            return null;
        }

        private static void ProcessAppsSate(AppsHash appsState, ServiceItem service)
        {
            foreach (KeyValuePair<string, AppInfoEx> entry in appsState)
            {
                entry.Value.Weight = (entry.Value.ServiceName == _serviceConfig.GetServiceName()) ? 0 : _servicesCollector.GetServiceWeight(entry.Value.ServiceName);
                AppInfoStorageController.CheckAndSetAppInfo(entry.Value, _serviceConfig.GetServiceAddress(), service.Url);
            }
        }

        static void Main(string[] args)
        {
            InitStartupState().Wait();

            using (WebApp.Start<Startup>(_serviceConfig.GetServiceAddress()))
            {
                Console.WriteLine("Web Service is running.");
                Console.WriteLine("Press any key to quit.");
                Console.ReadKey();
            }
        }
    }
}
