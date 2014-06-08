<?php

    require_once('include/common.inc.php');
    
    if (!userAuthorized())
    {
        exit();        
    }
    
    $userId = getUserInfoFromRequest(GET_FROM_GET);
    
    $pageVars = array();
    $pageVars['title']   = 'Sign In';
    $pageVars['header']  = 'Sign In';
    $pageVars['action']  = 'signin.php';
    $pageVars['script']  = '';
    $pageVars['css']     = 'style-form';
    
    if (!empty($userId['user_id']))
    {
        $userInfo = array();
        $userInfo = findSurveyById($userId['user_id']);

        $pageVars = printUserInfo($userInfo[0], $pageVars);
        
        echo buildLayout('answerlist.html', $pageVars);   
    }
    else
    {
        echo buildLayout('signin.html', $pageVars);
    }