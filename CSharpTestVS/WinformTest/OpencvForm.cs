using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;

using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;


using System.Drawing.Imaging;
using System.Drawing;

namespace WinformTest
{
    public partial class OpencvForm : Form
    {

        private NativeDllTest instance;

        public OpencvForm()
        {
            InitializeComponent();

            instance = new NativeDllTest();
        }

        private void func1ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            instance.testNativeFunc();
        }

        private void openImageToolStripMenuItem_Click(object sender, EventArgs e)
        {
            // file dialog的属性
            OpenFileDialog openFileDialog1 = new OpenFileDialog();
            openFileDialog1.Multiselect = false;  //单选
            openFileDialog1.Filter = "JPG|*.jpg|PNG|*.png|BMP|*.bmp";

            DialogResult dr = openFileDialog1.ShowDialog();
            if (DialogResult.OK == dr)
            {
                Form form = new Form();
                form.MdiParent = this;
                form.BackgroundImage = Image.FromFile(openFileDialog1.FileName);
                //PictureBox pbox = new PictureBox();
                //pbox.Image = Image.FromFile(openFileDialog1.FileName);
                //pbox.Size = pbox.Image.Size;
                //form.Controls.Add(pbox);
                form.Show();
            }

        }

        private void grayScaleToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (this.ActiveMdiChild == null)
            {
                MessageBox.Show("No active form.");
                return;
            }

            Form child = this.ActiveMdiChild;
            Image image = child.BackgroundImage;
            if (image == null)
            {
                MessageBox.Show("Empty image");
                return;
            }

            Bitmap res;
            instance.grayScale((Bitmap)image, out res);
            if(null == res)
            {
                MessageBox.Show("image is already gray.");
                return;
            }


            Form grayForm = new Form();
            grayForm.BackgroundImage = res;
            grayForm.MdiParent = this;
            grayForm.Show();
        }
    }
}
