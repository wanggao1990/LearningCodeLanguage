namespace WinformTest
{
    partial class WebForm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
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
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(WebForm));
            this.flowLayoutPanel1 = new System.Windows.Forms.FlowLayoutPanel();
            this.toolStrip1 = new System.Windows.Forms.ToolStrip();
            this.button1 = new System.Windows.Forms.ToolStripButton();
            this.textBox1 = new System.Windows.Forms.ToolStripTextBox();
            this.button2 = new System.Windows.Forms.ToolStripButton();
            this.back_btn = new System.Windows.Forms.ToolStripButton();
            this.stop_btn = new System.Windows.Forms.ToolStripButton();
            this.forward_btn = new System.Windows.Forms.ToolStripButton();
            this.webBrowser1 = new System.Windows.Forms.WebBrowser();
            this.flowLayoutPanel1.SuspendLayout();
            this.toolStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // flowLayoutPanel1
            // 
            this.flowLayoutPanel1.Controls.Add(this.toolStrip1);
            this.flowLayoutPanel1.Controls.Add(this.webBrowser1);
            this.flowLayoutPanel1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.flowLayoutPanel1.Location = new System.Drawing.Point(0, 0);
            this.flowLayoutPanel1.Name = "flowLayoutPanel1";
            this.flowLayoutPanel1.Size = new System.Drawing.Size(598, 358);
            this.flowLayoutPanel1.TabIndex = 2;
            // 
            // toolStrip1
            // 
            this.toolStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.button1,
            this.textBox1,
            this.button2,
            this.back_btn,
            this.stop_btn,
            this.forward_btn});
            this.toolStrip1.Location = new System.Drawing.Point(0, 0);
            this.toolStrip1.Name = "toolStrip1";
            this.toolStrip1.Size = new System.Drawing.Size(460, 25);
            this.toolStrip1.TabIndex = 5;
            this.toolStrip1.Text = "toolStrip1";
            // 
            // button1
            // 
            this.button1.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.button1.Image = ((System.Drawing.Image)(resources.GetObject("button1.Image")));
            this.button1.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(23, 22);
            this.button1.Text = "主页";
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // textBox1
            // 
            this.textBox1.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.textBox1.Name = "textBox1";
            this.textBox1.Size = new System.Drawing.Size(300, 25);
            this.textBox1.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.textBox1_KeyUp);
            // 
            // button2
            // 
            this.button2.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.button2.Image = global::WinformTest.Properties.Resources.refresh_Image;
            this.button2.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(23, 22);
            this.button2.Text = "刷新";
            this.button2.Click += new System.EventHandler(this.button2_Click);
            // 
            // back_btn
            // 
            this.back_btn.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.back_btn.Image = global::WinformTest.Properties.Resources.button1_Image;
            this.back_btn.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.back_btn.Name = "back_btn";
            this.back_btn.Size = new System.Drawing.Size(23, 22);
            this.back_btn.Text = "后退";
            this.back_btn.Click += new System.EventHandler(this.back_btn_Click);
            // 
            // stop_btn
            // 
            this.stop_btn.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.stop_btn.Image = global::WinformTest.Properties.Resources.button3_Image;
            this.stop_btn.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.stop_btn.Name = "stop_btn";
            this.stop_btn.Size = new System.Drawing.Size(23, 22);
            this.stop_btn.Text = "停止";
            this.stop_btn.Click += new System.EventHandler(this.stop_btn_Click);
            // 
            // forward_btn
            // 
            this.forward_btn.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.forward_btn.Image = global::WinformTest.Properties.Resources.button2_Image;
            this.forward_btn.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.forward_btn.Name = "forward_btn";
            this.forward_btn.Size = new System.Drawing.Size(23, 22);
            this.forward_btn.Text = "前进";
            this.forward_btn.Click += new System.EventHandler(this.forward_btn_Click);
            // 
            // webBrowser1
            // 
            this.webBrowser1.Dock = System.Windows.Forms.DockStyle.Top;
            this.flowLayoutPanel1.SetFlowBreak(this.webBrowser1, true);
            this.webBrowser1.IsWebBrowserContextMenuEnabled = false;
            this.webBrowser1.Location = new System.Drawing.Point(3, 28);
            this.webBrowser1.MinimumSize = new System.Drawing.Size(400, 200);
            this.webBrowser1.Name = "webBrowser1";
            this.webBrowser1.Size = new System.Drawing.Size(400, 200);
            this.webBrowser1.TabIndex = 6;
            this.webBrowser1.NewWindow += new System.ComponentModel.CancelEventHandler(this.webBrowser1_NewWindow);
            // 
            // WebForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(598, 358);
            this.Controls.Add(this.flowLayoutPanel1);
            this.MinimumSize = new System.Drawing.Size(400, 200);
            this.Name = "WebForm";
            this.Text = "WebForm";
            this.ClientSizeChanged += new System.EventHandler(this.WebForm_ClientSizeChanged);
            this.flowLayoutPanel1.ResumeLayout(false);
            this.flowLayoutPanel1.PerformLayout();
            this.toolStrip1.ResumeLayout(false);
            this.toolStrip1.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.FlowLayoutPanel flowLayoutPanel1;
        private System.Windows.Forms.ToolStrip toolStrip1;
        private System.Windows.Forms.ToolStripButton button1;
        private System.Windows.Forms.ToolStripButton button2;
        private System.Windows.Forms.ToolStripTextBox textBox1;
        private System.Windows.Forms.ToolStripButton stop_btn;
        private System.Windows.Forms.ToolStripButton forward_btn;
        private System.Windows.Forms.ToolStripButton back_btn;
        private System.Windows.Forms.WebBrowser webBrowser1;
    }
}