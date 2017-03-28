using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace InternetOfTrashHardware.Core.Collecting
{

    class CollectionProcess : ICollect
    {

        private string s;
        private MemoryStream _stream;

        public void Dispose()
        {
            _stream.Close();
        }

        public StreamReader GetOutputStream()
        {
            _stream = new MemoryStream();
            StreamWriter sw;
            sw = new StreamWriter(_stream);
            sw.Write(s);
            sw.Flush();
            _stream.Position = 0;
            var streamReader = new StreamReader(_stream);
            return streamReader;
        }
    }
    
}
