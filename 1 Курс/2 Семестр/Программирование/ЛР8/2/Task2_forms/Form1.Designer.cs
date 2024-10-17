namespace Task2_forms
{
    partial class Form1
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            RunButton = new Button();
            CompetitionsListView = new ListView();
            CompetitionsHeader = new ColumnHeader();
            AreaListView = new ListView();
            AreaHeader = new ColumnHeader();
            CompetitionHeader = new ColumnHeader();
            StatusHeader = new ColumnHeader();
            EndCompetitionsListView = new ListView();
            EndCompetitionsHeader = new ColumnHeader();
            SuspendLayout();
            // 
            // RunButton
            // 
            RunButton.BackColor = SystemColors.ButtonFace;
            RunButton.FlatStyle = FlatStyle.Flat;
            RunButton.Location = new Point(13, 320);
            RunButton.Margin = new Padding(4, 3, 4, 3);
            RunButton.Name = "RunButton";
            RunButton.Size = new Size(156, 46);
            RunButton.TabIndex = 0;
            RunButton.Text = "Начать";
            RunButton.UseVisualStyleBackColor = false;
            RunButton.Click += RunButton_Click;
            // 
            // CompetitionsListView
            // 
            CompetitionsListView.Columns.AddRange(new ColumnHeader[] { CompetitionsHeader });
            CompetitionsListView.GridLines = true;
            CompetitionsListView.Location = new Point(13, 13);
            CompetitionsListView.Margin = new Padding(4, 3, 4, 3);
            CompetitionsListView.Name = "CompetitionsListView";
            CompetitionsListView.Size = new Size(156, 291);
            CompetitionsListView.TabIndex = 1;
            CompetitionsListView.UseCompatibleStateImageBehavior = false;
            CompetitionsListView.View = View.Details;
            // 
            // CompetitionsHeader
            // 
            CompetitionsHeader.Text = "Предстоящие";
            CompetitionsHeader.Width = 150;
            // 
            // AreaListView
            // 
            AreaListView.Columns.AddRange(new ColumnHeader[] { AreaHeader, CompetitionHeader, StatusHeader });
            AreaListView.GridLines = true;
            AreaListView.Location = new Point(193, 13);
            AreaListView.Margin = new Padding(4, 3, 4, 3);
            AreaListView.Name = "AreaListView";
            AreaListView.Size = new Size(406, 353);
            AreaListView.TabIndex = 2;
            AreaListView.UseCompatibleStateImageBehavior = false;
            AreaListView.View = View.Details;
            AreaListView.SelectedIndexChanged += AreaListView_SelectedIndexChanged;
            // 
            // AreaHeader
            // 
            AreaHeader.Text = "Площадка";
            AreaHeader.Width = 100;
            // 
            // CompetitionHeader
            // 
            CompetitionHeader.Text = "Соревнование";
            CompetitionHeader.Width = 150;
            // 
            // StatusHeader
            // 
            StatusHeader.Text = "Статус";
            StatusHeader.Width = 150;
            // 
            // EndCompetitionsListView
            // 
            EndCompetitionsListView.Columns.AddRange(new ColumnHeader[] { EndCompetitionsHeader });
            EndCompetitionsListView.GridLines = true;
            EndCompetitionsListView.Location = new Point(621, 13);
            EndCompetitionsListView.Margin = new Padding(4, 3, 4, 3);
            EndCompetitionsListView.Name = "EndCompetitionsListView";
            EndCompetitionsListView.Size = new Size(154, 353);
            EndCompetitionsListView.TabIndex = 3;
            EndCompetitionsListView.UseCompatibleStateImageBehavior = false;
            EndCompetitionsListView.View = View.Details;
            // 
            // EndCompetitionsHeader
            // 
            EndCompetitionsHeader.Text = "Оконченые";
            EndCompetitionsHeader.Width = 150;
            // 
            // Form1
            // 
            AutoScaleDimensions = new SizeF(9F, 21F);
            AutoScaleMode = AutoScaleMode.Font;
            AutoSizeMode = AutoSizeMode.GrowAndShrink;
            BackgroundImageLayout = ImageLayout.Stretch;
            ClientSize = new Size(793, 377);
            Controls.Add(EndCompetitionsListView);
            Controls.Add(AreaListView);
            Controls.Add(CompetitionsListView);
            Controls.Add(RunButton);
            Font = new Font("Segoe UI", 12F, FontStyle.Regular, GraphicsUnit.Point);
            Margin = new Padding(4, 3, 4, 3);
            Name = "Form1";
            StartPosition = FormStartPosition.CenterScreen;
            Text = "Сочи-2014";
            Load += Form1_Load;
            ResumeLayout(false);
        }

        #endregion

        private Button RunButton;
        private ListView CompetitionsListView;
        private ColumnHeader CompetitionsHeader;
        private ListView AreaListView;
        private ColumnHeader AreaHeader;
        private ColumnHeader CompetitionHeader;
        private ColumnHeader StatusHeader;
        private ListView EndCompetitionsListView;
        private ColumnHeader EndCompetitionsHeader;
    }
}