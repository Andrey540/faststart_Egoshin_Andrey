using System;
using System.Configuration;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Web.Http;
using Newtonsoft.Json;
using RabbitMQ.Client;
using System.Net.Http;
using System.Text;

namespace BackendService
{
    public class PoemController : ApiController
    {
        private readonly HttpClient _httpClient;

        public PoemController(HttpClient httpClient)
        {
            _httpClient = httpClient;
        }

        public void Post(Poem poem)
        {
            string address = ConfigurationManager.AppSettings["vowelServiceAddress"];
            var json = JsonConvert.SerializeObject(poem);
            var stringContent = new StringContent(json, Encoding.UTF8, "application/json");

            var httpResponseMessage = _httpClient.PostAsync(address, stringContent);
        }
    }
}