<?php

 define('ERROR_OK', 0);
 define('ERROR_FIRST_NAME', 1);
 define('ERROR_LAST_NAME', 2);
 define('ERROR_PASSWORD', 3);
 define('ERROR_EMAIL', 4);
 define('ERROR_SEX', 5);
 define('ERROR_MONTH', 6);
 define('ERROR_DAY', 7);
 define('ERROR_YEAR', 8);
 define('ERROR_ADD_USER', 9);
 define('ERROR_EMAIL_EXIST', 10);
 define('ERROR_EMAIL_FIND', 11);
 define('ERROR_UPLOAD', 12);
 
 function getError($errorId)
 {
    $message = array(0  => 'OK',
                     1  => 'wrong First Name identifier!',
                     2  => 'wrong Last Name identifier!',
                     3  => 'wrong password identifier!',
                     4  => 'wrong e-mail identifier!',
                     5  => 'wrong sex identifier!',
                     6  => 'wrong month identifier!',
                     7  => 'wrong day identifier!',
                     8  => 'wrong year identifier!',
                     9  => 'can not add user!',
                     10 => 'this e-mail is already exist!',
                     11 => 'there is not such e-mail',
                     12 => 'can not upload file!');
                     
    return $message[$errorId];
 }
 
