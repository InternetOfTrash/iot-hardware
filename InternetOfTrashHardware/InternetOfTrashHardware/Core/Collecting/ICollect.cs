using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace InternetOfTrashHardware.Core.Collecting
{
    interface ICollect : IDisposable
    {
        StreamReader GetOutputStream();
    }
}
    