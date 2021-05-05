<?php
session_start();
?>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <script src="https://cdn.jsdelivr.net/npm/vue@2/dist/vue.js"></script>
    <link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.1.3/css/bootstrap.min.css" integrity="sha384-MCw98/SFnGE8fJT3GXwEOngsV7Zt27NXFoaoApmYm81iuXoPkFOJwJ8ERdknLPMO" crossorigin="anonymous">
    <title>Document</title>
</head>
<body>
    <header>
        <nav class="navbar navbar-expand-lg navbar-light bg-light">
            <img id="imgQB" src="../logo2.png" width="12%">
            <div class="collapse navbar-collapse" id="navbarSupportedContent">
                <ul class="navbar-nav nav mr-auto">
                    <li class="nav-item active">
                        <a class="nav-link" href="signIn/signIn.php">S'inscrire</a>
                    </li>
                    <li class="nav-item">
                        <a class="nav-link" href="#">Se connecter</a>
                    </li>
                </ul>
            </div>
        </nav>
    </header>
    <div class="container" id="app">
        <div class="row ">
            <div class="col-md-4" style="background-color: white">
            </div>
            <div class="col-md-4" style="background-color: grey">
                <div class="container" >
                    <div class="row">
                        <div class="col-md-2 col-md-offset-5">
                            <p>mail</p>
                            <input type="text" placeholder="mail address" id="mail">
                        </div>
                    </div>
                    <div class="row">
                        <div class="col-md-2 col-md-offset-5">
                            <label>passwords</label>
                            <input type="text" placeholder="password" id="pssword">
                            
                        </div>
                    </div>
                </div>
            </div>
            <div class="col-md-4" style="background-color: white">
            </div>
        </div>
        <div class="row ">
            <div class="col-md-4" style="background-color: white">
            </div>
            <div class="col-md-4" style="background-color: grey">
                <div class="container" >
                        <button v-on:click="signIn()">Sign In</button>
                </div>
            </div>
            <div class="col-md-4" style="background-color: white">
            </div>
        </div>
    </div>
    <?php

    ?>
</body>
<script>
    const app =  new Vue({
        el:"#app",
        data:{
            user:""
        },
        methods:{
            signIn: function() {
                let login = document.getElementById("mail").value;
                let psswrd = document.getElementById("pssword").value;
                let request = new XMLHttpRequest();  
                request.open("GET","http://localhost:8888/users/get/getValue.php?password=" + psswrd + "&mail=" + login ,true); 
                request.onreadystatechange = function() {
                    if(request.readyState == 4) {
                        if(request.status == 200) {
                            let ObjJson = JSON.parse(request.responseText);
                            //TODO check if the response IS GOOD

                            this.$session.start();
                            for (const [key, value] of ObjJson.entries) {
                                console.log(`${key}: ${value}`);
                                this.$session.set(`${key}`, `${value}`);
                            }
                            
                           //window.location.href = "http://localhost:8888/appWebClientPa/vujsTest/home.php";
                        } else {
                            alert("Error: returned status code " + request.status + " " + request.statusText);
                        }
                    }
                }
                request.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
                request.send();
            }
        }
    });
</script>
</html>
