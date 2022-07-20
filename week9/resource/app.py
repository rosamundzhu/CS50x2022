from flask import Flask, render_template, request

app = Flask(__name__)

@app.route("/")
def index():
    return render_template("index.html")

@app.route("/greet", methods=["Post"])
def greet():
    name = request.form.get("name", "world")
    return render_template("greet.html", name=name) #传递name
