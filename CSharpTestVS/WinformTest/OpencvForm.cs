﻿using System;
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


        
    }
}
