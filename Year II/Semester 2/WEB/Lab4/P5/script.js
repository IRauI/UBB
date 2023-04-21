var n = 5;
var value = 1;
var matrix;
var x;
var y;

function createMatrix(table){
    rows = table.getElementsByTagName('tr');
    matrix = [];
    rows = Array.from(rows);
    rows.forEach(element => {
        header = Array.from(element.getElementsByTagName("th"));
        data = Array.from(element.getElementsByTagName("td"));
        aux = header.concat(data);
        matrix.push(aux);
    });
    return matrix;
}

document.addEventListener('keydown', (e) => {
    e = e || window.event;
    if (e.key === 'ArrowUp') {
        if(x < n-1){
            matrix[x][y].textContent = matrix[x+1][y].textContent;
            x += 1;
            matrix[x][y].textContent = "";
        }
    } if (e.key === 'ArrowDown') {
        if(x > 0){
            matrix[x][y].textContent = matrix[x-1][y].textContent;
            x -= 1;
            matrix[x][y].textContent = "";
        }
    } if (e.key === 'ArrowLeft') {
        if(y < n-1){
            matrix[x][y].textContent = matrix[x][y+1].textContent;
            y += 1;
            matrix[x][y].textContent = "";
        }
    } if (e.key === 'ArrowRight') {
        if(y > 0){
            matrix[x][y].textContent = matrix[x][y-1].textContent;
            y -= 1;
            matrix[x][y].textContent = "";
        }
    }
  });


function generateTable(){
    var body = document.getElementsByTagName('body')[0];
    var table = document.createElement('table');
    table.style.border = 1;
    var tbody = document.createElement('tbody');
    table.appendChild(tbody);
    for (let i = 0; i < n; ++i){
        var tr = document.createElement('tr');
        for(let j = 0; j < n; ++j){
            var td = document.createElement('td');
            if(value != n*n){
                td.appendChild(document.createTextNode(value));
                value++;
            }
            tr.appendChild(td);
        }
        tbody.appendChild(tr);
    }
    body.appendChild(table);
    return table;
}

function shuffle(){
    var dirx = [1,-1,0,0];
    var diry = [0,0,1,-1];
    var i = 1;
    while(i <= 20*n*n){
        var rnd = Math.floor(Math.random()*4);
        if(x + dirx[rnd] > -1 && x + dirx[rnd] < n && y + diry[rnd] > -1 && y + diry[rnd] < n){
            matrix[x][y].textContent = matrix[x+dirx[rnd]][y+diry[rnd]].textContent;
            x += dirx[rnd];
            y += diry[rnd];
            matrix[x][y].textContent = "";
        }
        ++i;
    }
}

function run(){
    table = generateTable();
    matrix = createMatrix(table);
    x = n-1;
    y = n-1;
    shuffle();
}

run();
  

