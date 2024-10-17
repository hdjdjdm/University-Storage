namespace Task2_forms.ContestClasses
{
    internal class Competition
    {
        public delegate void ContestHandler(EventType type, int areaNumber);
        public event ContestHandler Notify;
        public event Action<int, Sports> EndContest;
        public Sports Sport { get; }

        public Competition(Sports sport)
        {
            Sport = sport;
        }

        public async void ConductingCompetition(int areaNum)
        {
            var rand = new Random();

            Notify?.Invoke(EventType.Тренировка, areaNum);
            await Task.Delay(rand.Next(1000, 2000));

            Notify?.Invoke(EventType.Соревнование, areaNum);
            await Task.Delay(rand.Next(2000, 8000));

            Notify?.Invoke(EventType.Конец, areaNum);
            await Task.Delay(1000);

            EndContest?.Invoke(areaNum, Sport);
        }
    }

    public enum EventType
    {
        Тренировка,
        Соревнование,
        Конец
    }
}
