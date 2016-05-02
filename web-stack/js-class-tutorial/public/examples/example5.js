// example5.js

var shape = {};

Object.defineProperty(shape, "color", {
  value: "red",
  enumerable: true,    // default: true
  configurable: true,  // default: true
  writable: true       // default: true
});

Object.defineProperty(shape, "sides", {
  value: 4,
  enumerable: true,    // default: true
  configurable: true,  // default: true
  writable: false       // default: true
});

Object.defineProperty(shape, "hiddenKey", {
  value: "You will not see this property in .keys()",
  enumerable: false,    // default: true
  configurable: true,  // default: true
  writable: false       // default: true
});

console.log(Object.keys(shape));  // No hiddenKey property!
console.log(shape.color + " shape has " + shape.sides + " sides.");
// Attempt to update color and shape
shape.color = "blue";
shape.sides = 20;
console.log(shape.color + " shape has changed color, but still has " + shape.sides + " sides.");