var b11 = document.getElementById("b11");
var b12 = document.getElementById("b12");
var b13 = document.getElementById("b13");
var b14 = document.getElementById("b14");

var b21 = document.getElementById("b21");
var b22 = document.getElementById("b22");
var b23 = document.getElementById("b23");
var b24 = document.getElementById("b24");

var b31 = document.getElementById("b31");
var b32 = document.getElementById("b32");
var b33 = document.getElementById("b33");
var b34 = document.getElementById("b34");

var b41 = document.getElementById("b41");
var b42 = document.getElementById("b42");
var b43 = document.getElementById("b43");
var b44 = document.getElementById("b44");

var buttons = document.querySelectorAll(".contentbtn");

var values = [1,1,2,2,3,3,4,4,5,5,6,6,7,7,8,8];

var clickedBtns = [];

var table = document.getElementById("table");

function random_value(){
    var index = Math.floor(Math.random()*values.length);
    var value = values[index];
    values.splice(index,1);
    return value;
}


function assign_value(button){
    button.value = random_value();
}

buttons.forEach(element => {
    assign_value(element);
});


function hide_values(b1,b2){
    b1.style.backgroundImage = "none";
    b1.style.backgroundColor = "#CED46A";
    b1.disabled = false;
    b2.style.backgroundImage = "none";
    b2.style.backgroundColor = "#CED46A";
    b2.disabled = false;
}

function show_value(button){
    if(button.value == "1"){
        button.style.backgroundImage = "url('images/andrei.png')";
        button.style.backgroundSize = "auto";
        button.style.backgroundPosition = "center";
    }
    if(button.value == 2){
        button.style.backgroundImage = "url('images/dana.png')";
        button.style.backgroundSize = "auto";
        button.style.backgroundPosition = "center";
    }
    if(button.value == 3){
        button.style.backgroundImage = "url('images/ionel.png')";
        button.style.backgroundSize = "auto";
        button.style.backgroundPosition = "52% 18%";
    }
    if(button.value == 4){
        button.style.backgroundImage = "url('images/gica.png')";
        button.style.backgroundSize = "auto";
        button.style.backgroundPosition = "50% 30%";
    }
    if(button.value == 5){
        button.style.backgroundImage = "url('images/shaman.png')";
        button.style.backgroundSize = "auto";
        button.style.backgroundPosition = "57% 11%";
    }
    if(button.value == 6){
        button.style.backgroundImage = "url('images/sura.png')";
        button.style.backgroundSize = "auto";
        button.style.backgroundPosition = "40% 15%";
    }
    if(button.value == 7){
        button.style.backgroundImage = "url('images/razboinic.png')";
        button.style.backgroundSize = "auto";
        button.style.backgroundPosition = "50% 20%";
    }
    if(button.value == 8){
        button.style.backgroundImage = "url('images/ninja.png')";
        button.style.backgroundSize = "auto";
        button.style.backgroundPosition = "40% 25%";
    }
}


buttons.forEach(element => {
    element.style.backgroundImage = "none";
    element.style.backgroundColor = "#CED46A";
    //show_value(element);
});

function show_button(){
    clickedBtns.push(this);
    show_value(this);
    this.disabled = true;
}

function add_click(){
    buttons.forEach(element => {
        element.onclick = show_button;
     });
}

add_click();

function delay(time) {
    return new Promise(resolve => setTimeout(resolve, time));
}

table.addEventListener('click', async function guess(){
    if(clickedBtns.length == 2){
        if(clickedBtns[0].value == clickedBtns[1].value){
            clickedBtns.pop();
            clickedBtns.pop();
        }else{
            await delay(500);
            hide_values(clickedBtns[0],clickedBtns[1]);
            clickedBtns.pop();
            clickedBtns.pop();
        }
    }
});