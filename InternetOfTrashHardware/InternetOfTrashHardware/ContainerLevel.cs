using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace InternetOfTrashHardware
{ 
    public class ContainerLevel
    {
        public int ID { get; set; }
        public int FillLevel { get; set; }

        public ContainerLevel(int id, int filllevel)
        {
            ID = id;
            FillLevel = filllevel;
        }

        public override string ToString()
        {
            return ("ID = " + ID + " and FillLevel = " + FillLevel);
        }
    }
}