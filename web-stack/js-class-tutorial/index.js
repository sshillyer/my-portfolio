/********************************************************
Author:         Shawn Hillyer
Description:    CS290 Assignment "How To Guide"
Date;           2/22/2016
*********************************************************/
"use strict";
var MAX_PAGE = 8; // Set to the highest page in guide
/*******************
* Setup middleware *
********************/

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


// Tell express our default rendering engine and extensions
app.engine('handlebars', handlebars.engine);
app.set('view engine', 'handlebars');

// Set port and public folder for static content
app.set('port', process.env.PORT || 3001); // defaults to 3000 if env.port not set
app.use(express.static(__dirname + '/public')); // tells express where to go for public static content like css, js, imgs, etc


/*******************
* ROUTES:          *
********************/

// Main index page
app.get('/', function(req,res){
    var context = {};
    var pages = [];
    var queryData = [];
    // Grab the page number from the request object if a page number was sent
    if (req.query != "undefined") {
        var getRequest = [];
        for (var key in req.query) {
            getRequest.push( req.query[key] );
        }
        console.log(getRequest);
        if (getRequest.length > 0 && getRequest[0] != 0) {
            var pageNum = getRequest[0];
            var pageTitle = "js-classes-" + Number(pageNum);
            var prevPage = Number(pageNum) - 1;
            var nextPage = Number(pageNum) + 1;
            context.prevPage = prevPage >= 0 ? prevPage : 0;
            context.nextPage = nextPage <= MAX_PAGE ? nextPage : 0;
            context.curPage = pageNum;
        }
        else {
            pageTitle = "js-classes-1";
            context.prevPage = 0;
            context.nextPage = 2;
            context.curPage = 1;
        }
    }
    
    res.render(pageTitle, context);
});


// If a POST request is received, parse the body header and the query or jsson and render the post.handlebars page
app.post('/', function(req, res){
    var context = {};
    res.render('index', context);
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