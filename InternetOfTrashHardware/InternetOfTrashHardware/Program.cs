using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Timers;
using InternetOfTrashHardware.Core;
using RestSharp;
using Timer = System.Timers.Timer;
using System.Configuration;
using System.Net;

namespace InternetOfTrashHardware
{
    class Program
    {   

        static void Main(string[] args)
        {
            var app = new Client();
            app.StartApp().Wait();
            Console.ReadLine();
        }
    }
    public static class MyRequestExtensions
    {
        public static void AddApiKey(this RestRequest request)
        {
            request.AddHeader("API_KEY", ConfigurationManager.AppSettings["Api_key"]);
        }

    }

    internal class Client
    {
        ISense sensor = new VirtualSensor(2,0);
        ISense sensor1 = new VirtualSensor(1,0);
        private readonly RestClient _client = new RestClient("http://145.93.133.154:11001/");
        public readonly CancellationTokenSource TokenSource = new CancellationTokenSource();
        private int _counter = 3;

        public async Task StartApp()
        {
            var token = TokenSource.Token;  
            var t = Task.Factory.StartNew(Poll, token);
            Console.ReadLine();
            TokenSource.Cancel();
            await t;
        }

        private void Poll()
        {
            Timer t = new Timer(5000);
            t.Elapsed += CollectionLowEvent;
            t.Start();
            Timer t2 = new Timer(2500);
            t2.Elapsed += CollectionHighEvent;
            t2.Start();
        }

        private void CollectionLowEvent(object sender, ElapsedEventArgs e)
        {
            
            if (TokenSource.IsCancellationRequested) return;
            if (PostInfo(sensor.collectData()))
            {
                Console.WriteLine("Post succesfull");
            }
        }
        private void CollectionHighEvent(object sender, ElapsedEventArgs e)
        {

            if (TokenSource.IsCancellationRequested) return;
            if (PostInfo(sensor1.collectData()))
            {
                Console.WriteLine("Post succesfull");
            }
        }

        private bool PostInfo(ContainerLevel cl)
        {
            var req = new RestRequest("containers/filllevel")
            {

                Method = Method.POST,
                RequestFormat = DataFormat.Json,
                Timeout = 2000
            };
            req.AddBody(cl);
            req.AddApiKey();
            var resp = _client.Execute(req);
            Console.WriteLine("The response of the post is : "+resp.StatusCode +"With values {0}",cl);
            if (resp.StatusCode != HttpStatusCode.OK)
            {
                return false;
            }
            return true;
        }
    }
}


