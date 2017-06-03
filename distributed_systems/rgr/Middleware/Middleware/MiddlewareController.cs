using System;
using System.Configuration;
using System.Web;
using System.Web.Http;
using Newtonsoft.Json;
using System.Net.Http;

namespace Middleware
{
    public class MiddlewareController : ApiController
    {
        private readonly HttpClient _httpClient;
        private readonly ServicesCollector _servicesCollector;
        private readonly ServiceConfig _serviceConfig;
        public MiddlewareController(HttpClient httpClient, ServicesCollector servicesCollector, ServiceConfig serviceConfig)
        {
            _httpClient = httpClient;
            _servicesCollector = servicesCollector;
            _serviceConfig = serviceConfig;
        }

        public AppsHash Get(string serviceName)
        {
            Console.WriteLine("Get all state request from " + serviceName);
            ResetService(serviceName);
            return AppInfoStorageController.GetState();
        }

        public AppInfoEx Get(string serviceName, string hash)
        {
            Console.WriteLine("Get app state request from " + serviceName);
            ResetService(serviceName);
            return AppInfoStorageController.GetAppInfo(Uri.UnescapeDataString(hash));
        }

        public void Post(Contracts.StateChangedEvent stateEvent)
        {
            Console.WriteLine("Receive info app from " + stateEvent.ServiceName);
            ResetService(stateEvent.ServiceName);
            var serviceName = _serviceConfig.GetServiceAddress();
            if (AppInfoStorageController.NeedUpdate(stateEvent.AppState.Hash, stateEvent.AppState.Time, serviceName, stateEvent.ServiceName))
            {
                SendGetAppInfoRequest(stateEvent);
            }
        }

        private async void SendGetAppInfoRequest(Contracts.StateChangedEvent stateEvent)
        {
            var serviceUrl = _servicesCollector.GetServiceUrl(stateEvent.ServiceName);
            if (serviceUrl != null)
            {
                var query = HttpUtility.ParseQueryString(string.Empty);
                query["serviceName"] = _serviceConfig.GetServiceName();
                query["hash"] = Uri.EscapeDataString(stateEvent.AppState.Hash);

                var response = await _httpClient.GetAsync(serviceUrl + "?" + query.ToString());
                var formattedResponse = await response.Content.ReadAsStringAsync();

                var serviceName = _serviceConfig.GetServiceAddress();
                var appInfo = JsonConvert.DeserializeObject<AppInfoEx>(formattedResponse);
                appInfo.Weight = _servicesCollector.GetServiceWeight(appInfo.ServiceName);

                AppInfoStorageController.CheckAndSetAppInfo(appInfo, serviceName, stateEvent.ServiceName);
            }
        }

        private void ResetService(string name)
        {
            var service = _servicesCollector.GetService(name);
            if ((service != null) && !service.Active)
            {
                Console.WriteLine("Reset " + name);
                service.Active = true;
            }
        }
    }
}