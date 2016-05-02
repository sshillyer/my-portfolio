/*
Author: Shawn S Hillyer
Date: 02-06-2016
Course: CS290-400
Assignment: Week6

Note: Using the Bootstrap basic template for the HTML framework.
Source: http://getbootstrap.com/getting-started/#template
All javascript I wrote is in weather-app.js for this assignment
I did not use JQUERY or anything other than pure Javascript
*/



"use strict";

let apiKey = "fa7d80c48643dfadde2cced1b1be6ca1";
let data = {};

/*  
 *  Bind the various buttons on the page to specific events.
 */
function bindButtons() {
    // Bind reload() to the reset the page button
    document.getElementById("reset-page-btn").addEventListener('click', function(event){
        event.preventDefault();
        location.reload();
    });
    
    // Bind the submit button for zip form with specific logic
    document.getElementById('zip-submit').addEventListener('click', function(event){
        event.preventDefault(); // Stops submit button from reloading page
        let queryString = document.getElementById("zip-code").value + ",us";
        
        // Send the GET request with the zip code
        queryServer(queryString);
    })
    
    // Bind the submit button for city/state form with specific logic
    document.getElementById('city-state-submit').addEventListener('click', function(event){
        event.preventDefault(); // Stops submit button from reloading page
        let queryString = document.getElementById("city-name").value + "," + document.getElementById("state-code").value;
        
        // Send the GET request with the zip code
        queryServer(queryString);
    })      
}


/*  
 *  query the openweathermap.org server using the qstring passed (which is appended to other
 *  pieces not input by users)
 */
function queryServer(qstring) {
    let req = new XMLHttpRequest();

    // Build the first part of the query string
    let queryString = "q=" + qstring + "&appid=" + apiKey + "&units=imperial";

    // Send the GET request with the zip code
    req.open("GET", "http://api.openweathermap.org/data/2.5/weather?" + queryString, true);
    
    req.addEventListener('load', function(){
        data = JSON.parse(req.responseText);
        
        // Make sure we got a valid code in the response object before trying to update page
        if(req.status >= 200 && req.status < 400) {
            hideErrorMessage();
            console.log(data); // For debug purposes
            displayWeatherInfo(data);
        
        // Display an error message and clear the form input if failure
        } else {
            if (data.cod == "404") {
                displayErrorMessage("The server did not find any data for that entry");
            } else {
                displayErrorMessage("Some unknown error occured.");
            }
            document.forms["zip-form"].reset();
            document.forms["city-state-form"].reset();
        }
    });
    
    req.send(null);  
}


/*  
 * Displays the results-panel div and updates its content
 */
function displayWeatherInfo(info) {
    console.log(data.name);
    let resultsPanel = document.getElementById("results-panel");
    resultsPanel.removeAttribute("hidden");
    
    document.getElementById("gen-description").textContent = data.weather[0].description;
    document.getElementById("city").textContent = data.name;
    document.getElementById("current-temp").textContent = data.main.temp;
    document.getElementById("humidity").textContent = data.main.humidity + "%";
    document.getElementById("wind-speed").textContent = data.wind.speed + " miles per hour";
    document.getElementById("city-name").textContent = data.name;
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
 *  Hides teh results-panel div
 */
function hideWeatherInfo() {
    document.getElementById("results-panel").setAttribute("hidden", "");
}


// I'm using the simple design pattern at http://eecs.oregonstate.edu/ecampus-video/CS290/core-content/ajax-forms/js-forms.html to add the event listener once DOm is loaded and bind the buttons, etc.
document.addEventListener('DOMContentLoaded', bindButtons);


// data.weather[0].description  retreives a short description
// data.coord.lon  data.coord.lat   --> longitude and latitude
// data.wind.speed
// data.name -- gives county