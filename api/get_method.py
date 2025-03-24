from flask import Flask, render_template

app = Flask(__name__)

@app.route('/example', methods=['GET'])
def example():
    #return 'This is a GET request'
    return render_template('ir.html')
    


if __name__ == '__main__':
    app.run(host='0.0.0.0', port=2000)
