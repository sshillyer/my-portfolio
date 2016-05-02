/*
Author: Shawn S Hillyer
Date: 02-06-2016
Course: CS290-400
Assignment: Week6

Note: Using the Bootstrap basic template for the HTML framework.
Source: http://getbootstrap.com/getting-started/#template
All javascript I wrote is in httpbin-app.js for this assignment.
I did not use JQUERY or anything other than pure Javascript
*/

"use strict";

/*  
 *  Bind the various buttons on the page to specific events.
 */
function bindButtons() {
    // Bind reload() to the reset the page button
    document.getElementById("reset-page-btn").addEventListener('click', function(event){
        event.preventDefault();
        location.reload();
    });
    
    // Bind the submit button for json-form with specific logic
    document.getElementById('json-form-submit').addEventListener('click', function(event){
        event.preventDefault(); // Stops submit button from reloading page
        
        // Get the input from the forms and build an object form the key/value pairs
        let jsonObjectKeys = buildArrayFromForm("key", 3);
        let jsonObjectValues = buildArrayFromForm("value", 3);
        let jsonObject = {};
        
        // Iterate over each of the keys and add the corresponding value
        for (let i = 0; i < jsonObjectKeys.length; i++) {
            jsonObject[String(jsonObjectKeys[i])] = jsonObjectValues[i];
        }
        
        // Send the GET request with the zip code
        queryServer(jsonObject);
    }) 
}

/*  
 *  Builds an array of values from from fiels with the label format:
 *  label-i-input
 *  Where i is a number from 1 to qty.
 *  The form input field must have an id that matches this constructed label
 */
function buildArrayFromForm(label, qty) {
    let keys = new Array();
    for (let i = 1; i <= qty; i++) {
        keys.push(document.getElementById(label + i + "-input").value);
    }
    return keys;
}


/*  
 *  query the openweathermap.org server using the qstring passed (which is appended to other
 *  pieces not input by users)
 */
function queryServer(obj) {
    let req = new XMLHttpRequest();
    
    // Send the GET request with the zip code
    req.open("POST", "http://httpbin.org/post", true);
    req.setRequestHeader('Content-type', 'application/json');
    
    req.addEventListener('load', function(){
        let response = JSON.parse(req.responseText);
        
        // Make sure we got a valid code in the response object before trying to update page
        if(req.status >= 200 && req.status < 400) {
            hideErrorMessage();
            console.log(response); // For debug purposes
            displayJSONResponse(response);
        
        // Display an error message and clear the form input if failure
        } else {
            if (response.cod == "404") {
                displayErrorMessage("The server did not send a response for that entry");
            } else {
                displayErrorMessage("Some unknown error occured.");
            }
            document.forms["json-form"].reset();
        }
    });
    
    req.send(JSON.stringify(obj));  
}


/*  
 * Displays the results-panel div and updates its content
 */
function displayJSONResponse(response) {
    console.log(response.name);
    let resultsPanel = document.getElementById("results-panel");
    resultsPanel.removeAttribute("hidden");
    
    // Print the object to the page, first as a literal string, then broken down again
    document.getElementById("json-string-response").textContent = response.data;
    let obj = JSON.parse(response.data);
    let i = 1;
    for (let property in obj) {
        document.getElementById("key" + i + "-response").textContent = property;
        document.getElementById("value" + i + "-response").textContent = obj[property];
        i++;
    }    
}


/*  
 *  Shows the error panel div and sets the content to msg
 */
function displayErrorMessage(msg) {
    hideWeatherInfo();
    document.getElementById("error-panel").removeAttribute("hidden");
    document.getElementById("error-message").textContent = msg;
}


/*  
 *  Hides the error-panel div
 */
function hideErrorMessage() {
    document.getElementById("error-panel").setAttribute("hidden", "");
}


/*  
 *  Hides the results-panel div
 */
function hideWeatherInfo() {
    document.getElementById("results-panel").setAttribute("hidden", "");
}


// I'm using the simple design pattern at http://eecs.oregonstate.edu/ecampus-video/CS290/core-content/ajax-forms/js-forms.html to add the event listener once DOm is loaded and bind the buttons, etc.
document.addEventListener('DOMContentLoaded', bindButtons);
