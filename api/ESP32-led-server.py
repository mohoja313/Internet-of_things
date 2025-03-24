from flask import Flask, request
app = Flask(__name__)
import requests
import json
url = "http://10.31.65.87/setStatus"
payload_t = {
    "ledStatus":1
}
payload = {
    "ledStatus":0
}
headers = {
    "Content-Type": "application/json"
}

@app.route('/json_example', methods=['GET','POST'])
def handle_json():
    if request.method == 'POST':
      uname=request.form['uname']  
      passwrd=request.form['pass']  
      if uname=="on" and passwrd=="123":  
        
        json_payload_t = json.dumps(payload_t)
        response_t = requests.post(url, data=json_payload_t, headers=headers)
        if response_t.status_code == 200:
            # Request successful
            print("light turn on.")
            return ("on")
      if uname=="off" and passwrd=="123":  
        json_payload = json.dumps(payload)
        response = requests.post(url, data=json_payload, headers=headers)
        if response.status_code == 200:
            print("light turn off.") 
            return ("off")
      
    if request.method == 'GET':
        uname=request.args.get('uname')
        passwrd=request.args.get('pass')  
        if uname=="a" and passwrd=="b":
            return ("Welcome %s" %uname )  
if __name__ == '__main__':
    app.run(debug = True)

