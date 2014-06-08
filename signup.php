<?php
    require_once('include/common.inc.php');
  
    $userInfo = getUserInfoFromRequest(GET_FROM_POST);
    $message = checkUserParams($userInfo);    
  
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