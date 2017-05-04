namespace Contracts
{
    public enum AppStatus { Stoped, Started };
    public class AppInfo
    {
        public string Name { get; set; }
        public string Url { get; set; }
        public AppStatus Status { get; set; }
    }
}
