using System;
using System.Web.Http;
using Newtonsoft.Json;
using System.Net.Http;
using System.Net.Http.Headers;
using System.Threading.Tasks;
using System.Collections.Generic;

namespace Middleware
{

    public class ApplicationController : ApiController
    {
        private readonly HttpClient _httpClient;
        private readonly ServicesCollector _servicesCollector;
        private readonly ServiceConfig _serviceConfig;
        public ApplicationController(HttpClient httpClient, ServicesCollector servicesCollector, ServiceConfig serviceConfig)
        {
            _httpClient = httpClient;
            _servicesCollector = servicesCollector;
            _serviceConfig = serviceConfig;
        }

        public string Get(string appName)
        {
            return AppInfoStorageController.GetOptimalUrl(appName);
        }

        public void Post(Contracts.AppInfo appInfo)
        {
            var appInfoEx = new AppInfoEx() {
                Name = appInfo.Name,
                Url = appInfo.Url,
                Weight = 0,
                Status = appInfo.Status,
                Time = 1,
                Hash = AppInfoStorageController.GenerateHash(appInfo.Url),
                ServiceName = _serviceConfig.GetServiceName(),
            };
            AppInfoStorageController.StepForwardAndSetAppInfo(appInfoEx);
            Console.WriteLine("Application with name: " + appInfo.Name + " and status: " + appInfo.Status + " and url: " + appInfo.Url + " and weight: 0 ");

            Task.WaitAll(SendStateChangedEvent(appInfoEx));
        }

        private Task<HttpResponseMessage>[] SendStateChangedEvent (AppInfoEx appInfo)
        {
            var tasks = new List<Task<HttpResponseMessage>>();
            var appsState = new Contracts.AppStateInfo() {Hash = appInfo.Hash, Time = appInfo.Time };
            var stateEvent = new Contracts.StateChangedEvent();
            stateEvent.ServiceName = _serviceConfig.GetServiceName();
            stateEvent.AppState = appsState;
            var services = _servicesCollector.GetServices();
            for (var i = 0; i < services.Count; ++i)
            {
                if ((services[i].Name.IndexOf(_serviceConfig.GetServiceName()) == -1) && services[i].Active)
                {
                    string jsonString = JsonConvert.SerializeObject(stateEvent);
                    HttpContent content = new StringContent(jsonString);
                    content.Headers.ContentType = new MediaTypeHeaderValue("application/json");
                    try
                    {
                        tasks.Add(_httpClient.PostAsync(services[i].Url, content));
                    }
                    catch (Exception)
                    {
                        services[i].Active = false;
                    }
                }
            }
            return tasks.ToArray();
        }
    }
}
