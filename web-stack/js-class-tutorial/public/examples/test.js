function Person(name) {
Object.defineProperty(this, "name", {
get: function() {
return name;
},
set: function(newName) {
name = newName;
},
enumerable: true,
configurable: true
});
this.sayName = function() {
console.log(this.name);
};
}