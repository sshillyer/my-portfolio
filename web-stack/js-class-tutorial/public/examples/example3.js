// example3.js

// If we use strict, assigning to square.color after making writable 
// false throw an error instead of failing silently
// "use strict";   // remove the comment here to try that out

var square = {
    color: "pink",
};
console.log(square.color); // pink
square.color = "red";

Object.defineProperty(square, "color", {
  writable: false
});

console.log(square.color); // red
square.color = "green";
console.log(square.color); // red