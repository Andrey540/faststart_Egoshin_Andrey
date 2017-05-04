using System;
using System.Collections.Generic;
using System.Security.Cryptography;
using System.Text;

namespace Middleware
{
    public class AppInfoStorageController
    {
        private static Object _lock = new Object();
        private static AppsState _appInfo = new AppsState();
        private static AppsHash _appHash = new AppsHash();
        private static SHA1Managed _sha1 = new SHA1Managed();

        public static string GetOptimalUrl(string appName)
        {
            AppInfoArray appInfoArray = null;
            if (_appInfo.TryGetValue(appName, out appInfoArray))
            {
                var filteredValues = appInfoArray.FindAll(item => item.Status == Contracts.AppStatus.Started);
                filteredValues.Sort(delegate (AppInfoEx first, AppInfoEx second)
                {
                    return first.Weight - second.Weight;
                });
                return (filteredValues.Count > 0) ? filteredValues[0].Url : "";
            }
            return "";
        }

        public static AppsHash GetState()
        {
            return _appHash;
        }

        public static void CheckAndSetAppInfo(AppInfoEx appInfo, string currentServiceName, string serviceName)
        {
            lock (_lock)
            {
                if (NeedUpdate(appInfo.Hash, appInfo.Time, currentServiceName, serviceName))
                {
                    AppInfoStorageController.SetAppInfo(appInfo);
                }
            }
        }

        public static void StepForwardAndSetAppInfo(AppInfoEx appInfo)
        {
            lock (_lock)
            {
                var stotingInfo = AppInfoStorageController.GetAppInfo(appInfo.Hash);
                if (stotingInfo != null)
                {
                    appInfo.Time = stotingInfo.Time + 1;
                }
                AppInfoStorageController.SetAppInfo(appInfo);
            }
        }

        public static bool NeedUpdate(string hash, int Time, string currentServiceName, string serviceName)
        {
            var stotingInfo = GetAppInfo(hash);
            if (((stotingInfo == null) ||
                (Time > stotingInfo.Time) ||
               ((Time == stotingInfo.Time) && (String.Compare(currentServiceName, serviceName) < 0))))
            {
                return true;
            }
            return false;
        }

        public static void SetAppInfo(AppInfoEx appInfo)
        {
            var storingInfo = GetAppInfo(appInfo.Hash);
            if (storingInfo != null)
            {
                storingInfo.Status = appInfo.Status;
                storingInfo.Time = appInfo.Time;
            }
            else
            {
                AppInfoArray appInfoArray = null;
                if (_appInfo.TryGetValue(appInfo.Name, out appInfoArray))
                {
                    appInfoArray.Add(appInfo);
                }
                else
                {
                    appInfoArray = new AppInfoArray();
                    appInfoArray.Add(appInfo);
                    _appInfo.Add(appInfo.Name, appInfoArray);
                }
                _appHash.Add(appInfo.Hash, appInfo);
            }
        }

        public static AppInfoEx GetAppInfo(string appName, string url)
        {
            AppInfoEx appInfo = null;
            AppInfoArray appInfoArray = null;
            if (_appInfo.TryGetValue(appName, out appInfoArray))
            {
                appInfo = appInfoArray.Find(x => x.Url == url);
            }
            return appInfo;
        }

        public static AppInfoEx GetAppInfo(string hash)
        {
            AppInfoEx appInfo = null;
            _appHash.TryGetValue(hash, out appInfo);
            return appInfo;
        }

        public static string GenerateHash(string key)
        {
            return Encoding.UTF8.GetString(_sha1.ComputeHash(Encoding.UTF8.GetBytes(key)));
        }
    }
}
