<?php
    require_once('include/common.inc.php');
  
    $userInfo = getUserInfoFromRequest(GET_FROM_POST);
    $message = '';
  
    if (!checkName($userInfo['first_name']))
    {
        $message = 'wrong First Name identifier!';
    }
    else if (!checkName($userInfo['last_name']))
    {
        $message = 'wrong Last Name identifier!';
    }
    else if (!checkPassword($userInfo['password']))
    {
        $message = 'wrong password identifier!';
    }
    else if ($userInfo['email'] != $userInfo['re_email'])
    {
        $message = 'wrong e-mail identifier!';
    }
    else if (!checkEmail($userInfo['email']))
    {
        $message = 'wrong e-mail identifier!';
    }    
    else if (!checkSex($userInfo['sex']))
    {
        $message = 'wrong sex identifier!';
    }    
    else if (!checkMonth($userInfo['month']))
    {
        $message = 'wrong month identifier!';
    }    
    else if (!checkDay($userInfo['day']))
    {
        $message = 'wrong day identifier!';
    }    
    else if (!checkYear($userInfo['year']))
    {
        $message = 'wrong year identifier!';
    }      
  
    strtolower($userInfo['email']);
    
    if ($message == '')
    {    
        $addUser = addNewUser($userInfo);
        switch ($addUser)
        {
            case -1:
                $message = 'can not sign up!';
                break;
            case -2:
                $message = 'this e-mail is already exist!';
                break;  
        }        
    }
    
    $pageVars = array();
    $pageVars['title']  = 'Sign Up';
    $pageVars['header'] = 'Sign Up';
    $pageVars['action'] = 'signin.php';
    $pageVars['script'] = '';
    $pageVars['css']    = 'style-form';
    
    if ($message == '')
    {
        $pageVars['success'] = 'Success: ';
        $message = 'you are signed up!';
    }
    else
    {
        $pageVars['success'] = 'Error: ';
    }
    $pageVars['message'] = $message;
    
    echo buildLayout('answer.html', $pageVars);