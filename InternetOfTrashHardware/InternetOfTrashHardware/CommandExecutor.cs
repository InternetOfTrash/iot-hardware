using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Diagnostics;

namespace InternetOfTrashHardware
{
    public class CommandExecutor
    {
        /// <summary>
        /// Executes a commando on the linux OS. 
        /// </summary>
        /// <param name="filename">Commando</param>
        /// <param name="arguments">Parameters</param>
        /// <returns>Returns a process which can be read with a StreamReader</returns>
        public static Process ExcecuteCommand(string filename, string arguments)
        {
            Process proc = new Process
            {
                StartInfo =
                {
                    FileName = filename,
                    Arguments = arguments,
                    UseShellExecute = false,
                    RedirectStandardOutput = true
                }
            };
            return proc;
        }
    }
}
