<?php

    require_once('include/common.inc.php');
    
    $password = getUserInfoFromRequest(GET_FROM_POST);    

    $strength = calcTextStrenght($password['password']);
    $result = 0;
    
    if (($strength >= 20) && ($strength < 60))
    {
        $result = 1;
    }
    else if ($strength >= 60)
    {
        $result = 2;
    }

   echo $result;