import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd, checkInt

import datetime

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    user_id = session["user_id"]

    cash = db.execute("SELECT cash FROM users WHERE id = :user_id", user_id=user_id)[0]["cash"]

    total_value = cash

    stocks = db.execute("SELECT * FROM stocks_owned WHERE user_id = :user_id", user_id=user_id)

    #symbols = db.execute("SELECT stock_symbol FROM stocks_owned WHERE user_id = :user_id", user_id=user_id)

    stock_symbols = []

    stock_names = []

    total_shares = []

    current_prices = []

    current_totals = []



    for dictionary in stocks:

        stock_symbols.append(dictionary['stock_symbol'])
        stock_names.append(dictionary['stock_name'])
        total_shares.append(dictionary['total_shares'])

        info = lookup(dictionary['stock_symbol'])
        price = info['price']

        current_prices.append(usd(price))

        current_total = price * dictionary['total_shares']
        total_value += current_total
        current_totals.append(usd(current_total))


    stock_info = zip(stock_symbols, stock_names, total_shares, current_prices, current_totals)


    return render_template("index.html", stocks=stocks, cash=usd(cash), total_value=usd(total_value), stock_info = zip(stock_symbols, stock_names, total_shares, current_prices, current_totals))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    if request.method == "POST":

        # Ensure stock symbol is entered
        if not request.form.get("symbol"):
            return apology("Must enter a valid symbol", 403)

        # Ensure number of shares entered
        elif not request.form.get("shares"):
            return apology("Must enter number of shares desired", 403)

        shares = request.form.get("shares")

        if checkInt(shares) == False:
            return apology("Must enter a positive integer", 403)

        else:

            #
            shares = int(shares)

            if shares <= 0:
                return apology("Must enter a positive integer")

            else:
                stock_symbol = request.form.get("symbol")

                info = lookup(stock_symbol)

                if info == None:
                    return apology("Not a valid symbol", 403)

                else:
                    purchase_price = float(info['price']) * shares

                    user_id = session["user_id"]

                    rows_users = db.execute("SELECT * FROM users WHERE id = :user_id", user_id=user_id)

                    username = rows_users[0]['username']

                    cash_available = rows_users[0]['cash']

                    stock_name = info['name']

                    if cash_available >= purchase_price:

                        timestamp = datetime.datetime.now()

                        db.execute("INSERT INTO transactions (user_id, stock_symbol, shares, price, stock_name, timestamp) VALUES (:user_id, :stock_symbol, :shares, :price, :stock_name, :timestamp)", user_id=user_id, stock_symbol=stock_symbol, shares=shares, price=info['price'], stock_name=stock_name, timestamp=timestamp)

                        rows_stocks_owned = db.execute("SELECT * FROM stocks_owned WHERE user_id = :user_id AND stock_symbol = :stock_symbol", user_id=user_id, stock_symbol=stock_symbol)

                        if len(rows_stocks_owned) != 1:
                            db.execute("INSERT INTO stocks_owned (user_id, stock_symbol, stock_name, total_shares) VALUES (:user_id, :stock_symbol, :stock_name, :total_shares)", user_id=user_id, stock_symbol=stock_symbol, stock_name=stock_name, total_shares=shares)

                        else:
                            old_shares = db.execute("SELECT total_shares FROM stocks_owned WHERE user_id = :user_id AND stock_symbol = :stock_symbol", user_id=user_id, stock_symbol=stock_symbol)[0]['total_shares']
                            new_shares_total = shares + old_shares
                            db.execute("UPDATE stocks_owned SET total_shares = :new_shares_total WHERE user_id = :user_id AND stock_symbol = :stock_symbol", new_shares_total=new_shares_total, user_id=user_id, stock_symbol=stock_symbol)

                        remaining_cash = cash_available - purchase_price
                        db.execute("UPDATE users SET cash = :remaining_cash WHERE id = :user_id", remaining_cash=remaining_cash, user_id=user_id)

                        return redirect("/")

                    else:
                        return apology("Sorry, you do not have enough funds to make this purchase.", 403)

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    user_id = session["user_id"]

    stocks = db.execute("SELECT * FROM transactions WHERE user_id = :user_id", user_id=user_id)

    return render_template("history.html", stocks=stocks)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    if request.method == "POST":
        symbol = request.form.get("symbol")
        info = lookup(symbol)

        if info == None:
            return apology("Symbol not valid", 403)

        else:
            name = info['name']
            symbol = info['symbol']
            price = usd(info['price'])


            return render_template("quoted.html", name=name, symbol=symbol, price=price)


    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

     # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Ensure password was confirmed
        elif not request.form.get("confirmation"):
            return apology("must confirm password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Check if password is already taken
        if len(rows) == 1:
            return apology("username already taken", 403)

        # Add username and password if username not taken
        elif len(rows) != 1:
            username = request.form.get("username")
            password = request.form.get("password")
            pass_hash = generate_password_hash(password)
            db.execute("INSERT INTO users (username, hash) VALUES (:username, :pass_hash)", username=username, pass_hash=pass_hash)

        # Redirect user to login form
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    user_id = session["user_id"]

    if request.method == "POST":

        # Ensure stock symbol is entered
        if not request.form.get("symbol"):
            return apology("Must enter a valid symbol", 403)

        # Ensure number of shares entered
        elif not request.form.get("shares"):
            return apology("Must enter number of shares desired", 403)

        # Ensure correct number of shares entered
        else:

            input_shares = request.form.get("shares")

            # Ensure an integer is entered
            if checkInt(input_shares) == False:
                return apology("Must enter a positive integer", 403)

            else:

                input_shares = int(input_shares)

                symbol = request.form.get("symbol").lower()

                shares = db.execute("SELECT total_shares FROM stocks_owned WHERE stock_symbol = :symbol", symbol=symbol)[0]['total_shares']

                if (input_shares <= 0):
                    return apology("Must select 1 or more shares to sell", 403)

                elif (input_shares > shares):
                    return apology("Not enough shares in your account", 403)

                elif (input_shares < shares):

                    cash = db.execute("SELECT cash FROM users WHERE id = :user_id", user_id=user_id)[0]['cash']

                    new_total_shares = shares - input_shares

                    info = lookup(symbol)

                    stock_name = info['name']

                    price = info['price']

                    sale_price = input_shares * price

                    new_cash = cash + sale_price

                    timestamp = datetime.datetime.now()

                    db.execute("UPDATE stocks_owned SET total_shares = :new_total_shares WHERE stock_symbol = :symbol", new_total_shares=new_total_shares, symbol=symbol)

                    db.execute("INSERT INTO transactions (user_id, stock_symbol, shares, price, stock_name, timestamp) VALUES (:user_id, :stock_symbol, :shares, :price, :stock_name, :timestamp)", user_id=user_id, stock_symbol=symbol, shares=-(input_shares), price=price, stock_name=stock_name, timestamp=timestamp)

                    db.execute("UPDATE users SET cash = :new_cash WHERE id = :user_id", new_cash=new_cash, user_id=user_id)

                    return redirect("/")

                elif (input_shares == shares):

                    cash = db.execute("SELECT cash FROM users WHERE id = :user_id", user_id=user_id)[0]['cash']

                    info = lookup(symbol)

                    stock_name = info['name']

                    price = info['price']

                    sale_price = input_shares * price

                    new_cash = cash + sale_price

                    timestamp = datetime.datetime.now()

                    db.execute("DELETE FROM stocks_owned WHERE stock_symbol = :symbol", symbol=symbol)

                    db.execute("INSERT INTO transactions (user_id, stock_symbol, shares, price, stock_name, timestamp) VALUES (:user_id, :stock_symbol, :shares, :price, :stock_name, :timestamp)", user_id=user_id, stock_symbol=symbol, shares=-(input_shares), price=price, stock_name=stock_name, timestamp=timestamp)

                    db.execute("UPDATE users SET cash = :new_cash WHERE id = :user_id", new_cash=new_cash, user_id=user_id)

                    return redirect("/")


    else:

        # Get list of stock symbols
        stocks = db.execute("SELECT stock_symbol FROM stocks_owned WHERE user_id = :user_id", user_id=user_id)

        return render_template("sell.html", stocks=stocks)


@app.route("/password", methods=["GET", "POST"])
def retrieve_password():
    """Get a user's forgotten password"""

    if request.method == "POST":

        # Ensure a password is entered
        if not request.form.get("username"):
            return apology("Must enter a username", 403)

        if not request.form.get("old_password"):
            return apology("Must enter old password", 403)

        if not request.form.get("new_password"):
            return apology("Must enter a new password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username in system and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("old_password")):
            return apology("invalid username and/or password", 403)

        # if username and password are valid
        elif len(rows) == 1:

            old_password = request.form.get("old_password")

            new_password = request.form.get("new_password")

            if old_password == new_password:
                return apology("New password must be different from current password", 403)

            else:
                password = request.form.get("new_password")
                username = request.form.get("username")
                pass_hash = generate_password_hash(password)
                db.execute("UPDATE users SET hash = :pass_hash WHERE username = :username", pass_hash=pass_hash, username=username)

                return redirect("/")

    else:
        return render_template("password.html")


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
