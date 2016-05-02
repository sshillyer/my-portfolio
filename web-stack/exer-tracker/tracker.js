/**************************************************************************************
 * Author: Shawn S Hillyer
 * Course: CS 290-400 Web Development
 * Date Completed: 02/29/2016
 * Assignment: "Database UI Interactions " - Assigned Week 9
 * 
**************************************************************************************/
"use strict";


/**************************************************************************************
Setup middleware
**************************************************************************************/

// Import express
var express = require('express');
var app = express();

// Import body-parser / setup (middleware for parsing POST content)
var bodyParser = require('body-parser');
app.use(bodyParser.urlencoded({ extended: false }));
app.use(bodyParser.json());

// Import and set up handlebars
var handlebars = require('express-handlebars').create({
    defaultLayout:'main',
    helpers: {
        // This helper allows us to use sections in templates
        section: function(name, options){
            if(!this._sections) this._sections = {};
            this._sections[name] = options.fn(this);
            return null;
        }
    }
});

// Import express-session and set the secret
var session = require('express-session');
app.use(session({secret:'IWillNeverTell'}));

// Set up MySql & connection pool.
// Code per: http://eecs.oregonstate.edu/ecampus-video/CS290/core-content/node-mysql/using-server-sql.html
var mysql = require('mysql');
var pool = mysql.createPool({
  host  : 'localhost',
  user  : 'student',
  password: 'default',
  database: 'student'
});

// Tell express our default rendering engine and extensions
app.engine('handlebars', handlebars.engine);
app.set('view engine', 'handlebars');

// Set port and public folder for static content
app.set('port', process.env.PORT || 3002); // defaults to 3002 if env.port not set
app.use(express.static(__dirname + '/public')); // tells express where to go for public static content like css, js, imgs, etc


/**************************************************************************************
ROUTES
**************************************************************************************/

// Main page route. Selects all rows from table and logs to console
// Client only sees page load - the contents are actually rendered by AJAX from tracker-ajax.js
app.get('/', function(req, res){
    var context = {};
    pool.query('SELECT * FROM workouts', function(err, rows, fields){
        if(err){
            next(err);
            return;
        }
        context.results = JSON.stringify(rows);
        res.render('home', context);
        console.log(context.results);
    });   
});

// Returns all of the data from the worksheets table as JSON string
app.get('/load-data', function(req, res){
  var allRows = {};
    pool.query('SELECT * FROM workouts', function(err, rows, fields){
        if(err){
            next(err);
            return;
        }
        allRows = JSON.stringify(rows);
        console.log(allRows);
        res.json(allRows);
    });  
});

// Render the edit page for a row passed in via querystring
app.get('/edit-by-id', function(req, res){
    var context = {};
    pool.query('SELECT * FROM workouts WHERE id=?', [req.query.id], function(err, rows, fields){
        if(err){
            next(err);
            return;
        }
        context.results = rows[0];
        var date = JSON.stringify(rows);
        // Hack to convert ugly mySql string back into simple datestring
        date = JSON.parse(date);
        date = date[0];
        date = date["date"];
        date = date.slice(0, 10);
        context.date = date;
        console.log(context.results);
        console.log(context.date);
        res.render('edit', context);
    });  
});

// Insert a new record - form will send the data and server will send back rows as JSON
app.get('/insert',function(req,res,next){
  var allRows = {};
  pool.query("INSERT INTO workouts (`name`, `reps`, `weight`, `date`, `lbs`) VALUES (?, ?, ?, ?, ?)", [req.query.name, req.query.reps, req.query.weight, req.query.date, req.query.lbs], function(err, result){
    if(err){
      next(err);
      return;
    }
    pool.query('SELECT * FROM workouts', function(err, rows, fields){
        if(err){
            next(err);
            return;
        }
        allRows = JSON.stringify(rows);
        console.log(allRows);
        res.json(allRows);
    });   
  });
});


// Delete a record with the id designated in query string
app.get('/delete', function(req, res, next) {
    var allRows = {};
    pool.query("DELETE FROM workouts WHERE id = ?", [req.query.id], function(err, result) {
        if(err){
            next(err);
            return;
        }
        pool.query('SELECT * FROM workouts', function(err, rows, fields){
            if(err){
                next(err);
                return;
            }
            allRows = JSON.stringify(rows);
            console.log(allRows);
            res.json(allRows);
        });   
    });
});

// SAFELY Update a record using querystring arguments and designed id
// Based on code pattern at http://eecs.oregonstate.edu/ecampus-video/CS290/core-content/node-mysql/using-server-sql.html
app.get('/edit-safe', function(req, res, next) {
    var allRows = {};
    // First select the row we plan to update
    pool.query("SELECT * FROM workouts WHERE id=?", [req.query.id], function(err, result){
        if(err){
            next(err);
            return;
        }
        // If a row with that id exists, then update any new values, keeping the original values if an argument is omitted.
        if (result.length == 1) {
            var curVals = result[0];
            pool.query("UPDATE workouts SET name=?, reps=?, weight=?, date=?, lbs=? WHERE id = ?", 
                       [req.query.name || curVals.name, req.query.reps || curVals.reps, req.query.weight || curVals.weight, req.query.date || curVals.date, req.query.lbs || curVals.lbs, req.query.id], 
            function(err, result) {
                if(err){
                    next(err);
                    return;
                }
                pool.query('SELECT * FROM workouts', function(err, rows, fields){
                    if(err){
                        next(err);
                        return;
                    }
                    allRows = JSON.stringify(rows);
                    console.log(allRows);
                    res.json(allRows);
                });   
            });
        }
    });
});


// RESET THE TABLE:
// Provided from assignmnet @ https://oregonstate.instructure.com/courses/1568412/assignments/6668343?module_item_id=16623348
app.get('/reset-table',function(req,res,next){
    var context = {};
    pool.query("DROP TABLE IF EXISTS workouts", function(err){ //replace your connection pool with the your variable containing the connection pool
        var createString = "CREATE TABLE workouts("+
            "id INT PRIMARY KEY AUTO_INCREMENT,"+
            "name VARCHAR(255) NOT NULL,"+
            "reps INT,"+
            "weight INT,"+
            "date DATE,"+
            "lbs BOOLEAN)";
        pool.query(createString, function(err){
          context.results = "Table reset";
          res.render('home',context);
        })
    });
});


// Error Pages 404 (Not found) & 500 (Error)
app.use(function(req, res, next){
    res.status(404);
    res.render('404');
});

app.use(function(err, req, res, next) {
    console.error(err.stack);
    res.status(500);
    res.render('500');
});


/******************
* Start Server    *
******************/

app.listen(app.get('port'), function(){
  console.log('Express started on http://52.26.146.27:' + 
              app.get('port') + 
              '; press Ctrl-C to terminate.' );
});