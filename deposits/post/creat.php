<?php
include("./../../chckFnctns/chckFnctns.php");
include("./../functions/functions.php");
$content = file_get_contents('php://input');
$data = json_decode($content);
$intKey = [
    "idDepot",
    "idUser"
];
countJsonObjElem($data, 2);   // must have 11 elements
areSetJsonObjElem($data);                   // elements are init
strToIntJsonObjElem($data, $intKey);         // cast elements
echo insertDeposit(
    $data->{"idDepot"},
    $data->{"idUser"});