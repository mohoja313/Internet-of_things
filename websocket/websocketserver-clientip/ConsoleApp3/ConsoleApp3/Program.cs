using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using WebSocketSharp;
using WebSocketSharp.Server;


namespace ConsoleApp3
{

    public class Echo : WebSocketBehavior
    {
        protected override void OnMessage(MessageEventArgs e)
        {
            var clientIp = Context.UserEndPoint.Address.ToString();
            Console.WriteLine("Client IP: " + clientIp);
            Console.WriteLine("message recived from client"+e.Data);
            Send(e.Data);
        }
    }
    public class Echoall : WebSocketBehavior
    {
        protected override void OnMessage(MessageEventArgs e)
        {
            var clientIp = Context.UserEndPoint.Address.ToString();
            Console.WriteLine("Client IP: " + clientIp);
            Console.WriteLine("message recived from client" + e.Data);
            Sessions.Broadcast(e.Data);
        }
    }
    internal class Program
    {
        static void Main(string[] args)
        {
            WebSocketServer server = new WebSocketServer("ws://10.31.65.90:7890");
           server.AddWebSocketService<Echo>("/Echo");
            server.AddWebSocketService<Echoall>("/Echoall");
            server.Start();
            Console.WriteLine("server start on ws://10.31.65.90:7890/Echo");
            Console.WriteLine("server start on ws://10.31.65.90:7890/Echoall");
            //Console.WriteLine(server.Address.Address.ToString());
          
            Console.ReadKey();
            server.Stop();


        }
    }
}
