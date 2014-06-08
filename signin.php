<?php
	require_once('include/common.inc.php');
    
    if (!userAuthorized())
    {
        exit();        
    }
   
    $userEmail = getUserInfoFromRequest(GET_FROM_POST);
	$message = '';
    
    $pageVars = array();
    $pageVars['title']  = 'Sign In';
    $pageVars['header'] = 'Sign In';
    $pageVars['script'] = '';
    $pageVars['css']    = 'style-form';

    if (!checkEmail($userEmail['email']))
	{
		$message = 'incorrect e-mail!';
	}
    else
    {
        $userInfo = array(); 
        $userInfo = findSurveyByEmail($userEmail['email']);    
    
        if ((empty($userInfo)) && ($message == ''))
            $message = 'There is not such e-mail';  
    }    
    
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