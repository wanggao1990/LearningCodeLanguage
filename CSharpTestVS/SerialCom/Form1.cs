using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WindowsFormsApplication1
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();

            Init();
        }


        private void Init()
        {

            ComboBox_baud.SelectedItem    = "19200";
            ComboBox_databit.SelectedItem = "8";
            ComboBox_stopBit.SelectedItem = "One";
            ComboBox_parity.SelectedItem  = "None";


            string[] portNames = SerialPort.GetPortNames();
            if (portNames.Length == 0)
                return;

            Array.Sort<string>(portNames);
            foreach (string name in portNames)
                ComboBox_ports.Items.Add(name);

            ComboBox_ports.SelectedIndex = 0;



            serialPort1.ReadBufferSize = 2048;
            serialPort1.ReadTimeout = 500;
        }


        private void button1_Click(object sender, EventArgs e)
        {
            if (!serialPort1.IsOpen)
            {
                if (ComboBox_ports.SelectedIndex < 0)
                {
                    MessageBox.Show("未选中com口");
                    return;
                }

                serialPort1.PortName = ComboBox_ports.Text;

                button1.Text = "关闭串口";
                button1.FlatStyle = FlatStyle.Flat;

                serialPort1.Open();
            }
            else
            {
                button1.Text = "打开串口";
                button1.FlatStyle = FlatStyle.Standard;

                serialPort1.Close();
            }
        }
        private void ComboBox_baud_SelectedIndexChanged(object sender, EventArgs e)
        {
            serialPort1.BaudRate = System.Convert.ToInt32(ComboBox_baud.Text);
        }

        private void ComboBox_databit_SelectedIndexChanged(object sender, EventArgs e)
        {
            serialPort1.DataBits = System.Convert.ToInt32(ComboBox_databit.Text);
        }

        private void ComboBox_stopBit_SelectedIndexChanged(object sender, EventArgs e)
        {
            if      (ComboBox_stopBit.Text == "One")          serialPort1.StopBits = StopBits.One;
            else if (ComboBox_stopBit.Text == "Two")          serialPort1.StopBits = StopBits.Two;
            else if (ComboBox_stopBit.Text == "OnePointFive") serialPort1.StopBits = StopBits.OnePointFive;
        }

        private void ComboBox_parity_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (ComboBox_parity.Text == "None")      serialPort1.Parity = Parity.None;
            else if (ComboBox_parity.Text == "Odd")  serialPort1.Parity = Parity.Odd;
            else if (ComboBox_parity.Text == "Even") serialPort1.Parity = Parity.Even;
        }


        private void serialPort1_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            if (e.EventType == SerialData.Eof)
                return;

            byte[] dat = new byte[serialPort1.ReadBufferSize];
            serialPort1.Read(dat, 0, serialPort1.ReadBufferSize);

            // System.Diagnostics.Debug.WriteLine(System.Text.Encoding.Default.GetString(dat));
            recvBox.Text += System.Text.Encoding.Default.GetString(dat) + "\n";
           
        }

        private void button2_Click(object sender, EventArgs e)
        {
            if (serialPort1.IsOpen)
            {
                serialPort1.Write(sendBox.Text);
            }
        }

        private void button3_Click(object sender, EventArgs e)
        {
            recvBox.Clear();
        }
    }
}
