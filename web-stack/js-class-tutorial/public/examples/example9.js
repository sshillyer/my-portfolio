// example9.js

function Creature(name) {
  this.name = name || "Unnamed";
}
 
Creature.prototype.printInfo = function() {
  console.log("Name: " + this.name);
}
 
var goblin = new Creature("Dobby");
goblin.printInfo(); // -->  Name: "Dobby"