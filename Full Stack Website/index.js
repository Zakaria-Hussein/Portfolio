// include the express modules
const express = require("express");
const app = express();
const bodyParser = require('body-parser');
const session = require('express-session');
const mysql = require("mysql");
const bcrypt = require('bcrypt');

// apply the body-parser middleware to all incoming requests
app.use(bodyParser.urlencoded({ extended: true }));
app.use(bodyParser.json());

// use express-session
app.use(session({
  secret: "csci4131secretkey",
  saveUninitialized: true,
  resave: false
}));

// server listens on port 9007 for incoming connections
app.listen(9007, () => console.log('Listening on port 9007!'));

// function to return the welcome page
app.get('/', (req, res) => {
  console.log("In Welcome");
  res.send(`
    <html>
      <head><title>Welcome</title></head>
      <body>
        <h1>Welcome Page</h1>
        <p>Welcome to our website!</p>
      </body>
    </html>
  `);
});

// handle login page
app.get('/login', (req, res) => {
  console.log("enter login");
  if (req.session.loggedIn) {
    // Redirect to the Schedule page if the user is logged in
    console.log("already logged in");
    res.redirect('/schedule');
  } else {
    // Otherwise, display the login page
    res.send(`
      <html>
        <head><title>Login</title></head>
        <body>
          <h1>Login Page</h1>
          <form action="/logincheck" method="GET">
            <input type="text" name="username" placeholder="Username">
            <input type="password" name="password" placeholder="Password">
            <button type="submit">Login</button>
          </form>
        </body>
      </html>
    `);
  }
});

// handle logout
app.get('/logout', (req, res) => {
  console.log("Logging out");
  // Destroy the session
  req.session.destroy(function(err) {
    if (err) {
      console.error("Error destroying session:", err);
    } else {
      console.log("Session destroyed successfully");
      // Redirect to the login page
      res.redirect('/login');
    }
  });
});

// handle login check
app.get('/logincheck', (req, res) => {
  var username = req.query.username;
  var password = req.query.password;
  console.log("in post username: " + username + " password: " + password);

  // Create Connection
  const connection = mysql.createConnection({
    host: "schedule-db.cdkq4kcmus2l.us-east-1.rds.amazonaws.com",
    user: "schedule-db",
    password: "Schedule20!",
    database: "schedule-db",
    port: 3306
  });

  connection.connect(function(err) {
    if (err) throw err;
    console.log("Connected to MySQL database!");

    // Query for existing username
    var query = "SELECT * FROM tbl_accounts WHERE acc_login = ?";
    connection.query(query, [username], function(err, results) {
      if (err) throw err;

      if (results.length > 0) {
        var user = results[0];
        console.log("comparing");

        // Compare passwords if username exists
        if (bcrypt.compareSync(password, user.acc_password)) {
          // Password correct
          req.session.loggedIn = true;
          res.json({ status: 'success' });
        } else {
          // Password incorrect
          res.status(401).send('Invalid username or password');
        }
      } else {
        // Username doesn't exist
        res.status(401).send('Invalid username or password');
      }

      connection.end();
    });
  });
});

// handle schedule page
app.get('/schedule', (req, res) => {
  console.log("schedule endpoint");
  if (req.session.loggedIn) {
    // Redirect to the Schedule page if the user is logged in
    res.send(`
      <html>
        <head><title>Schedule</title></head>
        <body>
          <h1>Schedule Page</h1>
          <p>Welcome to your schedule!</p>
        </body>
      </html>
    `);
  } else {
    // Otherwise, redirect to login
    res.redirect('/login');
  }
});

// handle 404 errors
app.get('*', (req, res) => {
  res.status(404).send('Page not found');
});
