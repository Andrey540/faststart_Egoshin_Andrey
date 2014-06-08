<?php
 
 function takeError($errorId)
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
                     9  => 'can not sign up!',
                     10 => 'this e-mail is already exist!',
                     11 => 'There is not such e-mail',
                     12 => 'Can not upload file!');
                      
 
 
 
 
 
    return $message[$errorId];
 }
 
