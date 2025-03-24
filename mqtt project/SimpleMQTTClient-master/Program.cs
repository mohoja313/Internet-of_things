using MQTTnet;
using MQTTnet.Client.Connecting;
using MQTTnet.Client.Disconnecting;
using MQTTnet.Client.Options;
using MQTTnet.Extensions.ManagedClient;
using System.Text.Json;


// Create the client object
IManagedMqttClient _mqttClient = new MqttFactory().CreateManagedMqttClient();

// Create client options object
MqttClientOptionsBuilder builder = new MqttClientOptionsBuilder()
                                        .WithClientId("behroozbc")
                                        .WithTcpServer("localhost");
ManagedMqttClientOptions options = new ManagedMqttClientOptionsBuilder()
                        .WithAutoReconnectDelay(TimeSpan.FromSeconds(60))
                        .WithClientOptions(builder.Build())
                        .Build();



// Set up handlers
_mqttClient.ConnectedHandler = new MqttClientConnectedHandlerDelegate((e) => Console.WriteLine("Connected"));
_mqttClient.DisconnectedHandler = new MqttClientDisconnectedHandlerDelegate((e) => Console.WriteLine("Disconnected"));
_mqttClient.ConnectingFailedHandler = new ConnectingFailedHandlerDelegate((e) => Console.WriteLine("Connection failed check network or broker!"));

// Connect to broker
await _mqttClient.StartAsync(options);

// Send a new message to the broker every second
while (true)
{
    string json = JsonSerializer.Serialize(new { message = "Hi Mqtt", sent = DateTime.UtcNow });
    await _mqttClient.PublishAsync("behroozbc.ir/topic/json", json);

    await Task.Delay(TimeSpan.FromSeconds(1));
}