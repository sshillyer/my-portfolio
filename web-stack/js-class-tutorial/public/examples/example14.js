"use strict";

function Creature(name, str) {
  var strength  = str || 100;    // Private
  this.name = name || "Unnamed"; // Public
  
  this.getStrength = function() {
    console.log("Getting strength...");
    return strength;
  };
  
  this.levelUp = function() {
    console.log("Leveling up...");
    strength += 10;
  };
 
  this.printInfo = function() {
    console.log("Name: " + this.name +", Strength: " + strength);
  }
}
 
// Our "superclass"
Creature.prototype = {
  constructor: Creature,  
 
  // This is okay, name is not private.
  battleCry: function() {
    console.log(this.name + " will crush you!");
  }
};
 
// Subclass of Creature
function Furry(name, strength) {
  // call superclass constructor to 'steal' the public methods and data members
  Creature.call(this, name, strength); 
}
 
// Here's the prototypal inheritance
Furry.prototype = new Creature();   
Furry.prototype.constructor = Furry; 
 
Furry.prototype.shed = function() {
  console.log(this.name + " sheds all over the floor. Ew!");
}
 
var ogre = new Creature("Shrek");
ogre.name = "Bob"; // Doesn't work!
console.log(ogre.getStrength()); // 100
ogre.levelUp();
ogre.printInfo(); // "Name: Shrek, Strength: 110"
console.log(ogre.strength);