// example4.js

var shape = {
    color: "red"
}
console.log(shape.hasOwnProperty("color")); // true

Object.defineProperty(shape, "color", {
    configurable: false
});

delete shape.color; // Throws an error

// Throws an error. Cannot turn configurable back on - locks down all attributes
Object.defineProperty(shape, "color", {
    configurable: true 
});