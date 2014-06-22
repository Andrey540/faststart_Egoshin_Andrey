<?php

function getUserInfoFromRequest($parameter = GET_FROM_GET)
{ 
    $userParams = array();
    
    if ($parameter == GET_FROM_GET)
    {  
        $userParams['first_name'] = getParameterFromGet('first_name');
        $userParams['last_name']  = getParameterFromGet('last_name'); 
        $userParams['email']      = getParameterFromGet('email');
        $userParams['re_email']   = getParameterFromGet('re_email');
        $userParams['password']   = getParameterFromGet('password');
        $userParams['sex']        = getParameterFromGet('sex');
        $userParams['month']      = getParameterFromGet('month');
        $userParams['day']        = getParameterFromGet('day');
        $userParams['year']       = getParameterFromGet('year');
        $userParams['user_id']    = getParameterFromGet('user_id');
        $userParams['show_page']  = getParameterFromGet('show_page');
        $userParams['extension']  = getParameterFromGet('extension');
        $userParams['action']     = getParameterFromGet('action');
        $userParams['file_id']    = getParameterFromGet('file_id');
        $userParams['rate']       = getParameterFromGet('rate');
        $userParams['image']      = getParameterFromGet('image');
        $userParams['audio']      = getParameterFromGet('audio');
        $userParams['video']      = getParameterFromGet('video');
    }
    else if ($parameter == GET_FROM_POST)
    {
        $userParams['first_name'] = getParameterFromPost('first_name');
        $userParams['last_name']  = getParameterFromPost('last_name'); 
        $userParams['email']      = getParameterFromPost('email');
        $userParams['re_email']   = getParameterFromPost('re_email');         
        $userParams['password']   = getParameterFromPost('password');
        $userParams['sex']        = getParameterFromPost('sex');
        $userParams['month']      = getParameterFromPost('month');
        $userParams['day']        = getParameterFromPost('day');
        $userParams['year']       = getParameterFromPost('year');
        $userParams['user_id']    = getParameterFromPost('user_id');
        $userParams['show_page']  = getParameterFromPost('show_page');
        $userParams['extension']  = getParameterFromPost('extension');
        $userParams['action']     = getParameterFromPost('action');
        $userParams['file_id']    = getParameterFromPost('file_id');
        $userParams['rate']       = getParameterFromPost('rate');
        $userParams['image']      = getParameterFromPost('image');
        $userParams['audio']      = getParameterFromPost('audio');
        $userParams['video']      = getParameterFromPost('video');
    }
    else if ($parameter == GET_FROM_FILE)
    {
        $userParams['data_file']  = getFileParameter('data_file');    
    }

    return $userParams;
}

function userAuthorized()
{
    $result = true;
    if (empty($_SESSION['user_id']))
    {
        $result = false;
        header ('Location: formlogin.php');         
    }
    
    return $result;
}

function joinUserInfo($userInfo, $pageVars)
{
    parseDate(&$userInfo);
        
    $sex = array('Select Sex:', 'Man', 'Woman');
        
    $pageVars['user'] = array(         
                               array('class' => 'name',
                                     'title' => 'First Name: ',
                                     'data'  => $userInfo['first_name']),
                               array('class' => 'name',
                                     'title' => 'Last Name: ',
                                     'data'  => $userInfo['last_name']),
                               array('class' => 'email',
                                     'title' => 'E-mail: ',
                                     'data'  => $userInfo['email']),
                               array('class' => 'sex',
                                     'title' => 'You Are: ',
                                     'data'  => $sex[$userInfo['sex']]),
                               array('class' => '',
                                     'title' => 'Your Birthday: ',
                                     'data'  => $userInfo['day']   . ' ' . 
                                                $userInfo['month'] . ' ' . 
                                                $userInfo['year'])
                             );

    return $pageVars;
}