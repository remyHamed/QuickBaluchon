let webSitePath ="https://quickbaluchonservice.site";



function signIn() {
    let login = document.getElementById("mail").value;
    let psswrd = document.getElementById("pssword").value;
    let homePage =[webSitePath + "/home/homeDriver.php,webSitePath" + "/home/homeAdmin.php",webSitePath + "/home/homeUser.php"];
    let request = new XMLHttpRequest();
    
    request.open("GET","https://quickbaluchonservice.site/api/QuickBaluchon/users/get/getValue.php?password=" + psswrd + "&mail=" + login ,true); 
    request.onreadystatechange = function() {
        if(request.readyState == 4) {
            if(request.status == 200) {
                let ObjJson = JSON.parse(request.responseText);
                console.log(request.responseText);
                console.log("affuchafe de l'objet");
                console.log(ObjJson);
                console.log("affuchafe de l'objet ObjJson[statut]");
                console.log(ObjJson["statut"]);
                console.log("type de ObjJson[statut]");
                console.log(typeof(ObjJson["statut"]));
                console.log("type de ObjJson[statut]");
                let num = ObjJson["statut"].toString();
                console.log(" num 1");
                console.log(num);
                num = parseInt(num);
                console.log(" num 2");
                console.log(num);
                console.log(typeof(numRedirection));
                let numRedirection = num;
                //console.log(typeof(numRedirection));
                console.log(numRedirection);
                window.location.href = homePage[numRedirection - 1];
            } else {
                alert("Error: returned status code " + request.status + " " + request.statusText);
            }
        }
    }
    request.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
    request.send();
}






/*
function getUser() {
    let login = document.getElementById("mail").value;
    let psswrd = document.getElementById("pssword").value;
    let request = new XMLHttpRequest();  
     request.open("GET","http://localhost:8888/users/get/getValue.php?password=" + psswrd + "&mail=" + login ,true); 
     request.onreadystatechange = function() {
        if(request.readyState == 4) {
            if(request.status == 200) {
                let ObjJson = JSON.parse(request.responseText);
                console.log(ObjJson);
            } else {
                alert("Error: returned status code " + request.status + " " + request.statusText);
            }
        }
    }
    request.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
    request.send();
}*/
