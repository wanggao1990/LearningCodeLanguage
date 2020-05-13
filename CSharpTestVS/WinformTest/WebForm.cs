using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WinformTest
{
    public partial class WebForm : Form
    {
        public WebForm()
        {
            InitializeComponent();

            webBrowser1.Dock = DockStyle.Top;
            //webBrowser1.Width = this.ClientRectangle.Size.Width;
            //webBrowser1.Height = this.ClientRectangle.Size.Height - toolStrip1.Height;
            WebForm_ClientSizeChanged(this, new EventArgs());
        }

        private void webBrowser1_Navigated(object sender, WebBrowserNavigatedEventArgs e)
        {
            textBox1.Text = webBrowser1.Url.ToString();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            textBox1.Text = "www.baidu.com";
            webBrowser1.Navigate(textBox1.Text);
        }

        private void button2_Click(object sender, EventArgs e)
        {
            webBrowser1.Navigate(textBox1.Text); //加载Url
        }

        private void WebForm_ClientSizeChanged(object sender, EventArgs e)
        {
            //Debug.WriteLine(this.ClientRectangle.Size);
            //webBrowser1.Width = this.ClientRectangle.Size.Width;
            //webBrowser1.Height = this.ClientRectangle.Size.Height - toolStrip1.Height;
            //webBrowser1.Update();

            // 必须设置 DockStyle为 top
            webBrowser1.Width = this.ClientRectangle.Size.Width;
            webBrowser1.Height = this.ClientRectangle.Size.Height - toolStrip1.Height;

        }

        private void textBox1_KeyUp(object sender, KeyPressEventArgs e)
        {
            if ((char)Keys.Enter == e.KeyChar)
            {
                webBrowser1.Navigate(textBox1.Text);
            }
        }

        private void back_btn_Click(object sender, EventArgs e)
        {
            webBrowser1.GoBack();
        }

        private void stop_btn_Click(object sender, EventArgs e)
        {
            webBrowser1.Stop();
        }

        private void forward_btn_Click(object sender, EventArgs e)
        {
            webBrowser1.GoForward();
        }


        private void webBrowser1_NewWindow(object sender, CancelEventArgs e)
        {
            e.Cancel = true;
            string url = this.webBrowser1.StatusText;
            this.webBrowser1.Url = new Uri(url);
        }


    }
}
