// example7.js

function Creature(name, strength, health) {   //  Note capital letter - convention for a constructor method
  this.name = name || "Unnamed";
  this.strength = strength || 10;
  this.hitpoints = health || 100;

  this.printInfo = function() {
    console.log("Name: " + this.name + "\n"
               +"Strength: " + this.strength + "\n"
               +"Hitpoints: " + this.hitpoints);
  } 
}

var goblin1 = new Creature;   // if not passing arguments, () not needed
var goblin2 = new Creature(); // same as agove
var goblin3 = new Creature("Dobby", 15);
goblin1.printInfo(); 
goblin3.printInfo();
// Name: Unnamed
// Strength: 10
// Hitpoints: 100
// Name: Dobby
// Strength: 15
// Hitpoints: 100