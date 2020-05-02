using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WinformTest
{
    public partial class RegForm : Form
    {
        /// method 1
        public delegate void SendDataInvoke(string name, string psw);
        public event SendDataInvoke SendData;

        /// method 2
        public string name;
        public string psw;

        public RegForm()                            // method1, method2
        {
            InitializeComponent();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (String.IsNullOrEmpty(textBox1.Text))
            {
                MessageBox.Show("账号不能为空");
                return;
            }
            else if (String.IsNullOrEmpty(textBox2.Text))
            {
                MessageBox.Show("密码不能为空");
                return;
            }
            else if (!String.Equals(textBox2.Text, textBox3.Text))
            {
                MessageBox.Show("两次输入密码不同");
                return;
            }

            /// method 1
            // SendData(textBox1.Text, textBox2.Text);

            // method 2
            this.name = textBox1.Text;
            this.psw = textBox2.Text;



            Close();
        }
    }
}
