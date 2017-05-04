using System;
using System.Configuration;
using System.Web.Http;
using Newtonsoft.Json;
using System.Net.Http;
using System.Net.Http.Headers;

namespace Middleware
{

    public class ApplicationController : ApiController
    {
        private readonly HttpClient _httpClient;
        public ApplicationController(HttpClient httpClient)
        {
            _httpClient = httpClient;
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
                ServiceName = Program.currentServiceName,
            };
            AppInfoStorageController.StepForwardAndSetAppInfo(appInfoEx);
            Console.WriteLine("Application with name: " + appInfo.Name + " and status: " + appInfo.Status + " and url: " + appInfo.Url + " and weight: 0 ");

            SendStateChangedEvent(appInfoEx);
        }

        private void SendStateChangedEvent (AppInfoEx appInfo)
        {
            var appsState = new Contracts.AppStateInfo() {Hash = appInfo.Hash, Time = appInfo.Time };
            var stateEvent = new Contracts.StateChangedEvent();
            stateEvent.ServiceName = Program.currentServiceName;
            stateEvent.AppState = appsState;
            Program.services.ForEach(delegate (ServiceItem service)
            {
                if ((service.Name.IndexOf(Program.currentServiceName) == -1) && service.Active)
                {
                    string jsonString = JsonConvert.SerializeObject(stateEvent);
                    HttpContent content = new StringContent(jsonString);
                    content.Headers.ContentType = new MediaTypeHeaderValue("application/json");
                    try
                    {
                        var httpResponseMessage = _httpClient.PostAsync(service.Url, content).Result;
                    }
                    catch (Exception)
                    {
                        service.Active = false;
                    }
                }
            });
        }
    }
}
