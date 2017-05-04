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
        public MiddlewareController(HttpClient httpClient)
        {
            _httpClient = httpClient;
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
            var serviceName = Program.currentServiceAddress;
            if (AppInfoStorageController.NeedUpdate(stateEvent.AppState.Hash, stateEvent.AppState.Time, serviceName, stateEvent.ServiceName))
            {
                SendGetAppInfoRequest(stateEvent);
            }
        }

        private void SendGetAppInfoRequest(Contracts.StateChangedEvent stateEvent)
        {
            var serviceUrl = Program.GetServiceUrl(stateEvent.ServiceName);
            if (serviceUrl != null)
            {
                var query = HttpUtility.ParseQueryString(string.Empty);
                query["serviceName"] = Program.currentServiceName;
                query["hash"] = Uri.EscapeDataString(stateEvent.AppState.Hash);
                var httpResponseMessage = _httpClient.GetAsync(serviceUrl + "?" + query.ToString()).Result;
                var formattedResponse = httpResponseMessage.Content.ReadAsStringAsync().Result;
                var serviceName = Program.currentServiceAddress;
                var appInfo = JsonConvert.DeserializeObject<AppInfoEx>(formattedResponse);
                appInfo.Weight = Program.GetServiceWeight(appInfo.ServiceName);

                AppInfoStorageController.CheckAndSetAppInfo(appInfo, serviceName, stateEvent.ServiceName);
            }
        }

        private void ResetService(string name)
        {
            var service = Program.GetService(name);
            if ((service != null) && !service.Active)
            {
                Console.WriteLine("Reset " + name);
                service.Active = true;
            }
        }
    }
}