namespace WinformTest
{
    partial class OpencvForm
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
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.nativeFuncToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.func1ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.menuStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.nativeFuncToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(501, 25);
            this.menuStrip1.TabIndex = 2;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // nativeFuncToolStripMenuItem
            // 
            this.nativeFuncToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.func1ToolStripMenuItem});
            this.nativeFuncToolStripMenuItem.Name = "nativeFuncToolStripMenuItem";
            this.nativeFuncToolStripMenuItem.Size = new System.Drawing.Size(82, 21);
            this.nativeFuncToolStripMenuItem.Text = "native func";
            // 
            // func1ToolStripMenuItem
            // 
            this.func1ToolStripMenuItem.Name = "func1ToolStripMenuItem";
            this.func1ToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
            this.func1ToolStripMenuItem.Text = "func1";
            this.func1ToolStripMenuItem.Click += new System.EventHandler(this.func1ToolStripMenuItem_Click);
            // 
            // OpencvForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(501, 393);
            this.Controls.Add(this.menuStrip1);
            this.IsMdiContainer = true;
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "OpencvForm";
            this.Text = "OpencvForm";
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem nativeFuncToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem func1ToolStripMenuItem;
    }
}