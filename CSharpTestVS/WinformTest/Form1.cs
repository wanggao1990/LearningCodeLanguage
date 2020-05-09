using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

using System.Threading;

namespace WinformTest
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();

            timer1.Tick += delegate {
                Winform_MouseClick(this, new MouseEventArgs(MouseButtons.Left, 0, 0, 0, 0));
            };

            timer2.Tick += delegate { dateTimePicker1.ResetText();  };
            timer2.Interval = 1000;
            timer2.Enabled = true;
        }

        private MdiClient mdiClient;

        private void Form1_Load(object sender, EventArgs e)
        {
            // this.BackColor = Color.Green;

            foreach (Control c in this.Controls)
            {
                if (c.GetType().ToString() ==
                    "System.Windows.Forms.MdiClient")
                    mdiClient = (MdiClient)c;
            }
        }


        private void Form1_Click(object sender, EventArgs e)
        {
            Winform_MouseClick(sender, new MouseEventArgs(MouseButtons.Left,0,0,0,0));
        }

        private void Winform_FormClosing(object sender, FormClosingEventArgs e)
        {
            //if (DialogResult.No == MessageBox.Show("确认退出？", "提示", MessageBoxButtons.YesNo))
            //    e.Cancel = true;
        }


        private Color getRandomColor()
        {
            Random rng = new Random();
            byte[] rgb = new byte[3];
            rng.NextBytes(rgb);
            return Color.FromArgb(255, rgb[0], rgb[1], rgb[2]);
        }

        private void Winform_MouseClick(object sender, MouseEventArgs e)
        {

            if (e.Button == MouseButtons.Left)
            {
                if (!this.IsMdiContainer)
                {
                    BackColor = getRandomColor();
                }
                else
                {
                    // mdi窗口中有子窗口时不能修改背景色
                    // mdiClient.BackColor = getRandomColor();
                    //foreach (Form form in this.MdiChildren)
                    //{
                    //    form.Activate();
                    //    form.BackColor = getRandomColor();
                    //}
                    Form form = this.ActiveMdiChild;
                    if (form != null)
                    {
                        form.BackColor = getRandomColor();
                    }
                }

            }
            else if (e.Button == MouseButtons.Right)
            {
                //弹出消息框，并获取消息框的返回值
                DialogResult dr = MessageBox.Show("是否打开新窗体？", "提示", MessageBoxButtons.YesNo, MessageBoxIcon.Warning);
                //如果消息框返回值是Yes，显示新窗体
                if (dr == DialogResult.Yes)
                {
                    Form messageForm = new Form();
                    messageForm.Show();
                }
            }
        }

        private void linkLabel1_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            String tmp = this.label1.Text;
            this.label1.Text = this.label2.Text;
            this.label2.Text = tmp;
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {
            label3.Text = textBox1.Text;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (textBox2.Text != this.name)
            {
                MessageBox.Show("账号不正确！");
            }
            else if ( textBox3.Text != this.psw)
            {
                MessageBox.Show("密码错误！");
            }
            else
            {
                MessageBox.Show("登陆成功！");
            }
        }

        private void textBox3_PreviewKeyDown(object sender, PreviewKeyDownEventArgs e)
        {
            if(e.KeyData == Keys.Enter)
            {
                button1_Click(sender, e);
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {

            /// method  1
            //RegForm regForm = new RegForm();
            //regForm.SendData += delegate (string name, string psw)
            //{
            //    this.name = name; this.psw = psw;
            //};
            //regForm.ShowDialog();
            //regForm.Dispose();

            /// method  2
            /// // 下次取消后，密码被重置，窗体一直存活? 越来越多？
            RegForm regForm = new RegForm();
            if (DialogResult.OK == regForm.ShowDialog())// 设置dialog返回结果
            {   
                this.name = regForm.name;
                this.psw = regForm.psw;
            }
            regForm.Dispose();
        }

        private void button3_Click(object sender, EventArgs e)
        {
            string msg = "";
            if (radioButton1.Checked) msg = radioButton1.Text;
            else if (radioButton2.Checked) msg = radioButton2.Text;
            else if (radioButton3.Checked) msg = radioButton3.Text;
            if (msg != "")
                MessageBox.Show("您选择的权限是：" + msg, "提示");
            else
                MessageBox.Show("您没有选择权限", "提示");

        }

        private void button4_Click(object sender, EventArgs e)
        {
            Boxes boxes = new Boxes();
            boxes.ShowDialog();
            boxes.Dispose();
        }

        private void notifyIcon1_BalloonTipClosed(object sender, EventArgs e)
        {
            this.Dispose();
        }

        private void button5_Click(object sender, EventArgs e)
        {
            if (numericUpDown1.Value == 0) return;

            if (button5.Text == "Start")
            {
                int newInterval = (int)(numericUpDown1.Value * 1000);
                if (newInterval != timer1.Interval)
                    timer1.Interval = newInterval;

                timer1.Enabled = true;
                numericUpDown1.Enabled = false;
                button5.Text = "Stop";
            }
            else
            {
                timer1.Enabled = false;
                numericUpDown1.Enabled = true;
                button5.Text = "Start";
            }

        }

        private void dateTimePicker1_CloseUp(object sender, EventArgs e)
        {
            timer2.Enabled = false ;
            new Thread( new ThreadStart(  delegate {
                MessageBox.Show("Select time: " + dateTimePicker1.ToString());
            })).Start();
            timer2.Enabled = true;
        }

        private void button6_Click(object sender, EventArgs e)
        {
            monthCalendar1.Show();
        }

        private void monthCalendar1_DateSelected(object sender, DateRangeEventArgs e)
        {
            textBox4.Text = monthCalendar1.SelectionStart.ToLongDateString();
            monthCalendar1.Hide();
        }

        private void splitContainer1_Panel1_MouseClick(object sender, MouseEventArgs e)
        {
            if(e.Button == MouseButtons.Left)
            {
                splitContainer1.Panel2.BackColor = getRandomColor();
            }

            // 可以直接进行绑定 contextMenuStrips属性， 参见notifyIcon的右键功能
            else if (e.Button == MouseButtons.Right)
            {
                contextMenuStrip1.Show(splitContainer1.Panel1, e.Location);
            }

        }

        private void toolStripButton1_Click(object sender, EventArgs e)
        {
            colorDialog1.ShowDialog();
        }

        private void toolStripLabel1_Click(object sender, EventArgs e)
        {
            //fontDialog1.ShowDialog();

            // 直接代码添加
            FontDialog fontDiag = new FontDialog();
            if (DialogResult.OK == fontDiag.ShowDialog())
                MessageBox.Show("Choose font:\n" + fontDiag.Font.ToString());
        }

        private void button7_Click(object sender, EventArgs e)
        {
            WebForm webForm = new WebForm();
            webForm.Show();
        }

        private void exitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            DialogResult dr = MessageBox.Show("确认退出？", "提示", MessageBoxButtons.OKCancel);
            if (DialogResult.OK == dr)
            {
                this.Close();
                this.Dispose();
            }
        }

        private void 最大化ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            
        }

        private void 最小化ToolStripMenuItem_Click(object sender, EventArgs e)
        {

        }

        private void mdi窗口ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            // 这里再不能修改背景颜色
            if (this.IsMdiContainer != true) this.IsMdiContainer = true;

            for (int i = 0; i < 2; i++)
            {
                Form form = new Form();
                form.Text = String.Format("mdi form %d", i);
                form.MdiParent = this;
                form.Show();
            }
        }

        private void button8_Click(object sender, EventArgs e)
        {
            (new OpencvForm()).ShowDialog();
        }
    }
}
