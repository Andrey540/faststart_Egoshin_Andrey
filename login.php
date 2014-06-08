<?php
	require_once('include/common.inc.php');
   
    $logIn = getUserInfoFromRequest(GET_FROM_POST);
	$message = '';

    $userInfo = array(); 
    $userInfo = findSurveyByEmailAndPass($logIn['email'], $logIn['password']);  

    if (empty($userInfo))
    {
        $message = 'Wrong e-mail or password!';
        session_unset();        
    }
    else
    {
        $_SESSION['user_id'] = $userInfo[0]['user_id'];
    }
         
    $pageVars = array();
    $pageVars['title']  = 'Log In';
    $pageVars['header'] = 'Log In';
    $pageVars['script'] = '';
    $pageVars['css']    = 'style-form';    
    
    if ($message == '')
    {
        $pageVars = printUserInfo($userInfo[0], $pageVars);
        
        echo buildLayout('answerlist.html', $pageVars);
    }
    else
    {
        $pageVars['success'] = 'Error: ';
        $pageVars['message'] = $message;
        echo buildLayout('answer.html', $pageVars); 
    }