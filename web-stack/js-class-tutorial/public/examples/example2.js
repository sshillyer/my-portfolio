// example2.js

"use strict";

var redSquare = {
  // _sides isn't technically private, we're just defining public get/set methods
  _sides: 4,
  get sides() {
    console.log("Reading sides");
    return this._sides;
  },
  set sides(numSides) {
    console.log("Setting sides to %s", numSides);
      this._sides = numSides;
  },
  _color: "red",
  get color() {
    console.log("Reading color");
    return this._color;
  },
  set color(newColor) {
    console.log("Setting color to %s", newColor);
    this._color = newColor;
  },
  
  identity: function() {
    console.log(this.sides + " sided " + this.color + " shape.");
  }
};

redSquare.identity();  // Reading sides --> Reading color --> 4 sided red shape
// Make our red square not so red or square. 
redSquare.sides = 5; // Setting sides to 5
redSquare.color = "blue"; // Setting color to blue
// Doesn't accomplish much except logging in this case!
redSquare.identity(); // Reading sides --> Reading color --> 5 sided blue shape.