namespace WindowsFormsApplication1
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
            this.components = new System.ComponentModel.Container();
            this.serialPort1 = new System.IO.Ports.SerialPort(this.components);
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.button1 = new System.Windows.Forms.Button();
            this.label5 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.ComboBox_parity = new System.Windows.Forms.ComboBox();
            this.ComboBox_stopBit = new System.Windows.Forms.ComboBox();
            this.ComboBox_databit = new System.Windows.Forms.ComboBox();
            this.label1 = new System.Windows.Forms.Label();
            this.ComboBox_baud = new System.Windows.Forms.ComboBox();
            this.ComboBox_ports = new System.Windows.Forms.ComboBox();
            this.button3 = new System.Windows.Forms.Button();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.radioBtn_recv_HEX = new System.Windows.Forms.RadioButton();
            this.radioBtn_recv_ascii = new System.Windows.Forms.RadioButton();
            this.checkBox_autonextline = new System.Windows.Forms.CheckBox();
            this.button2 = new System.Windows.Forms.Button();
            this.sendBox = new System.Windows.Forms.TextBox();
            this.recvBox = new System.Windows.Forms.TextBox();
            this.splitContainer1 = new System.Windows.Forms.SplitContainer();
            this.checkBox_showlatest = new System.Windows.Forms.CheckBox();
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer1)).BeginInit();
            this.splitContainer1.Panel1.SuspendLayout();
            this.splitContainer1.Panel2.SuspendLayout();
            this.splitContainer1.SuspendLayout();
            this.SuspendLayout();
            // 
            // serialPort1
            // 
            this.serialPort1.DataReceived += new System.IO.Ports.SerialDataReceivedEventHandler(this.serialPort1_DataReceived);
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.button1);
            this.groupBox1.Controls.Add(this.label5);
            this.groupBox1.Controls.Add(this.label4);
            this.groupBox1.Controls.Add(this.label3);
            this.groupBox1.Controls.Add(this.label2);
            this.groupBox1.Controls.Add(this.ComboBox_parity);
            this.groupBox1.Controls.Add(this.ComboBox_stopBit);
            this.groupBox1.Controls.Add(this.ComboBox_databit);
            this.groupBox1.Controls.Add(this.label1);
            this.groupBox1.Controls.Add(this.ComboBox_baud);
            this.groupBox1.Controls.Add(this.ComboBox_ports);
            this.groupBox1.Location = new System.Drawing.Point(12, 12);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(129, 191);
            this.groupBox1.TabIndex = 0;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "串口设置";
            // 
            // button1
            // 
            this.button1.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            this.button1.Location = new System.Drawing.Point(8, 152);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(108, 33);
            this.button1.TabIndex = 2;
            this.button1.Text = "打开串口";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(6, 127);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(41, 12);
            this.label5.TabIndex = 1;
            this.label5.Text = "校验位";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(6, 101);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(41, 12);
            this.label4.TabIndex = 1;
            this.label4.Text = "停止位";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(6, 75);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(41, 12);
            this.label3.TabIndex = 1;
            this.label3.Text = "数据位";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(6, 48);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(41, 12);
            this.label2.TabIndex = 1;
            this.label2.Text = "波特率";
            // 
            // ComboBox_parity
            // 
            this.ComboBox_parity.AutoCompleteCustomSource.AddRange(new string[] {
            "无",
            "奇",
            "偶"});
            this.ComboBox_parity.FormattingEnabled = true;
            this.ComboBox_parity.Items.AddRange(new object[] {
            "None",
            "Odd",
            "Even"});
            this.ComboBox_parity.Location = new System.Drawing.Point(53, 124);
            this.ComboBox_parity.Name = "ComboBox_parity";
            this.ComboBox_parity.Size = new System.Drawing.Size(63, 20);
            this.ComboBox_parity.TabIndex = 0;
            this.ComboBox_parity.SelectedIndexChanged += new System.EventHandler(this.ComboBox_parity_SelectedIndexChanged);
            // 
            // ComboBox_stopBit
            // 
            this.ComboBox_stopBit.FormattingEnabled = true;
            this.ComboBox_stopBit.Items.AddRange(new object[] {
            "One",
            "Two",
            "OnePointFive"});
            this.ComboBox_stopBit.Location = new System.Drawing.Point(53, 98);
            this.ComboBox_stopBit.Name = "ComboBox_stopBit";
            this.ComboBox_stopBit.Size = new System.Drawing.Size(63, 20);
            this.ComboBox_stopBit.TabIndex = 0;
            this.ComboBox_stopBit.SelectedIndexChanged += new System.EventHandler(this.ComboBox_stopBit_SelectedIndexChanged);
            // 
            // ComboBox_databit
            // 
            this.ComboBox_databit.FormattingEnabled = true;
            this.ComboBox_databit.Items.AddRange(new object[] {
            "7",
            "8"});
            this.ComboBox_databit.Location = new System.Drawing.Point(53, 72);
            this.ComboBox_databit.Name = "ComboBox_databit";
            this.ComboBox_databit.Size = new System.Drawing.Size(63, 20);
            this.ComboBox_databit.TabIndex = 0;
            this.ComboBox_databit.SelectedIndexChanged += new System.EventHandler(this.ComboBox_databit_SelectedIndexChanged);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(6, 23);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(41, 12);
            this.label1.TabIndex = 1;
            this.label1.Text = "串口号";
            // 
            // ComboBox_baud
            // 
            this.ComboBox_baud.AutoCompleteCustomSource.AddRange(new string[] {
            "9600",
            "19200",
            "115200"});
            this.ComboBox_baud.FormattingEnabled = true;
            this.ComboBox_baud.Items.AddRange(new object[] {
            "9600",
            "19200",
            "115200"});
            this.ComboBox_baud.Location = new System.Drawing.Point(53, 45);
            this.ComboBox_baud.Name = "ComboBox_baud";
            this.ComboBox_baud.Size = new System.Drawing.Size(63, 20);
            this.ComboBox_baud.TabIndex = 0;
            this.ComboBox_baud.SelectedIndexChanged += new System.EventHandler(this.ComboBox_baud_SelectedIndexChanged);
            // 
            // ComboBox_ports
            // 
            this.ComboBox_ports.FormattingEnabled = true;
            this.ComboBox_ports.Location = new System.Drawing.Point(53, 20);
            this.ComboBox_ports.Name = "ComboBox_ports";
            this.ComboBox_ports.Size = new System.Drawing.Size(63, 20);
            this.ComboBox_ports.TabIndex = 0;
            // 
            // button3
            // 
            this.button3.Location = new System.Drawing.Point(13, 90);
            this.button3.Name = "button3";
            this.button3.Size = new System.Drawing.Size(75, 23);
            this.button3.TabIndex = 3;
            this.button3.Text = "clear";
            this.button3.UseVisualStyleBackColor = true;
            this.button3.Click += new System.EventHandler(this.button3_Click);
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.radioBtn_recv_HEX);
            this.groupBox2.Controls.Add(this.radioBtn_recv_ascii);
            this.groupBox2.Controls.Add(this.checkBox_showlatest);
            this.groupBox2.Controls.Add(this.checkBox_autonextline);
            this.groupBox2.Controls.Add(this.button3);
            this.groupBox2.Location = new System.Drawing.Point(12, 209);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(129, 119);
            this.groupBox2.TabIndex = 0;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "接收设置";
            // 
            // radioBtn_recv_HEX
            // 
            this.radioBtn_recv_HEX.AutoSize = true;
            this.radioBtn_recv_HEX.Location = new System.Drawing.Point(72, 18);
            this.radioBtn_recv_HEX.Name = "radioBtn_recv_HEX";
            this.radioBtn_recv_HEX.Size = new System.Drawing.Size(41, 16);
            this.radioBtn_recv_HEX.TabIndex = 5;
            this.radioBtn_recv_HEX.TabStop = true;
            this.radioBtn_recv_HEX.Text = "HEX";
            this.radioBtn_recv_HEX.UseVisualStyleBackColor = true;
            // 
            // radioBtn_recv_ascii
            // 
            this.radioBtn_recv_ascii.AutoSize = true;
            this.radioBtn_recv_ascii.Location = new System.Drawing.Point(13, 18);
            this.radioBtn_recv_ascii.Name = "radioBtn_recv_ascii";
            this.radioBtn_recv_ascii.Size = new System.Drawing.Size(53, 16);
            this.radioBtn_recv_ascii.TabIndex = 5;
            this.radioBtn_recv_ascii.TabStop = true;
            this.radioBtn_recv_ascii.Text = "ASCII";
            this.radioBtn_recv_ascii.UseVisualStyleBackColor = true;
            // 
            // checkBox_autonextline
            // 
            this.checkBox_autonextline.AutoSize = true;
            this.checkBox_autonextline.Location = new System.Drawing.Point(13, 43);
            this.checkBox_autonextline.Name = "checkBox_autonextline";
            this.checkBox_autonextline.Size = new System.Drawing.Size(108, 16);
            this.checkBox_autonextline.TabIndex = 4;
            this.checkBox_autonextline.Text = "接收区自动换行";
            this.checkBox_autonextline.UseVisualStyleBackColor = true;
            // 
            // button2
            // 
            this.button2.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.button2.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            this.button2.Location = new System.Drawing.Point(400, 6);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(46, 44);
            this.button2.TabIndex = 0;
            this.button2.Text = "send";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.button2_Click);
            // 
            // sendBox
            // 
            this.sendBox.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.sendBox.BackColor = System.Drawing.SystemColors.Window;
            this.sendBox.Location = new System.Drawing.Point(0, 6);
            this.sendBox.MinimumSize = new System.Drawing.Size(4, 20);
            this.sendBox.Multiline = true;
            this.sendBox.Name = "sendBox";
            this.sendBox.Size = new System.Drawing.Size(394, 44);
            this.sendBox.TabIndex = 1;
            // 
            // recvBox
            // 
            this.recvBox.BackColor = System.Drawing.SystemColors.Window;
            this.recvBox.Dock = System.Windows.Forms.DockStyle.Fill;
            this.recvBox.Location = new System.Drawing.Point(0, 0);
            this.recvBox.MinimumSize = new System.Drawing.Size(128, 50);
            this.recvBox.Multiline = true;
            this.recvBox.Name = "recvBox";
            this.recvBox.ReadOnly = true;
            this.recvBox.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.recvBox.Size = new System.Drawing.Size(446, 280);
            this.recvBox.TabIndex = 2;
            // 
            // splitContainer1
            // 
            this.splitContainer1.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.splitContainer1.Location = new System.Drawing.Point(147, 12);
            this.splitContainer1.Name = "splitContainer1";
            this.splitContainer1.Orientation = System.Windows.Forms.Orientation.Horizontal;
            // 
            // splitContainer1.Panel1
            // 
            this.splitContainer1.Panel1.Controls.Add(this.recvBox);
            // 
            // splitContainer1.Panel2
            // 
            this.splitContainer1.Panel2.Controls.Add(this.button2);
            this.splitContainer1.Panel2.Controls.Add(this.sendBox);
            this.splitContainer1.Size = new System.Drawing.Size(446, 337);
            this.splitContainer1.SplitterDistance = 280;
            this.splitContainer1.TabIndex = 3;
            // 
            // checkBox_showlatest
            // 
            this.checkBox_showlatest.AutoSize = true;
            this.checkBox_showlatest.Location = new System.Drawing.Point(13, 65);
            this.checkBox_showlatest.Name = "checkBox_showlatest";
            this.checkBox_showlatest.Size = new System.Drawing.Size(108, 16);
            this.checkBox_showlatest.TabIndex = 4;
            this.checkBox_showlatest.Text = "显示最新接收行";
            this.checkBox_showlatest.UseVisualStyleBackColor = true;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(605, 361);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.splitContainer1);
            this.MinimumSize = new System.Drawing.Size(600, 400);
            this.Name = "Form1";
            this.Text = "Form1";
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.splitContainer1.Panel1.ResumeLayout(false);
            this.splitContainer1.Panel1.PerformLayout();
            this.splitContainer1.Panel2.ResumeLayout(false);
            this.splitContainer1.Panel2.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer1)).EndInit();
            this.splitContainer1.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.IO.Ports.SerialPort serialPort1;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.ComboBox ComboBox_ports;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.ComboBox ComboBox_databit;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.ComboBox ComboBox_baud;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.TextBox sendBox;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.ComboBox ComboBox_parity;
        private System.Windows.Forms.ComboBox ComboBox_stopBit;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.Button button3;
        private System.Windows.Forms.TextBox recvBox;
        private System.Windows.Forms.SplitContainer splitContainer1;
        private System.Windows.Forms.CheckBox checkBox_autonextline;
        private System.Windows.Forms.RadioButton radioBtn_recv_HEX;
        private System.Windows.Forms.RadioButton radioBtn_recv_ascii;
        private System.Windows.Forms.CheckBox checkBox_showlatest;
    }
}

