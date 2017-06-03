using Ninject;

using System.Net.Http;

namespace Middleware
{
    public static class NinjectConfig
    {
        public static IKernel CreateKernel()
        {
            var kernel = new StandardKernel();
            //Create the bindings

            kernel.Bind<HttpClient>().ToMethod(ctx => new HttpClient(new RetryDelegatingHandler.RetryDelegatingHandler()));
            kernel.Bind<ServicesCollector>().ToMethod(ctx => ServicesCollector.Instance);
            kernel.Bind<ServiceConfig>().ToMethod(ctx => ServiceConfig.Instance);
            
            return kernel;
        }
    }
}