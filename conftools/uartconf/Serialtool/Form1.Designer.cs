namespace Serialtool
{
    partial class Form1
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要修改
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            System.Windows.Forms.DataVisualization.Charting.ChartArea chartArea1 = new System.Windows.Forms.DataVisualization.Charting.ChartArea();
            System.Windows.Forms.DataVisualization.Charting.Legend legend1 = new System.Windows.Forms.DataVisualization.Charting.Legend();
            System.Windows.Forms.DataVisualization.Charting.Series series1 = new System.Windows.Forms.DataVisualization.Charting.Series();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.label2 = new System.Windows.Forms.Label();
            this.btn_serial_sw = new System.Windows.Forms.Button();
            this.cbx_comx = new System.Windows.Forms.ComboBox();
            this.label1 = new System.Windows.Forms.Label();
            this.tbx_revdata = new System.Windows.Forms.TextBox();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.groupBox4 = new System.Windows.Forms.GroupBox();
            this.btn_send = new System.Windows.Forms.Button();
            this.tbx_senddata = new System.Windows.Forms.TextBox();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.tabControl1 = new System.Windows.Forms.TabControl();
            this.tabPage1 = new System.Windows.Forms.TabPage();
            this.tabPage2 = new System.Windows.Forms.TabPage();
            this.groupBox5 = new System.Windows.Forms.GroupBox();
            this.btn_getconf = new System.Windows.Forms.Button();
            this.btn_setworkmode = new System.Windows.Forms.Button();
            this.label3 = new System.Windows.Forms.Label();
            this.cbx_workmode = new System.Windows.Forms.ComboBox();
            this.chart1 = new System.Windows.Forms.DataVisualization.Charting.Chart();
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.groupBox4.SuspendLayout();
            this.groupBox3.SuspendLayout();
            this.tabControl1.SuspendLayout();
            this.groupBox5.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.chart1)).BeginInit();
            this.SuspendLayout();
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.label2);
            this.groupBox1.Controls.Add(this.btn_serial_sw);
            this.groupBox1.Controls.Add(this.cbx_comx);
            this.groupBox1.Controls.Add(this.label1);
            this.groupBox1.Location = new System.Drawing.Point(12, 12);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(120, 105);
            this.groupBox1.TabIndex = 0;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Serial_Information";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(6, 82);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(113, 12);
            this.label2.TabIndex = 3;
            this.label2.Text = "Default:115200 8N1";
            // 
            // btn_serial_sw
            // 
            this.btn_serial_sw.Location = new System.Drawing.Point(8, 51);
            this.btn_serial_sw.Name = "btn_serial_sw";
            this.btn_serial_sw.Size = new System.Drawing.Size(87, 28);
            this.btn_serial_sw.TabIndex = 2;
            this.btn_serial_sw.Text = "Open";
            this.btn_serial_sw.UseVisualStyleBackColor = true;
            this.btn_serial_sw.Click += new System.EventHandler(this.btn_serial_sw_Click);
            // 
            // cbx_comx
            // 
            this.cbx_comx.FormattingEnabled = true;
            this.cbx_comx.Location = new System.Drawing.Point(35, 28);
            this.cbx_comx.Name = "cbx_comx";
            this.cbx_comx.Size = new System.Drawing.Size(60, 20);
            this.cbx_comx.TabIndex = 1;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(6, 36);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(29, 12);
            this.label1.TabIndex = 0;
            this.label1.Text = "COM:";
            // 
            // tbx_revdata
            // 
            this.tbx_revdata.Location = new System.Drawing.Point(15, 30);
            this.tbx_revdata.Multiline = true;
            this.tbx_revdata.Name = "tbx_revdata";
            this.tbx_revdata.Size = new System.Drawing.Size(602, 55);
            this.tbx_revdata.TabIndex = 1;
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.groupBox4);
            this.groupBox2.Controls.Add(this.groupBox3);
            this.groupBox2.Location = new System.Drawing.Point(138, 12);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(637, 176);
            this.groupBox2.TabIndex = 2;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Data";
            // 
            // groupBox4
            // 
            this.groupBox4.Controls.Add(this.btn_send);
            this.groupBox4.Controls.Add(this.tbx_senddata);
            this.groupBox4.Location = new System.Drawing.Point(6, 123);
            this.groupBox4.Name = "groupBox4";
            this.groupBox4.Size = new System.Drawing.Size(623, 48);
            this.groupBox4.TabIndex = 3;
            this.groupBox4.TabStop = false;
            this.groupBox4.Text = "Send";
            // 
            // btn_send
            // 
            this.btn_send.Location = new System.Drawing.Point(534, 19);
            this.btn_send.Name = "btn_send";
            this.btn_send.Size = new System.Drawing.Size(83, 21);
            this.btn_send.TabIndex = 1;
            this.btn_send.Text = "Send";
            this.btn_send.UseVisualStyleBackColor = true;
            this.btn_send.Click += new System.EventHandler(this.btn_send_Click);
            // 
            // tbx_senddata
            // 
            this.tbx_senddata.Location = new System.Drawing.Point(15, 20);
            this.tbx_senddata.Name = "tbx_senddata";
            this.tbx_senddata.Size = new System.Drawing.Size(497, 21);
            this.tbx_senddata.TabIndex = 0;
            // 
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.tbx_revdata);
            this.groupBox3.Location = new System.Drawing.Point(6, 20);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(623, 97);
            this.groupBox3.TabIndex = 2;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "Rev";
            // 
            // tabControl1
            // 
            this.tabControl1.Controls.Add(this.tabPage1);
            this.tabControl1.Controls.Add(this.tabPage2);
            this.tabControl1.Location = new System.Drawing.Point(20, 194);
            this.tabControl1.Name = "tabControl1";
            this.tabControl1.SelectedIndex = 0;
            this.tabControl1.Size = new System.Drawing.Size(702, 337);
            this.tabControl1.TabIndex = 3;
            // 
            // tabPage1
            // 
            this.tabPage1.Location = new System.Drawing.Point(4, 22);
            this.tabPage1.Name = "tabPage1";
            this.tabPage1.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage1.Size = new System.Drawing.Size(694, 311);
            this.tabPage1.TabIndex = 0;
            this.tabPage1.Text = "tabPage1";
            this.tabPage1.UseVisualStyleBackColor = true;
            // 
            // tabPage2
            // 
            this.tabPage2.Location = new System.Drawing.Point(4, 22);
            this.tabPage2.Name = "tabPage2";
            this.tabPage2.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage2.Size = new System.Drawing.Size(694, 311);
            this.tabPage2.TabIndex = 1;
            this.tabPage2.Text = "tabPage2";
            this.tabPage2.UseVisualStyleBackColor = true;
            // 
            // groupBox5
            // 
            this.groupBox5.Controls.Add(this.btn_getconf);
            this.groupBox5.Controls.Add(this.btn_setworkmode);
            this.groupBox5.Controls.Add(this.label3);
            this.groupBox5.Controls.Add(this.cbx_workmode);
            this.groupBox5.Location = new System.Drawing.Point(781, 12);
            this.groupBox5.Name = "groupBox5";
            this.groupBox5.Size = new System.Drawing.Size(310, 294);
            this.groupBox5.TabIndex = 4;
            this.groupBox5.TabStop = false;
            this.groupBox5.Text = "Conf";
            // 
            // btn_getconf
            // 
            this.btn_getconf.Location = new System.Drawing.Point(229, 265);
            this.btn_getconf.Name = "btn_getconf";
            this.btn_getconf.Size = new System.Drawing.Size(75, 23);
            this.btn_getconf.TabIndex = 3;
            this.btn_getconf.Text = "GetConf";
            this.btn_getconf.UseVisualStyleBackColor = true;
            // 
            // btn_setworkmode
            // 
            this.btn_setworkmode.Location = new System.Drawing.Point(199, 26);
            this.btn_setworkmode.Name = "btn_setworkmode";
            this.btn_setworkmode.Size = new System.Drawing.Size(75, 23);
            this.btn_setworkmode.TabIndex = 2;
            this.btn_setworkmode.Text = "SetMode";
            this.btn_setworkmode.UseVisualStyleBackColor = true;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(25, 31);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(53, 12);
            this.label3.TabIndex = 1;
            this.label3.Text = "工作模式";
            // 
            // cbx_workmode
            // 
            this.cbx_workmode.FormattingEnabled = true;
            this.cbx_workmode.Location = new System.Drawing.Point(96, 28);
            this.cbx_workmode.Name = "cbx_workmode";
            this.cbx_workmode.Size = new System.Drawing.Size(83, 20);
            this.cbx_workmode.TabIndex = 0;
            // 
            // chart1
            // 
            chartArea1.Name = "ChartArea1";
            this.chart1.ChartAreas.Add(chartArea1);
            legend1.Name = "Legend1";
            this.chart1.Legends.Add(legend1);
            this.chart1.Location = new System.Drawing.Point(728, 331);
            this.chart1.Name = "chart1";
            series1.ChartArea = "ChartArea1";
            series1.Legend = "Legend1";
            series1.Name = "Series1";
            this.chart1.Series.Add(series1);
            this.chart1.Size = new System.Drawing.Size(300, 300);
            this.chart1.TabIndex = 5;
            this.chart1.Text = "chart1";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1103, 643);
            this.Controls.Add(this.chart1);
            this.Controls.Add(this.groupBox5);
            this.Controls.Add(this.tabControl1);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox1);
            this.Name = "Form1";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox4.ResumeLayout(false);
            this.groupBox4.PerformLayout();
            this.groupBox3.ResumeLayout(false);
            this.groupBox3.PerformLayout();
            this.tabControl1.ResumeLayout(false);
            this.groupBox5.ResumeLayout(false);
            this.groupBox5.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.chart1)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Button btn_serial_sw;
        private System.Windows.Forms.ComboBox cbx_comx;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox tbx_revdata;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.GroupBox groupBox4;
        private System.Windows.Forms.TextBox tbx_senddata;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.Button btn_send;
        private System.Windows.Forms.TabControl tabControl1;
        private System.Windows.Forms.TabPage tabPage1;
        private System.Windows.Forms.TabPage tabPage2;
        private System.Windows.Forms.GroupBox groupBox5;
        private System.Windows.Forms.Button btn_setworkmode;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.ComboBox cbx_workmode;
        private System.Windows.Forms.Button btn_getconf;
        private System.Windows.Forms.DataVisualization.Charting.Chart chart1;
    }
}

