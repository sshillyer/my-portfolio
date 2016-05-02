var creature1 = {
  name: "Shrek",
  skill: "burping",
  brag: function() {
    console.log("My name is " + this.name + " and I am the best at " + this.skill + "!"); 
  }
};
 
var creature2 = Object.create(creature1, {
 
  // Define a property on creature2 that overrides creature1
  name: {
    configurable: true,
    enumerable: true,
    value: "Donkey",
    writable: true
  },
  skill: {
    configurable: true,
    enumerable: true,
    value: "talking, and talking, and talking",
    writable: true
  }
  // Note that we did not define brag() here!
});
 
creature1.brag();   // "My name is Shrek and I am the best at burping!"
creature2.brag();   // "My name is Donkey and I am the best at talking, and talking, and talking!"