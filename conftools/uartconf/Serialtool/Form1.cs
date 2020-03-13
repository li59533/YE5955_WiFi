using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace Serialtool
{
    public partial class Form1 : Form
    {
        hal_serial serial_1; 


        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            serial_1 = new hal_serial(this);

            foreach (string s in SerialPort.GetPortNames())
            {
                Console.WriteLine("   {0}", s);
                cbx_comx.Items.Add(s);
            }
            cbx_comx.SelectedIndex = 0;

            cbx_workmode.Items.Add("正常模式");
            cbx_workmode.Items.Add("低功耗模式");
            cbx_workmode.Items.Add("测试模式");
            cbx_workmode.Items.Add("————");
            cbx_workmode.SelectedIndex = 3;

            if (serial_1.current_status == true)
            {
                btn_serial_sw.Text = "Close";
            }
            else
            {
                btn_serial_sw.Text = "Open";
            }
        }


        public void Form_RevData(Byte[] buf , UInt16 len)
        {
            for (int i = 0; i < buf.Length; i++)
            {
                tbx_revdata.Text += buf[i].ToString("X2") + " ";
            }
            tbx_revdata.Text += "\r\n";
        }

        private void btn_serial_sw_Click(object sender, EventArgs e)
        {
            string portname;
            int baudrate;
            Parity parity;
            UInt16 databits;
            StopBits stopbits;



            if (serial_1.current_status == true)
            {
                serial_1.Serial_Close();
                btn_serial_sw.Text = "Close";
            }
            else
            {
                portname = cbx_comx.SelectedItem.ToString();
                baudrate = 115200;
                parity = (Parity)Enum.Parse(typeof(Parity), "None", true);
                databits = 8;
                stopbits = (StopBits)Enum.Parse(typeof(StopBits), "1", true);

                serial_1.Serial_Open(portname, baudrate , parity, databits , stopbits);
                btn_serial_sw.Text = "Open";
            }
        }

        private void btn_send_Click(object sender, EventArgs e)
        {
            byte[] temp = Encoding.ASCII.GetBytes(tbx_senddata.Text.Trim());

            serial_1.Serial_Send(temp , (UInt16)temp.Length);
        }
    }
}
