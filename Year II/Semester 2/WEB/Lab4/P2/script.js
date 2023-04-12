/*
var buton = document.getElementById("buton");

function validate(){
    var nume = document.getElementById("nume");
    var data = document.getElementById("data");
    var varsta = document.getElementById("varsta");
    var reg = /[a-zA-Z]/
    console.log("intra");
    if(!nume.value){
        console.log("intra");
        nume.style.border("1px solid red");
        nume.style.borderRadius("25px");
        nume.style.margin("50px auto");
    }else{
        for(let i = 0; i < nume.value.length; i++)
        {
            if(!reg.test(nume.value[i])){
                console.log("intra");
                nume.style.border("1px solid red");
                nume.style.borderRadius("25px");
                nume.style.margin("50px auto");
                break;
            }
    
        }
    }
}


buton.onclick = validate;
*/

function validateNume(nume){
    var reg = /[a-zA-Z]/
    for(let i = 0; i < nume.length; i++){
        if(!reg.test(nume[i])){
            return false;
        }
    }
    return true;
}

function validate() {
	var nume = document.getElementById("nume").value;
    var varsta = document.getElementById("varsta").value;
    var data = document.getElementById("data").value;
    var eroare = "";
	if (nume === "" || !validateNume(nume)) {
		document.getElementById("nume").classList.add("error");
		eroare += " nume";
	} else {
		document.getElementById("nume").classList.remove("error");
	}
    if (!data) {
		document.getElementById("data").classList.add("error");
		eroare += " data";
	} else {
		document.getElementById("data").classList.remove("error");
	}
    if(!varsta || varsta <= 0){
        document.getElementById("varsta").classList.add("error");
		eroare += " varsta";
    } else {
        document.getElementById("varsta").classList.remove("error");
    }
    if(eroare != ""){
        alert("Urmatoarele campuri sunt introduse gresit:"+eroare)
    } else {
        alert("Campurile sunt completate corect");
    }
    
}