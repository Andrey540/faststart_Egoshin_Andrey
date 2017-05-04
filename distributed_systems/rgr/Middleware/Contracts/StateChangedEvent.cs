namespace Contracts
{
    public class StateChangedEvent
    {
        public string ServiceName { get; set; }
        public AppStateInfo AppState { get; set; }
    }

    public class AppStateInfo: AppInfo
    {
        public string Hash { get; set; }
        public int Time { get; set; }
    }
}
