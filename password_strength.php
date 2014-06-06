<?php

    require_once('include/common.inc.php');
    
    const PASSWORD_WEAK   = 0;
    const PASSWORD_GOOD   = 1;
    const PASSWORD_STRONG = 2;
    
    $password = getUserInfoFromRequest(GET_FROM_POST);    

    $strength = calcTextStrenght($password['password']);

    $result = PASSWORD_WEAK;
     
    $strengthCriteria = array
    (
        PASSWORD_GOOD   => 60,
        PASSWORD_STRONG => 70
    );
    
    if (($strength >= $strengthCriteria[PASSWORD_GOOD]) && ($strength < $strengthCriteria[PASSWORD_STRONG]))
    {
        $result = PASSWORD_GOOD;
    }
    else if ($strength >= $strengthCriteria[PASSWORD_STRONG])
    {
        $result = PASSWORD_STRONG;
    }

   echo $result;