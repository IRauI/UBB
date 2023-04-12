var t11 = document.getElementById("1.1");
var t12 = document.getElementById("1.2");
var t13 = document.getElementById("1.3");
var t14 = document.getElementById("1.4");

var t21 = document.getElementById("2.1");
var t22 = document.getElementById("2.2");
var t23 = document.getElementById("2.3");
var t24 = document.getElementById("2.4");

function removet1() {
    var t1 = document.getElementById("t1");
    var t2 = document.getElementById("t2");
    var options = t1.options;
    var option = document.createElement("option")
    option.text = options[options.selectedIndex].value;
    t2.add(option, t2[0]);
    t2[0].ondblclick = removet2;
    t1.remove(options.selectedIndex);
}

function removet2() {
    var t1 = document.getElementById("t1");
    var t2 = document.getElementById("t2");
    var options = t2.options;
    var option = document.createElement("option")
    option.text = options[options.selectedIndex].value;
    t1.add(option, t1[0]);
    t1[0].ondblclick = removet1;
    t2.remove(options.selectedIndex);
}

t11.ondblclick = removet1;
t12.ondblclick = removet1;
t13.ondblclick = removet1;
t14.ondblclick = removet1;

t21.ondblclick = removet2;
t22.ondblclick = removet2;
t23.ondblclick = removet2;
t24.ondblclick = removet2;