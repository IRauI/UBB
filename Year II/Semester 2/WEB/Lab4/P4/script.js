function isNumber(value) {
    if (typeof value === "string") {
        return !isNaN(value);
    }
}

function findTable(filter){
    var tables = document.getElementsByTagName('table');
    var table = tables[0];
    var rows = tables[0].getElementsByTagName('tr');

    for(let i = 1; i < tables.length; ++i){
        rows = tables[i].getElementsByTagName('tr');
        for(let j = 0; j < rows.length; ++j){
            row_header = rows[j].getElementsByTagName('th');
            if(row_header[0] == filter){
                table = tables[i];
                break;
            }
        }
    }

    return table;
}

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

function order(filter,a,b){
    if(filter.classList.contains("crescator")){
        return a > b;
    }
    return a < b;
}

function getFilterRow(matrix,filter,len){
    for(let i = 0; i < len; ++i){
        if(matrix[i][0] == filter){
            return i;
        }
    }
    return 0;
}

function sortTableByFIlter(table,filter,order){
    matrix = createMatrix(table);
    rows = table.getElementsByTagName("tr");
    index = getFilterRow(matrix,filter,rows.length);

    header = Array.from(rows[0].getElementsByTagName("th"));
    data = Array.from(rows[0].getElementsByTagName("td"));
    aux = header.concat(data);

    for(let i = 1; i < aux.length; ++i){
        for(let j = i + 1; j < aux.length; ++j){
            console.log(i,j);
            if(!isNumber(matrix[index][i].textContent)){
                if(order(filter,matrix[index][i].textContent,matrix[index][j].textContent)){
                    for(let k = 0; k < rows.length; ++k){
                        o = matrix[k][i].textContent;
                        matrix[k][i].textContent = matrix[k][j].textContent;
                        matrix[k][j].textContent = o;
                    }
                    console.log(matrix[index][i].textContent,matrix[index][j].textContent);
                }
            }
            else {
                if(order(filter,+matrix[index][i].textContent, +matrix[index][j].textContent)){
                    for(let k = 0; k < rows.length; ++k){
                        o = matrix[k][i].textContent;
                        matrix[k][i].textContent = matrix[k][j].textContent;
                        matrix[k][j].textContent = o;
                    }
                }
            }
        }
    }
    
    if(filter.classList.contains("crescator")){
        filter.classList.add("descrescator");
        filter.classList.remove("crescator");
    } else if(filter.classList.contains("descrescator")){
        filter.classList.remove("descrescator");
        filter.classList.add("crescator");
    }
}

function sortByCol(filter){
    table = findTable(filter);
    sortTableByFIlter(table,filter,order);
}
