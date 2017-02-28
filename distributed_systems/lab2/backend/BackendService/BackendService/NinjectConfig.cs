using System.Configuration;
using Ninject;
using StackExchange.Redis;
using RabbitMQ.Client;

using System.Net.Http;

namespace BackendService
{
    public static class NinjectConfig
    {
        public static IKernel CreateKernel()
        {
            var kernel = new StandardKernel();
            //Create the bindings

            kernel.Bind<IStorage>().ToMethod(ctx => new RedisStorage(RedisDBManager.GetDatabase()));
            kernel.Bind<HttpClient>().ToMethod(ctx => new HttpClient(new RetryDelegatingHandler()));
            
            return kernel;
        }
    }
}