<?php
	require_once('include/common.inc.php');
   
    $logIn = getUserInfoFromRequest(GET_FROM_POST);

    $userInfo = array(); 
    $userInfo = findSurveyByEmailAndPass($logIn['email'], $logIn['password']);  
    
    $pageVars = array();
    $pageVars['title']  = 'Log In';
    $pageVars['header'] = 'Log In';
    $pageVars['script'] = '';
    $pageVars['css']    = 'style-form'; 

    if (empty($userInfo))
    {
        $pageVars['success'] = 'Error: ';
        $pageVars['message'] = 'Wrong e-mail or password!';
        echo buildLayout('answer.html', $pageVars); 
        session_unset();        
    }
    else
    {
        $_SESSION['user_id'] = $userInfo[0]['user_id'];
        $pageVars = printUserInfo($userInfo[0], $pageVars);        
        echo buildLayout('answerlist.html', $pageVars);
    }   
