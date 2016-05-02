// example6.js

var person1 = {
  _name: "Nicholas"
};

// This is one use-case for defineProperty -- we'll see more later
Object.defineProperty(person1, "name", {
  get: function() {
    console.log("Reading name");
    return this._name;
  },
  set: function(value) {
    console.log("Setting name to %s", value);
    this._name = value;
  },
  enumerable: true,
  configurable: true
});