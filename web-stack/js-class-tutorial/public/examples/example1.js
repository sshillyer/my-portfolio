// example1.js

var redSquare = {
  sides: 4,
  color: "red",
  identity: function() {
    console.log(this.sides + " sided " + this.color + " shape.");
  }
};

redSquare.identity(); // 4 sided red shape.