import websocket

ws = websocket.WebSocket()

ws.connect("ws://10.31.65.90:7890/Echo")

ws.send("Hello, Server")


print(ws.recv())

ws.close()