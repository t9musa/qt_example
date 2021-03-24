var express = require('express');
var path = require('path');
var cookieParser = require('cookie-parser');
var logger = require('morgan');

var personRouter = require('./routes/person');

var app = express();

const basicAuth = require('express-basic-auth');
app.use(basicAuth({users: { 'ATM123': 'pass123' }}))


app.use(logger('dev'));
app.use(express.json());
app.use(express.urlencoded({ extended: false }));
app.use(cookieParser());
app.use(express.static(path.join(__dirname, 'public')));

app.use('/person', personRouter);

module.exports = app;
