
let token = document.getElementById("token").innerHTML;
let mail = document.getElementById("mail").innerHTML;
let idUser = document.getElementById("di").innerHTML;
let activeUrl= "https://quickbaluchonservice.site/api/QuickBaluchon/users/get/getValue.php?tokenEmail=" + token + "&mail=" + mail;

let updateActiveUserAtributeUrl = "https://quickbaluchonservice.site/api/QuickBaluchon/users/post/update.php";

function  active(){
    let request = new XMLHttpRequest();  
    request.open("GET",activeUrl,true); 
    request.onreadystatechange = function() {
        if(request.readyState == 4) {
                if(request.status == 200) {
                    let result = JSON.stringify(request.responseText);
                    console.log (result);
                    updateActiveUserAtribute(idUser);
            } else {
                alert("Error: returned status code " + request.status + " " + request.statusText);
            }
        }
    }
    request.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
    request.send();
}


function updateActiveUserAtribute(idData) {
    let json = {
        "id":String(idData),
        "active":1
    }
    let request = new XMLHttpRequest();  
    request.open("POST",updateActiveUserAtributeUrl,true); 
    request.onreadystatechange = function() {
        if(request.readyState == 4) {
                if(request.status == 200) {
                    console.log(request.responseText);
                    let result = JSON.stringify(request.responseText);
                    console.log(result);
                    if(result.length <= 1) {
                        console.log(result["message"]);
                    } else {
                        window.location.href = "https://quickbaluchonservice.site/QuickBaluchon/signIn/signIn.php";
                    }
            } else {
                alert("Error: returned status code " + request.status + " " + request.statusText);
            }
        }
    }
    request.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
    request.send(JSON.stringify(json));
}
    