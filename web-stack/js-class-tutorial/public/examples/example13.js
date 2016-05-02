// example13.js

function Creature(name, strength) {
  this.name = name || "Unnamed";
  this.strength = strength || 100;
}
 
// Our "superclass"
Creature.prototype = {
  constructor: Creature,  
 
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
 
// Subclass of Creature
function Furry(name, strength) {
  this.name = name || "Furry creature";
  this.strength = strength || 40;
}
 
// Here's the prototypal inheritance
Furry.prototype = new Creature();    // get all our fancy Creature behavior
Furry.prototype.constructor = Furry; // make sure Furry still knows 'who' constructed it
 
// For fun, let's extend our Furry creature
Furry.prototype.shed = function() {
  console.log(this.name + " sheds all over the floor. Ew!");
}
 
var ogre = new Creature("Shrek", 110);
ogre.battleCry();       // "Shrek will crush you!"
ogre.printInfo();       // "Name: Shrek, Strength: 150"
ogre.levelUp();
ogre.printInfo();       // "Name: Shrek, Strength: 110"
var donkey = new Furry("Donkey", 9001);
donkey.battleCry();     // "Donkey will crush you!"
donkey.printInfo();     // "Name: Donkey, Strength: 9001"
donkey.shed();          // "Donkey sheds all over the floor. Ew!");
donkey.levelUp();
donkey.printInfo();     // "Name: Donkey, Strength: 9011"
console.log(donkey instanceof Creature); // true