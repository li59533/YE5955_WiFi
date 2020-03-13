using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Serialtool
{
    class makemessage
    {
        hal_serial serial_1;
        Form1 form_1;
        protocol LN_P;
        public makemessage(hal_serial serial, Form1 form)
        {
            LN_P = new protocol();
            serial_1 = serial;
            form_1 = form;
        }


        public void MakeMessage_Test()
        {
            byte test = 0;
            test =(byte) protocol.LN_protocol_cmd_e.NORMAL_MODE;
        }


    }
}
