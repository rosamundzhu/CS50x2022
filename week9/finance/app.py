import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# which stocks the user owns, the numbers of shares owned, the current price of each stock,
# and the total value of each holding (i.e., shares times price).
# the user’s current cash balance along with a grand total (i.e., stocks’ total value plus cash).
@app.route("/")
@login_required
# only need to display information
# by default the method is GET
def index():
    """Show portfolio of stocks"""
    user_id = session["user_id"]

    # a list of dictionary
    stocks = db.execute("SELECT symbol, name, price, SUM(shares) AS totalshares FROM transactions WHERE user_id = ? GROUP BY symbol", user_id)
    # get rid of a dictionary
    cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]["cash"]

    total = cash

    for stock in stocks:
        total += stock["price"] + stock["totalshares"]

    return render_template("index.html", stocks=stocks, cash=cash, usd=usd, total=total)


"""
CREATE TABLE transactions (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    user_id INTEGER NOT NULL,
    name TEXT NOT NULL,
    shares INTEGER NOT NULL,
    price NUMERIC NOT NULL,
    type TEXT NOT NULL,
    symbol TEXT NOT NULL,
    time TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY(user_id) REFERENCES user(id)
);
"""
@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        # ask for symbol (valid) and # of shares (not negative)
        # check for valid input
        symbol = request.form.get("symbol").upper()
        item = lookup(symbol)
        if not symbol:
            return apology("Please enter a symbol")
        elif not item:
            return apology("Invalid symbol")

        try:
            shares = int(request.form.get("shares"))
        except:
            return apology("Shares must be an integer!")

        if shares <= 0:
            return apology("Shares must be a positive interger!")

        user_id = session["user_id"]
        # to get the first element (which is a dictionary) and the cash is the key
        cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]["cash"]

        # return the value of our name key
        item_name = item["name"]
        item_price = item["price"]
        total_price = item_price * shares

        if cash < total_price:
            return apology("cannot afford it")
        else:
            # update the user's table, subtract the cash
            # insert into the transaction table the information
            db.execute("UPDATE users SET cash = ? WHERE id = ?", cash - total_price, user_id)
            db.execute("INSERT INTO transactions (user_id, name, shares, price, type, symbol) VALUES (?, ?, ?, ?, ?, ?)", user_id, item_name, shares, item_price, 'buy', symbol)

        return redirect("/")

    # via GET
    else:
        return render_template("buy.html")

@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    # the value of the "user_id" key
    user_id = session["user_id"]

    # one row for each buy and sell
    transactions = db.execute("SELECT type, symbol, price, shares, time FROM transactions WHERE user_id = ?", user_id)
    return render_template("history.html", transactions=transactions, usd=usd)

@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username")

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password")

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        # ensure it is one row for this particular user
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password")

        # Remember which user has logged in
        # by storing his or her user_id, an INTEGER, in session
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id by simply clearing session
    session.clear()

    # Redirect user to login form
    # if a user tries to visit any of those routes, he or she will first be redirected to login so as to log in.
    return redirect("/")

# allows a user to register for an account via a form.

# require a user name and password
# Submit the user’s input via POST to /register.
# INSERT the new user into users, storing a hash of the user’s password by generate_password_hash
@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    # when form is submitted via POST, check for possible errors and insert the new user into users table
    if request.method == "POST":
        # is the name in html

        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        if not username:
            return apology("must provide username")

        # Ensure password was submitted
        elif not password:
            return apology("must provide password")

        elif not confirmation:
            return apology("must provide confirmation")

        elif confirmation != password:
            return apology("Passwords do not match!")

        # if username already exists
        hash = generate_password_hash(password)

        try:
            db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, hash)
            return redirect("/")
        except:
            return apology("username has already existed")

    # when requested via GET, display registration form
    else:
        return render_template("register.html")


# allows a user to look up a stock’s current price.
@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    # via POST, lookup the stock symbol by calling the lookup function and display
    if request.method == "POST":
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("Please enter a symbol")

        # lookup is defined in helpers.py
        item = lookup(symbol)
        # if unsuccessful, returns None
        if not item:
            return apology("Invalid symbol!")
        # usd is imported from helpers. function can also be passed in.
        return render_template("quoted.html", item=item, usd_function=usd)
        # via GET, display form to request a stock quote
    else:
        return render_template("quote.html")

@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    # ask for symbol (owns) and # of shares (not negative)
    # check for valid input
    user_id = session["user_id"]
    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = int(request.form.get("shares"))

        if shares <= 0:
            return apology("shares must be a positive number")

        item_price = lookup(symbol)["price"]
        item_name = lookup(symbol)["name"]

        shares_owned = db.execute("SELECT shares FROM transactions WHERE user_id = ? AND symbol = ? GROUP BY symbol", user_id, symbol)[0]["shares"]
        if shares > shares_owned:
            return apology("you do not have enough shares!")

        current_cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]["cash"]
        current_cash += shares * item_price

        db.execute("UPDATE users SET cash = ? WHERE id = ?", current_cash, user_id)
        # use minus shares to make sense using SUM() in SQL
        db.execute("INSERT INTO transactions (user_id, name, shares, price, type, symbol) VALUES (?, ?, ?, ?, ?, ?)", user_id, item_name, -shares, item_price, 'sell', symbol)
        return redirect("/")

    else:
        symbols = db.execute("SELECT DISTINCT symbol FROM transactions WHERE user_id = ?", user_id)
        return render_template("sell.html", symbols=symbols)


# reference to https://www.youtube.com/watch?v=D9_6WLj-JTA&list=PLsJNRspv63XRbsJizNi55DE6FAjx7yK-x&index=5
