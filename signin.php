<?php
	require_once('include/common.inc.php');
    
    if (!userAuthorized())
    {
        exit();        
    }
   
    $userEmail = getUserInfoFromRequest(GET_FROM_POST);
    $error = ERROR_OK;
    
    $pageVars = array();
    $pageVars['title']  = 'Sign In';
    $pageVars['header'] = 'Sign In';
    $pageVars['script'] = '';
    $pageVars['css']    = 'style-form';

    if (!checkEmail($userEmail['email']))
	{
		$error = ERROR_EMAIL;
	}
    else
    {
        $userInfo = array(); 
        $userInfo = findSurveyByEmail($userEmail['email']);    
    
        if ((empty($userInfo)) && ($error == ERROR_OK))
            $error = ERROR_EMAIL_FIND;  
    }    
    
    if ($error == ERROR_OK)
    {
        $pageVars = joinUserInfo($userInfo[0], $pageVars);        
        echo buildLayout('answerlist.html', $pageVars);
    }
    else
    {
        $pageVars['success'] = 'Error: ';
        $pageVars['message'] = getError($error);
        echo buildLayout('answer.html', $pageVars); 
    }