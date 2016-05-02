"use strict";

// Put event handler on the New Game button on load
var bttnNewGame = document.getElementById("bttn-new-game");

bttnNewGame.addEventListener("click", function(event) {
    newGame();
    event.stopPropagation();
    event.preventDefault();
});

// Global color variables
var hiddenColor = "darkgray";
var revealedColor = "gray";
var bombColor = "red";
var bombCounter = 0;



// Add various event handlers
function addEventHandlers() {
    // Select the cells, then iterate through adding click handler
    var cells = document.getElementsByTagName("td");
    
    for (let i = 0; i < cells.length; i++) {
        (function(cellToUpdate){
            cellToUpdate.addEventListener("click", function() {
                checkCell(cellToUpdate);
            });
         }(cells[i]));
    }
}



// buildTable() : Builds the table for the page
// TODO: Make this use arguments instead of global variables
function buildTable(numRows, numCols) {
    let board = document.getElementById("game-board");
        
    // Make a table node
    let table = document.createElement("table");
    board.appendChild(table);
    
    // Add a tbody with numRows-1 additional rows, each with numCols td elements
    let tableBody = document.createElement("tbody");
    table.appendChild(tableBody);
    
    // Append each row and append the td for each row
    let cellId = 0;
    for (let row = 1; row <= numRows; row++) {
        let thisRow = document.createElement("tr");
        tableBody.appendChild(thisRow);

        for (let col = 1; col <= numCols; col++) {
            let thisCell = document.createElement("td");
            thisCell.setAttribute("isRevealed", "false");
            thisCell.style.border = "1px solid black";
            thisCell.style.backgroundColor = hiddenColor;
            thisCell.setAttribute("id", String(cellId));
            thisCell.setAttribute("bomb-neighbors-cnt", "0");
            thisRow.appendChild(thisCell);
            cellId++;
        }
    }
}

// Marks a cell with a certain color
// Arguments: color. string. Use a valid css color property
// Arguments: cell. a td element to mark up (as currently implemented)
function markCell(cell, color) {
    cell.style.background = color;
}

// Destroy the table (game board) so we can build a new one
function clearBoard() {
    let child = document.getElementsByTagName("table");
    if (child[0]) {
        let parent = document.getElementById("game-board");
        parent.removeChild(child[0]);
    }
}


// Build an index of bombs and put them in random locations
function plantBombs(rows, cols) {
    let totalCells = Number(rows) * Number(cols);
    console.log("There are " + totalCells + " total cells");
    let totalBombs = Math.floor(totalCells * 0.15625);
    console.log("There are " + totalBombs + " total bombs");
    
    // Build an array of values from 1 to totalCells
    let bombIndices = buildIndexArray(totalCells);
    // call a shuffle function on bombIndices, then grab the first totalBombs values and slice the array down to that size
    shuffleArray(bombIndices);
    bombIndices = bombIndices.slice(0, totalBombs);
    bombIndices.sort();
    // DEBUG START
    console.log("Bombs are at indices: " );
    let bombIndicesString = "";
    for (let i = 0; i < bombIndices.length; i++) {
        bombIndicesString += (String(bombIndices[i]) + " ");
    }
    console.log(bombIndicesString);
//    renderAllCells("bomb-cell");
    // DEBUG END
    
    addBombClassToCells(bombIndices);
    incrementNeighborTally(bombIndices, rows, cols);
    return totalBombs;
}

// Calls subroutines to initialize a new game
function newGame() {
    clearBoard();
    let maxRows = document.getElementById("row-setting").value;
//    console.log("maxRows set to " + maxRows);
    let maxCols = document.getElementById("column-setting").value;
//    console.log("maxCols set to " + maxCols);
    buildTable(maxRows, maxCols);
    addEventHandlers();
    let numBombs = plantBombs(maxRows, maxCols);
    updateBombCounter(numBombs);
    toggleBombPanel("show");
}

// Shuffle an array
function shuffleArray(a) {
    let n = a.length;
    let random;
    
    for (let j = 0; j < n - 1; j++) {
        (function(x) {
            let change = Number(randomInt(x, n-x));
            swap(a, j, change); 
        }(j));
    }
}

// Swap value in a[i] with a[change]
function swap(a, i, change) {
    let temp = a[i];
    a[i] = a[change];
    a[change] = temp;
}


// Generate a random integer from min to max
function randomInt(min, max) {
    let result = Math.floor( (Math.random() * max) + min);
    return result;
}


// Build an array with integers [0 .. size]
function buildIndexArray(size) {
    let newArr = new Array();
    for (let i = 0; i < size; i++) {
        newArr.push(i);
    }
    return newArr;
}


// turn the .bomb-panel on and off
function toggleBombPanel(newStatus) {
    let bombPanel = document.getElementById("bomb-panel");
    console.log("bombPanel = " + bombPanel);
    {
        if (newStatus === "show") {
            console.log("Toggle bomb panel ON");
//            bombPanel.setAttribute("hidden", "false");
            bombPanel.removeAttribute("hidden");
        }
        else {
            console.log("Toggle bomb panel OFF");
            bombPanel.setAttribute("hidden", "true");
        }
    }
}

// Increment or decrement the bomb counter on page
function updateBombCounter(change) {
    let bombPanel = document.getElementById("bomb-qty");
    bombPanel.textContent = bombCounter + change;
}

// add the bomb-cell class to all bomb td elements (cells)
function addBombClassToCells(bombIndices) {
    let cells = document.getElementsByTagName("td");
    for (let i = 0; i < bombIndices.length; i++) {
        cells[bombIndices[i]].className += "bomb-cell";
    }
}


// render all cells of a given type
function renderAllCells(typeId) {
    let cells = document.getElementsByClassName(String(typeId));
    if (typeId === "bomb-cell") {
        let newColor = bombColor;
    }
    for (let i = 0; i < cells.length; i++) {
        markCell(cells[i], bombColor);
    }
}

function getCellType(cell) {
    let cellType = cell.className;
//    console.log("checking cell " + cell + ": type: " + cellType);
//    for (let i = 0; i < cellType.length; i++) 
    return cellType;
}

function checkCell(cell) {
    if (cell.getAttribute("isRevealed") == "false") {
        // If cell is a bomb, change to bomb color and BOOM!
        if (getCellType(cell) == "bomb-cell") {
            cell.setAttribute("isRevealed", "true");
            markCell(cell, bombColor);
            endGame();
        }
        
        else {
            markCell(cell, revealedColor);
            cell.setAttribute("isRevealed", "true");
            revealBombs(cell);
        }
    }
}

function revealBombs(cell) {
    if (cell != null) {
        let nearbyBombs = cell.getAttribute("bomb-neighbors-cnt");
        cell.textContent = String(nearbyBombs);
    }
}


function incrementNeighborTally(bombIndices, rows, cols) {
    for (let i = 0; i < bombIndices.length; i++) {
        let center = bombIndices[i];
        let thisCol = (center % cols);
        let thisRow = Math.floor(center / cols);
        console.log("center: " + center + ", bombIndicies[i]: " + bombIndices[i] + ", thisRow: " + thisRow + ", thisCol: " + thisCol);
                
        // First calculate offset assuming we're not on any edge
        let up = center - cols;
        let upLeft = up - 1;
        let upRight = up + 1;
        
        let left = center - 1;
        let right = center + 1;
        
        let down = Number(center) + Number(cols);
        console.log("down:" + down);
        let downLeft = Number(down) - 1;
        let downRight = Number(down) + 1;
        
        
        // Set left or right sides to -1 if the cell we're checking is on a left/right edge
        if (thisCol === 0) {
            upLeft = left = downLeft = -1;
        }
        else if (thisCol === (cols - 1)) {
            upRight = right = downRight = -1;
        }
        
        // Set top or bottom to -1 similarly
        if (thisRow === 0) {
            upLeft = up = upRight = -1;
        }
        else if (thisRow === (rows - 1)) {
            downLeft = down = downRight = -1;
        }
        
        console.log("down: " + down);
        
        let indicesToIncrement = new Array();
        indicesToIncrement.push(upLeft);
        indicesToIncrement.push(up);
        indicesToIncrement.push(upRight);
        indicesToIncrement.push(left);
        indicesToIncrement.push(right);
        indicesToIncrement.push(downLeft);
        indicesToIncrement.push(down);
        indicesToIncrement.push(downRight);
        
        // TODO: test incrementBombNeighborsCount()
        for (let i = 0; i < indicesToIncrement.length; i++) {
            if (indicesToIncrement[i] >= 0) {
                incrementBombNeighborsCount(indicesToIncrement[i]);
            }
        }
    }
}

function incrementBombNeighborsCount(index) {
    let cell = document.getElementById(String(index));
    if (cell) {
        let oldValue = cell.getAttribute("bomb-neighbors-cnt");
        // TODO: add "bomb-neighbors-cnt" attribute during buildTable method so we have something to grab and update
        let newValue = Number(oldValue) + Number(1);
        console.log("Setting cell " + index + " bomb-neighors-cnt to " + newValue );
    //    cell.setAttribute("bomb-neighbors-cnt", String(newValue));
        cell.setAttribute("bomb-neighbors-cnt", newValue);
    }
}

// Handle the end of game logic
function endGame() {
    console.log("BOOM");
    console.log("GAME OVER");
    renderAllCells("bomb-cell");
    renderAllCells("isRevealed");
    toggleBombPanel("hide");
}




//
function countNearbyBombs(cell) {
    
}