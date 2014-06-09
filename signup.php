<?php
    require_once('include/common.inc.php');
  
    $userInfo = getUserInfoFromRequest(GET_FROM_POST);
    $error = checkUserParams($userInfo);    
  
    strtolower($userInfo['email']);
    
    if ($error == ERROR_OK)
    {    
        $error = addNewUser($userInfo);   
    }
    
    $pageVars = array();
    $pageVars['title']  = 'Sign Up';
    $pageVars['header'] = 'Sign Up';
    $pageVars['action'] = 'signin.php';
    $pageVars['script'] = '';
    $pageVars['css']    = 'style-form';
    $message = '';
    
    if ($error == ERROR_OK)
    {
        $pageVars['success'] = 'Success: ';
        $message = 'you are signed up!';
    }
    else
    {
        $pageVars['success'] = 'Error: ';
        $message = getError($error);
    }
    $pageVars['message'] = $message;
    
    echo buildLayout('answer.html', $pageVars);