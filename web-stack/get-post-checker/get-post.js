/********************************************************
Author:         Shawn Hillyer
Description:    CS290 Assignment "GET and Post Checker"
Date;           2/12/2016
Note:           I used the lectures and textbook as 
reference, I did not cite every similarity because there
are only so many ways to do these things :)
*********************************************************/

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
// Tell express our default rendering engine and extensions
app.engine('handlebars', handlebars.engine);
app.set('view engine', 'handlebars');

// Set port and public folder for static content
app.set('port', process.env.PORT || 3000); // defaults to 3000 if env.port not set
app.use(express.static(__dirname + '/public')); // tells express where to go for public static content like css, js, imgs, etc




/*******************
* ROUTES:          *
********************/

// If a GET request is received, grab the object and render the get.handlebars page
app.get('/', function(req,res){
    var payload = {};
    
    // Iterate over the req.query and push the key value pairs into our array
    var getRequest = [];
    for (var key in req.query) {
        getRequest.push( {'key': key, 'value': req.query[key] });
    }
    
    // Make a 'content' object and pass it to our render page with a kvPairs[] property
    payload.queryKvPairs = getRequest;
    payload.typeName = "GET";
    res.render('get-post', payload);
});

// If a POST request is received, parse the body header and the query or jsson and render the post.handlebars page
app.post('/', function(req, res){
    var payload = {};

    // Iterate over the req.body and push the key value pairs into our array
    var postRequest = [];
    for (var key in req.body) {
        postRequest.push( {'key': key, 'value': req.body[key] });
    }

    // Iterate over the req.query and push the key value pairs into our array
    var queryRequest = [];
    for (var key in req.query) {
        queryRequest.push( {'key': key, 'value': req.query[key] });
    }

    // Make a 'content' object and pass it to our render page with the two KvPairs[] properties
    payload.postKvPairs = postRequest;
    payload.queryKvPairs = queryRequest;
    payload.typeName = "POST";
    res.render('get-post', payload);
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