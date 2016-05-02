// example11.js

// From Example 10:
function Creature(name, strength) {
  this.name = name || "Unnamed";
  this.strength = 100 || strength;
}
 
// Note: We're using object literal notation to define multiple prototype methods
Creature.prototype = {
  constructor: Creature,    // Without this, constructor would be set to Object instead of Creature
 
  battleCry: function() {
    console.log(this.name + " will crush you!");
  },
 
  printInfo: function() {
    console.log("Name: " + this.name +", Strength: " + this.strength);
  },
 
  levelUp: function() {
    this.strength += 10;
  }
};
 
var ogre = new Creature("Shrek", 110);
ogre.battleCry();  // "Shrek will crush you!"
ogre.printInfo(); // "Name: Shrek, Strength: 150"
ogre.levelUp();
ogre.printInfo(); // "Name: Shrek, Strength: 160"

// From Example 11:

Creature.prototype.rest = function() {
  console.log(this.name + " sits down and rests a while.");
}

ogre.rest(); // "Shrek sits down and rests a while."