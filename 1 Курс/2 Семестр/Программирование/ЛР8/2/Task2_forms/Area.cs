namespace Task2_forms.ContestClasses
{
    internal class Area
    {
        public int AreaID { get; private set; }
        public bool IsRunning { get; set; }
        public Area(int ID)
        {
            IsRunning = false;
            AreaID = ID;
        }

        public void StartCompetition(Competition contest)
        {
            IsRunning = true;
            contest.ConductingCompetition(AreaID);
        }
    }
}
