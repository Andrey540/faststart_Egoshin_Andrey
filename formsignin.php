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
        parseDate(&$userInfo[0]);
        
        $pageVars['user'] = array(         
                                   array('class' => 'name',
                                         'title' => 'First Name: ',
                                         'data'  => $userInfo[0]['first_name']),
                                   array('class' => 'name',
                                         'title' => 'Last Name: ',
                                         'data'  => $userInfo[0]['last_name']),
                                   array('class' => 'email',
                                         'title' => 'E-mail: ',
                                         'data'  => $userInfo[0]['email']),
                                   array('class' => 'sex',
                                         'title' => 'You Are: ',
                                         'data'  => $userInfo[0]['sex']),
                                   array('class' => '',
                                         'title' => 'Your Birthday: ',
                                         'data'  => $userInfo[0]['day']   . ' ' . 
                                                    $userInfo[0]['month'] . ' ' . 
                                                    $userInfo[0]['year'])
                                 );
        
        echo buildLayout('answerlist.html', $pageVars);   
    }
    else
    {
        echo buildLayout('signin.html', $pageVars);
    }