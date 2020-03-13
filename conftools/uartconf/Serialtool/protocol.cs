using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

/*
 * 
typedef struct
{
    uint8_t head;
    uint16_t len;
    uint16_t inf
    uint8_t cmd;
    uint8_t * payload;
    uint8_t foot;
    uint8_t sum;
}LN_Protocol_t;
 * 
 * 
 */

namespace Serialtool
{
    class protocol
    {
        byte[] protocol_buf = new byte[100];
        UInt32 protocol_buflen = 0;


        //public byte[] protocol_buf = new byte[100];

        public enum LN_protocol_cmd_e
        {
            NORMAL_MODE = 0X00,

        };

        public void Protocol_Write_Inf(UInt16 inf)
        {
            protocol_buf[3] = (byte)(inf & 0x00ff);
            protocol_buf[4] = (byte)(inf >> 8);
        }

        public void Protocol_Write_Cmd(byte cmd)
        {
            protocol_buf[5] = cmd;
        }

        public void Protocol_Add_TLV(byte tag, byte len , byte[] value)
        {

        }

    }
}


