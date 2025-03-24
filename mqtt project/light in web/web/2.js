
// Create a client instance
var client = new Paho.MQTT.Client("192.168.1.105", Number(5050), "clientId");

// Set callback handlers for connection lost and message arrival
client.onConnectionLost = onConnectionLost;
client.onMessageArrived = onMessageArrived;

// Connect to MQTT broker
client.connect({ onSuccess: onConnect });

// Called when the client connects successfully
function onConnect() {
    console.log("Connected to MQTT broker");

    // Subscribe to a topic
    client.subscribe("test/topic");
}

// Called when the client loses the connection
function onConnectionLost(response) {
    if (response.errorCode !== 0) {
        console.log("Connection lost: " + response.errorMessage);
    }
}

// Called when a message arrives
function onMessageArrived(message) {
    console.log("Message received: " + message.payloadString);

    // Show different images based on the received message
    if (message.payloadString === "0") {
        document.getElementById("image").src = "lamp.png";
    } else if (message.payloadString === "1") {
        document.getElementById("image").src = "lamp2.png";
    }
}
