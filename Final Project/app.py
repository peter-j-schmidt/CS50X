import os

from flask import Flask, flash, jsonify, redirect, render_template, request, session, g
from flask_session import Session
from werkzeug.exceptions import default_esceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

import datetime
import sqlite3

# Configure the application
app = Flask(__name__)

db = sqlite3.connect('stocks.db')


@app.route("/")
# This will be where login_required should go.
def index():
