from flask import Flask, render_template, request

app = Flask(__name__)

# a global variable
SPORTS = [
    "Basketball",
    "Soccer", 
    "Ultimate Frisbee"
]

@app.route("/")
def index():
    return render_template("index.html", sports=SPORTS)

@app.route("/register", methods=["POST"])
def register(): #could be greet() but to be consistent
    # validate submission
    if not request.form.get("name") or request.form.get("sport") not in SPORTS:
        return render_template("failure.html")

    #confirm registration
    return render_template("success.html")