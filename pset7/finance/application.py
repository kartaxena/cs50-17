from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session, url_for
from flask_session import Session
from passlib.apps import custom_app_context as pwd_context
from tempfile import gettempdir

from helpers import *

# configure application
app = Flask(__name__)

# ensure responses aren't cached
if app.config["DEBUG"]:
    @app.after_request
    def after_request(response):
        response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
        response.headers["Expires"] = 0
        response.headers["Pragma"] = "no-cache"
        return response

# custom filter
app.jinja_env.filters["usd"] = usd

# configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = gettempdir()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

@app.route("/")
@login_required
def index():
    
    if session["user_id"]:
        result = db.execute(
            "SELECT * FROM shares JOIN users ON users.cash WHERE user_id= :user_id AND id= :user_id AND shares > 0",
            user_id = session["user_id"])
        if not result:
            c = db.execute("SELECT cash FROM users WHERE id= :user_id", user_id = session["user_id"])
            return render_template("index.html", cash = usd(c[0]["cash"]), total_cash = usd(c[0]["cash"]))
        else:    
            new_res = []
            total_cash = 0
            #print(result)
            for res in result:
                quote = lookup(res["symbol"])
                
                temp_res_dict = dict(user_id=res['user_id'], symbol=res['symbol'], \
                                    name=quote["name"], shares=res['shares'], price=usd(quote["price"]), \
                                    total_price=usd(quote["price"] * res['shares']))
                
                total_cash = total_cash + quote["price"] * res['shares']
                new_res.append(temp_res_dict)
                #print(new_res)
            return render_template("index.html", result=new_res, cash=usd(res["cash"]), \
                                    total_cash=usd(total_cash), all_total=usd(total_cash + res["cash"]))
    else:
        return redirect(url_for("login"))

@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock."""
    if request.method == "POST":
        
        #перевіряємо чи передали символ і чи він є літерою
        if not request.form.get("symbol") or not request.form.get("symbol").isalpha:
            return apology("Missing symbol")
            
        #перевіряємо на біржі чи закріплене за введеним символом підприємство
        elif not lookup(request.form.get("symbol")):
            return apology("Your symbol \"{}\"".format(request.form.get("symbol")), "not in Stock")
            
        #перевіряємо чи ввів користувач кількість акцій, чи значення є числове і чи воно не менше за одиницю
        elif not request.form.get("share") or not request.form.get("share").isdigit() or int(request.form.get("share")) < 1:
            return apology("Missing share")
        else:
            
            #отримуємо повну інформацію про акції підприємство та ціну
            qoute = lookup(request.form.get("symbol"))
            cost = float(qoute["price"])
            
            result = db.execute("SELECT cash FROM users WHERE id = :id", id=session["user_id"])
            money = float(result[0]["cash"])
            #перевіряємо, ич достатньо у користувача грошей, щоб придбати певну кількість акцій
            if float(request.form.get("share")) * cost > money:
                return apology("You do not have so much money")
            else:
                
                shares_buy = int(request.form.get("share"))
                if not db.execute(
                    "INSERT INTO shares (user_id, symbol, shares) VALUES (:user_id, :symbol, :shares)", 
                    user_id=session["user_id"], symbol=qoute["symbol"], shares=shares_buy
                    ):
                        
                    issh = db.execute(
                        "SELECT shares FROM shares WHERE user_id= :user_id AND symbol= :symbol",
                        user_id = session["user_id"], symbol = qoute["symbol"]
                        )
                    db.execute(
                        "UPDATE shares SET shares= :shares WHERE symbol= :symbol AND user_id= :user_id",
                        shares = issh[0]["shares"] + shares_buy, symbol = qoute["symbol"], user_id = session["user_id"]
                        )
                db.execute(
                    "INSERT INTO history (user_id, symbol, shares, transactions, price) \
                    VALUES(:user_id, :symbol, :shares, :transactions, :price)",
                    user_id = session["user_id"], symbol = qoute["symbol"], \
                    shares = shares_buy, transactions = 'Buy', price = qoute["price"]
                    )
                db.execute(
                    "UPDATE users SET cash = :cash WHERE id = :id", 
                    cash = money - shares_buy*qoute["price"], id = session["user_id"]
                    )
            flash("Congratulations!!! ")
            flash("You bought")
            flash(shares_buy)
            flash("shares of")
            flash(qoute["name"])
            return redirect(url_for("index"))
       
       
    else:
        return render_template("buy.html")

@app.route("/history")
@login_required
def history():
    """Show history of transactions."""
    if session["user_id"]:
        result = db.execute("SELECT * FROM history WHERE user_id= :user_id ORDER BY date DESC", user_id = session["user_id"])
        return render_template("history.html", result=result)
        
    else:
        return render_template("login.html")

@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in."""

    # forget any user_id
    session.clear()

    # if user reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username")

        # ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password")

        # query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = :username", username=request.form.get("username")
            )

        # ensure username exists and password is correct
        if len(rows) != 1 or not pwd_context.verify(request.form.get("password"), rows[0]["hash"]):
            return apology("invalid username and/or password")

        # remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # redirect user to home page
        return redirect(url_for("index"))

    # else if user reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")

@app.route("/logout")
def logout():
    """Log user out."""

    # forget any user_id
    session.clear()

    # redirect user to login form
    return redirect(url_for("login"))

@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    
    if request.method == "POST":
        
        if not request.form.get("symbol"):
            return apology("Missing symbol")
        elif request.form.get("symbol").isalpha():
            #get quote
            s = request.form.get("symbol")
            quote = lookup(s)
            if not quote:
                return apology("Your symbol \"{}\"".format(s), "not in Stock")
            return render_template("quote.html", quote=quote)
        else:
            return apology("Invalid symbol")
    else:
        return render_template("quote.html")
        
    

@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user."""
     # if user reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username")
        elif not request.form.get("username").isalnum():
            return apology("must be only letters and numbers")

        # ensure password was submitted
        elif not request.form.get("password1"):
            return apology("must provide first password")
        elif not request.form.get("password2"):
            return apology("must provide second password")
        elif request.form.get("password1") != request.form.get("password2"):
            return apology("Your passwords does not match")
            
        #hash password
        hash = pwd_context.hash(request.form.get("password1"))
        
        # create new user in database
        result = db.execute(
            "INSERT INTO users (username, hash) VALUES (:username, :hash)", 
            username=request.form.get("username"), hash=hash
            )
            
        if not result:
            return apology("Insert to the database failed")
        
        session["user_id"] = result
        # redirect user to home page
        return redirect(url_for("index"))

    # else if user reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")
    #return apology("TODO")

@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock."""
    if request.method == "POST":
        
        if not request.form.get("symbol") or not request.form.get("symbol").isalpha:
            return apology("Missing symbol")
        elif not request.form.get("share") or not request.form.get("share").isdigit() or int(request.form.get("share")) < 1:
            return apology("Missing share")
        else:
            result = db.execute(
                "SELECT * FROM shares JOIN users ON users.cash WHERE user_id= :user_id AND id= :user_id AND symbol= :symbol",
                user_id = session["user_id"], symbol = request.form.get("symbol").upper()
                )
                
        if result and request.form.get("symbol").upper() in result[0]['symbol']:
                if result[0]['shares'] < int(request.form.get("share")):
                    return apology("You do not have so much shares")
                else:
                    new_shares = result[0]['shares'] - int(request.form.get("share"))
                    now_quote = lookup(request.form.get("symbol"))
                    add_cash = int(request.form.get("share")) * float(now_quote["price"])
                    db.execute(
                        "UPDATE shares SET shares= :shares WHERE user_id= :user_id AND symbol= :symbol",
                        shares = new_shares, user_id = session["user_id"], symbol = request.form.get("symbol").upper()
                        )
                    db.execute(
                        "UPDATE users SET cash= :cash WHERE id= :id", cash = add_cash + result[0]["cash"], id = session["user_id"]
                        )
                    db.execute(
                    "INSERT INTO history (user_id, symbol, shares, transactions, price) \
                    VALUES(:user_id, :symbol, :shares, :transactions, :price)",
                    user_id = session["user_id"], symbol = now_quote["symbol"], \
                    shares = int(request.form.get("share")), transactions = 'Sell', price = now_quote["price"]
                    )
                    flash("You sold")
                    flash(request.form.get("share"))
                    flash("shares of")
                    flash(now_quote["name"])
                    return redirect(url_for("index"))
        else:
            return apology("You do not have shares of the company")

        
    else:
        return render_template("sell.html")

@app.route("/change", methods=["GET", "POST"])
@login_required
def change():
    """Get stock quote."""
    
    if request.method == "POST":
        
        passwd = db.execute("SELECT hash FROM users WHERE id= :id", id = session["user_id"])    
        if not request.form.get("old_password"):
            return apology("must provide Old Password")
        else:
            passwd = db.execute("SELECT hash FROM users WHERE id= :id", id = session["user_id"])
            if not pwd_context.verify(request.form.get("old_password"), passwd[0]["hash"]):
                return apology("invalid Old password")
                
        # ensure password was submitted
        if not request.form.get("new_password1"):
            return apology("must provide first password")
        elif not request.form.get("new_password2"):
            return apology("must provide second password")
        elif request.form.get("new_password1") != request.form.get("new_password2"):
            return apology("Your passwords does not match")
        else:    
            #hash password
            hash = pwd_context.hash(request.form.get("new_password1"))
            # change password in database
            result = db.execute("UPDATE users SET hash= :hash WHERE id= :id", hash=hash, id = session["user_id"])
            if not result:
                return apology("Update to the database failed")
            else:
                # redirect user to home page
                flash("You password changed successfully")
                return redirect(url_for("index"))
    else:
        return render_template("change.html")

@app.route("/sell_all", methods=["GET", "POST"])
@login_required
def sell_all():
    
    if request.method == "POST":
        
        now_quote = lookup(request.form.get("symbol"))
        add_cash = int(request.form.get("shares")) * now_quote["price"]
        #new_shares = int(request.form.get("shares")) - int(request.form.get("share"))
        result = db.execute("SELECT cash FROM users WHERE id= :id", id = session["user_id"])
        db.execute(
            "UPDATE shares SET shares= :shares WHERE user_id= :user_id AND symbol= :symbol",
            shares = 0, user_id = session["user_id"], symbol = request.form.get("symbol").upper()
            )
        db.execute(
            "UPDATE users SET cash= :cash WHERE id= :id", 
            cash = result[0]["cash"] + add_cash, id = session["user_id"]
            )
        db.execute(
            "INSERT INTO history (user_id, symbol, shares, transactions, price) \
            VALUES(:user_id, :symbol, :shares, :transactions, :price)",
            user_id = session["user_id"], symbol = now_quote["symbol"], \
            shares = request.form.get("shares"), transactions = 'Sell', price = now_quote["price"]
            )
        flash("You sold all shares of")
        flash(now_quote["name"])
        return redirect(url_for("index"))
    else:
        return render_template("index.html")
    