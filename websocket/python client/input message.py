import asyncio
import websockets
n=0
while True:
    async def hello():
        uri = "ws://10.31.65.90:7890/Echo" # Replace with your websocket server URL
        async with websockets.connect(uri) as websocket:
            print("Connection established")
            m=input("enter your message:")
            await websocket.send(m)
            print("Message sent:",m)
            # Receive and print the response from the server
            response = await websocket.recv()
            if response != None:
                print("Received message:", response)
            else:
                print("no awnser")

    asyncio.run(hello())
