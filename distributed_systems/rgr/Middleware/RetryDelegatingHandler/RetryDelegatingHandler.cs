﻿using System;
using System.Threading.Tasks;
using System.Threading;
using Microsoft.Practices.EnterpriseLibrary.TransientFaultHandling;
using System.Net.Http;

namespace RetryDelegatingHandler
{
    public class RetryDelegatingHandler : HttpClientHandler
    {
        public RetryPolicy _retryPolicy;
        public RetryDelegatingHandler() : base()
        {
            _retryPolicy = DefaultRetryPolicy.MakeHttpRetryPolicy();
        }

        protected async override Task<HttpResponseMessage> SendAsync(HttpRequestMessage request, CancellationToken cancellationToken)
        {
            return await _retryPolicy.ExecuteAsync(async () => {
                return await base.SendAsync(request, cancellationToken).ConfigureAwait(false);
            }, cancellationToken).ConfigureAwait(false);
        }
    }

    public static class DefaultRetryPolicy
    {
        public static RetryPolicy MakeHttpRetryPolicy()
        {
            var retryCount = 1;
            var minBackoff = TimeSpan.FromSeconds(1);
            var maxBackoff = TimeSpan.FromSeconds(2);
            var deltaBackoff = TimeSpan.FromSeconds(5);
            var exponentialBackoff = new ExponentialBackoff(retryCount, minBackoff, maxBackoff, deltaBackoff);
            var strategy = new HttpTransientErrorDetectionStrategy();
            return new RetryPolicy(strategy, exponentialBackoff);
        }
    }

    public class HttpTransientErrorDetectionStrategy : ITransientErrorDetectionStrategy
    {
        public bool IsTransient(Exception ex)
        {
            Console.WriteLine("try.");
            return (ex != null);
        }
    }
}