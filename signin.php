<?php
	require_once('include/common.inc.php');
    
    if (!userAuthorized())
    {
        exit();        
    }
   
    $userEmail = getUserInfoFromRequest(GET_FROM_POST);
    $error = 0;
    
    $pageVars = array();
    $pageVars['title']  = 'Sign In';
    $pageVars['header'] = 'Sign In';
    $pageVars['script'] = '';
    $pageVars['css']    = 'style-form';

    if (!checkEmail($userEmail['email']))
	{
		$error = 4;
	}
    else
    {
        $userInfo = array(); 
        $userInfo = findSurveyByEmail($userEmail['email']);    
    
        if ((empty($userInfo)) && ($error == 0))
            $error = 11;  
    }    
    
    if ($error == 0)
    {
        $pageVars = joinUserInfo($userInfo[0], $pageVars);        
        echo buildLayout('answerlist.html', $pageVars);
    }
    else
    {
        $pageVars['success'] = 'Error: ';
        $pageVars['message'] = takeError($error);
        echo buildLayout('answer.html', $pageVars); 
    }