var express = require('express');
var passport = require('passport');
var Strategy = require('passport-http-bearer').Strategy;
var db = require('./db');
var bodyParser = require('body-parser');


// Configure the Bearer strategy for use by Passport.
//
// The Bearer strategy requires a `verify` function which receives the
// credentials (`token`) contained in the request.  The function must invoke
// `cb` with a user object, which will be set at `req.user` in route handlers
// after authentication.
passport.use(new Strategy(
  function(token, cb) {
    db.users.findByToken(token, function(err, user) {
      if (err) { return cb(err); }
      if (!user) { return cb(null, false); }
      return cb(null, user);
    });
  }));


// Create a new Express application.
var app = express();


app.use(bodyParser.json()); // for parsing application/json
app.use(bodyParser.urlencoded({ extended: true })); // for parsing application/x-www-form-urlencoded

// Configure Express application.
app.use(require('morgan')('combined'));

// curl -v -H "Authorization: Bearer 123456789" http://127.0.0.1:3000/
// curl -v http://127.0.0.1:3000/?access_token=123456789
app.get('/',
  passport.authenticate('bearer', { session: false }),
  function(req, res) {
    console.log(req.params)
    res.json({ username: req.user.username, email: req.user.emails[0].value });
  });

app.post('/',
    passport.authenticate('bearer', { session: false }),
    function(req, res) {
      console.log(req.body.rfid);
    //  res.json({ username: req.user.username, email: req.user.emails[0].value });
      res.sendStatus(200)
});



app.listen(3000);
