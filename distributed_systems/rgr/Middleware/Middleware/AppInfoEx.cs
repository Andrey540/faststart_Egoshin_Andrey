using System.Collections.Generic;

namespace Middleware
{
    public class AppInfoEx : Contracts.AppInfo
    {
        public string ServiceName { get; set; }
        public int Weight { get; set; }
        public int Time { get; set; }
        public string Hash { get; set; }
    }

    public class AppInfoArray : List<AppInfoEx>
    {}

    public class AppsState : Dictionary<string, AppInfoArray>
    {}

    public class AppsHash : Dictionary<string, AppInfoEx>
    { }
}
