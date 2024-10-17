using Task2_forms.ContestClasses;

namespace Task2_forms
{
    public partial class Form1 : Form
    {
        List<Area> sportAreas = new List<Area>();
        List<Competition> competition = new List<Competition>();
        Random rand = new Random();

        public Form1()
        {
            InitializeComponent();
            FillTables(10);
        }

        private void FillTables(int competCount)
        {
            for (int i = 0; i < competCount; i++)
            {
                competition.Add(new Competition((Sports)(i % 10)));

                competition[competition.Count - 1].Notify += (EventType evType, int areaNum) => AreaListView.Items[areaNum].SubItems[2].Text = evType.ToString();
                competition[competition.Count - 1].EndContest += (int areaNum, Sports compet) =>
                {
                    EndCompetitionsListView.Items.Add(new ListViewItem(compet.ToString()));
                    AreaListView.Items[areaNum].SubItems[1].Text = "";
                    AreaListView.Items[areaNum].SubItems[2].Text = "";
                    sportAreas[areaNum].IsRunning = false;
                };
                CompetitionsListView.Items.Add(new ListViewItem(competition[i].Sport.ToString()));
            }

            if (AreaListView.Items.Count == 0)
            {
                for (int i = 1; i <= 5; i++)
                {
                    sportAreas.Add(new Area(i - 1));
                    AreaListView.Items.Add(new ListViewItem(new string[] { i.ToString(), "", "" }));
                }
            }
        }

        private async Task RunCompetition(int i)
        {
            if (competition.Count == 0)
            {
                return;
            }

            var contest = competition[competition.Count-1];
            competition.Remove(contest);

            if (CompetitionsListView.Items.Count > 0)
            {
                CompetitionsListView.Items[CompetitionsListView.Items.Count - 1].Remove();
            }

            AreaListView.Items[i].SubItems[1].Text = contest.Sport.ToString();
            sportAreas[i].StartCompetition(contest);
        }

        private async void StartOlympiad()
        {
            while (true)
            {
                if (EndCompetitionsListView.Items.Count == 10)
                {
                    break;
                }

                await Task.Delay(250);

                for (int i = 0; i < 5; i++)
                {
                    if (!sportAreas[i].IsRunning)
                    {
                        await RunCompetition(i);
                    }
                }
            }
            MessageBox.Show("Все соревнования окончены", "Конец");
        }

        private void RunButton_Click(object sender, EventArgs e)
        {
            StartOlympiad();
        }

        private void AreaListView_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }
    }

    enum Sports
    {
        ГорныеЛыжи,
        Биатлон,
        Бобслей,
        ФигурноеКатание,
        Керлинг,
        Хоккей,
        Сноуборд,
        ЛыжныеГонки,
        Фристайл,
        Скелетон
    }
}
