using System;
using System.Configuration;
using System.Net.Http;
using System.Net.Http.Headers;
using Newtonsoft.Json;
using System.Threading.Tasks;

namespace Application
{
    class Program
    {
        private static HttpClient _httpClient;
        static void Main(string[] args)
        {
            Run(args).Wait();
        }

        static async Task Run(string[] args)
        {
            _httpClient = new HttpClient(new RetryDelegatingHandler.RetryDelegatingHandler());

            string middlewareAddress = ConfigurationManager.AppSettings["middlewareAddress"];

            var appInfo = new Contracts.AppInfo()
            {
                Name = ConfigurationManager.AppSettings["appName"],
                Url = ConfigurationManager.AppSettings["applicationAddress"],
                Status = Contracts.AppStatus.Started
            };

            string jsonString = JsonConvert.SerializeObject(appInfo);
            HttpContent content = new StringContent(jsonString);
            content.Headers.ContentType = new MediaTypeHeaderValue("application/json");
            var sendStartTask = await _httpClient.PostAsync(middlewareAddress, content);

            Console.WriteLine(jsonString);
            Console.WriteLine("Web Applicationr is running.");
            Console.WriteLine("Press any key to quit.");
            Console.ReadKey();

            appInfo.Status = Contracts.AppStatus.Stoped;
            jsonString = JsonConvert.SerializeObject(appInfo);
            content = new StringContent(jsonString);
            content.Headers.ContentType = new MediaTypeHeaderValue("application/json");
            var sendStopTask = await _httpClient.PostAsync(middlewareAddress, content);
        }
    }
}
