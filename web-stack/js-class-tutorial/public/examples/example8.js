// example8.js

"use strict";

function Creature(name, strength, hitpoints) {   //  Note capital letter - convention for a constructor method
  // Define "name" property and give it a default value
  Object.defineProperty(this, "name", {
    get: function() {
      return name;
    },
    set: function(newName) {
      console.log("Setting name to " + newName);
      name = newName;
    },
    enumerable: true,
    configurable: true
  });
  
  this.name = name || "Unnamed";  // does this work still??

  // Repeat for strength
  Object.defineProperty(this, "strength", {
    get: function() {
      return strength;
    },
    set: function(newStrength) {
      console.log("Setting strength to " + newStrength);
      strength = newStrength;
    },
    enumerable: true,
    configurable: true
  });
    
  this.strength = strength || 10; // does this work still??

  Object.defineProperty(this, "hitpoints", {
    get: function() {
      return hitpoints;
    },
    set: function(newHitpoints) {
      console.log("Setting hitpoints to " + newHitpoints);
      hitpoints = newHitpoints;
    },
    enumerable: true,
    configurable: true
  });
  
  this.hitpoints = hitpoints || 100;
 
  // Hmm... every time we call new Creature(), another instance of this function is created
  this.printInfo = function() {
    console.log("Name: " + this.name + "\n"
               +"Strength: " + this.strength + "\n"
               +"Hitpoints: " + this.hitpoints);
  } 
}

var goblin1 = new Creature;
var goblin2 = new Creature("Scribblez", 10, 40); 
var goblin3 = new Creature("Dobby", 15); 
goblin3.printInfo();

//Setting name to Unnamed
//Setting Strength to 10
//Setting name to Unnamed
//Setting Strength to 10
//Setting name to Dobby
//Setting strength to 15
//Name: Dobby
//Strength: 15
//Hitpoints: undefined