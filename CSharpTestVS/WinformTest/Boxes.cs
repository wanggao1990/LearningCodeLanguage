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
    public partial class Boxes : Form
    {
        public Boxes()
        {
            InitializeComponent();

            pictureBox1.SizeMode = PictureBoxSizeMode.Zoom;
            pictureBox1.AllowDrop = true;

            // 可以在属性中设置，可以dragdrop但是不显示内容
            richTextBox1.AllowDrop = true;
            richTextBox1.DragEnter += delegate (object sender, DragEventArgs e)
            {
                if (e.Data.GetDataPresent(DataFormats.FileDrop))
                    e.Effect = DragDropEffects.Link;
                else
                    e.Effect = DragDropEffects.None;
            };
            richTextBox1.DragDrop += delegate (object sender, DragEventArgs e)
            {
                string file = ((System.Array)e.Data.GetData(DataFormats.FileDrop)).GetValue(0).ToString();
                if (file.Contains(".txt"))
                    richTextBox1.LoadFile(file, RichTextBoxStreamType.PlainText);
                else if (file.Contains(".rtf"))
                    richTextBox1.LoadFile(file, RichTextBoxStreamType.RichText);
            };

        }

        private void button4_Click(object sender, EventArgs e)
        {
            string msg = "";
            //if (checkBox1.Checked)msg = msg + " " + checkBox1.Text;
            //if (checkBox2.Checked)msg = msg + " " + checkBox2.Text;
            //if (checkBox3.Checked) msg = msg + " " + checkBox3.Text;
            //if (checkBox4.Checked) msg = msg + " " + checkBox4.Text;

            foreach (Control c in Controls)
            {
                if (c is CheckBox)
                {
                    if (((CheckBox)c).Checked)
                        msg += " " + ((CheckBox)c).Text;
                }
                else if (c is GroupBox)
                {
                    foreach (Control gc in ((GroupBox)c).Controls)
                    {
                        if (gc is CheckBox)
                            if (((CheckBox)gc).Checked)
                                msg += " " + ((CheckBox)gc).Text;
                    }
                }
            }

            if (msg != "")
                MessageBox.Show("您选择的爱好是：" + msg, "提示");
            else
                MessageBox.Show("您没有选择爱好", "提示");
        }

        private void button5_Click_1(object sender, EventArgs e)
        {
            string msg = "";

            for (int i = 0; i < checkedListBox1.CheckedItems.Count; i++)
                msg += " " + checkedListBox1.CheckedItems[i].ToString();

            //// checkedListBox 选中所有项中就是最后一个
            //foreach (string s in checkedListBox1.SelectedItems)
            //    msg += " " + s;

            if (msg != "") MessageBox.Show("您购买的水果有：" + msg, "提示");
            else           MessageBox.Show("您没有选购水果！", "提示");

        
        }


        private void checkedListBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            label1.Text = "item: " + ((CheckedListBox)sender).SelectedItem.ToString();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            button2.BackColor = Color.LightGray;
            listBox1.SelectionMode = SelectionMode.One;
            button1.BackColor = Color.AliceBlue;
        }

        private void button2_Click(object sender, EventArgs e)
        {
            button1.BackColor = Color.LightGray;
            listBox1.SelectionMode = SelectionMode.MultiSimple;
            button2.BackColor = Color.AliceBlue;
        }

        private void listBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            label2.Text = "item: " + ((ListBox)sender).SelectedItem;
        }

        private void button3_Click(object sender, EventArgs e)
        {
            string msg = "";

            for (int i = 0; i < listBox1.SelectedItems.Count; i++)
                msg += " " + listBox1.SelectedItems[i].ToString();

            if (msg != "") MessageBox.Show("list all：" + msg, "提示");
            else MessageBox.Show("no celect list！", "提示");
        }

        private void button6_Click(object sender, EventArgs e)
        {
            if (String.IsNullOrEmpty(textBox1.Text))
                return ;

            if (listBox1.Items.Contains(textBox1.Text))
            {
                MessageBox.Show(String.Format("项 {0} 已存在",textBox1.Text));
                return;
            }

            listBox1.Items.Add(textBox1.Text);
        }

        private void button7_Click(object sender, EventArgs e)
        {
            foreach (int i in listBox1.SelectedIndices)
                listBox1.Items.RemoveAt(i);
        }

        private void button8_Click(object sender, EventArgs e)
        {
            if (String.IsNullOrEmpty(textBox2.Text))
                return;

            if (comboBox1.Items.Contains(textBox2.Text))
            {
                MessageBox.Show(String.Format("项 {0} 已存在", textBox2.Text));
                return;
            }

            comboBox1.Items.Add(textBox2.Text);
        }

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            textBox2.Text = comboBox1.SelectedItem.ToString();
        }

        private void button9_Click(object sender, EventArgs e)
        {
            if(comboBox1.SelectedIndex >= 0)
                comboBox1.Items.RemoveAt(comboBox1.SelectedIndex);
            else
            {
                if (String.IsNullOrEmpty(textBox2.Text)) return;
                comboBox1.Items.Remove(textBox2.Text);
            }
        }

        private void button10_Click(object sender, EventArgs e)
        {
            // file dialog的属性
            openFileDialog1.Multiselect = false;  //单选
            openFileDialog1.Filter = "JPG|*.jpg|PNG|*.png|BMP|*.bmp";

            DialogResult dr = openFileDialog1.ShowDialog();
            if (DialogResult.OK == dr)
            {
                // 根据是否可以多选修改代码
                //MessageBox.Show(openFileDialog1.FileName);
                if (openFileDialog1.FileName != pictureBox1.ImageLocation)
                {
                    pictureBox1.ImageLocation = openFileDialog1.FileName;
                    pictureBox1.Load();
                }
            }
        }

        private void pictureBox1_DragDrop(object sender, DragEventArgs e)
        {
            string file = ((System.Array)e.Data.GetData(DataFormats.FileDrop)).GetValue(0).ToString();

            if(file.Contains(".bmp") || file.Contains(".jpg") || file.Contains(".png"))
            {
                if (file != pictureBox1.ImageLocation)
                {
                    pictureBox1.ImageLocation = file;
                    pictureBox1.Load();
                }
            }
        }
        private void pictureBox1_DragEnter(object sender, DragEventArgs e)
        {
            if (e.Data.GetDataPresent(DataFormats.FileDrop))
                e.Effect = DragDropEffects.Link;
            else
                e.Effect = DragDropEffects.None;
        }


        private void button11_Click(object sender, EventArgs e)
        {
            if (String.IsNullOrEmpty(pictureBox1.ImageLocation)) return;

            saveFileDialog1.Filter = "JPG|*.jpg|PNG|*.png|BMP|*.bmp";
            saveFileDialog1.AddExtension = false;
            saveFileDialog1.DefaultExt = "JPG";

            DialogResult dr = saveFileDialog1.ShowDialog();
            if (DialogResult.OK == dr)
            {
                // pictureBox1.Image.
                //MessageBox.Show("file: " + saveFileDialog1.FileName +
                //    "\next: " + saveFileDialog1);

                int npos = saveFileDialog1.FileName.ToString().LastIndexOf('.');
                string fileName = saveFileDialog1.FileName.Substring(0, npos);
                fileName += DateTime.Now.ToLocalTime().ToString("_yyyyMMddHHmmss") + saveFileDialog1.FileName.Substring(npos);

                if (saveFileDialog1.FilterIndex == 1) // jpg
                    pictureBox1.Image.Save(fileName, System.Drawing.Imaging.ImageFormat.Jpeg);
                else if (saveFileDialog1.FilterIndex == 2) // png
                    pictureBox1.Image.Save(fileName, System.Drawing.Imaging.ImageFormat.Png);
                else if (saveFileDialog1.FilterIndex == 3) // bmp
                    pictureBox1.Image.Save(fileName, System.Drawing.Imaging.ImageFormat.Bmp);
            }
        }
    }
}
