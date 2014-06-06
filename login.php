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
        parseDate(&$userInfo[0]);
        $_SESSION['user_id'] = $userInfo[0]['user_id'];
    }
        
    $pageVars = array();
    $pageVars['title']  = 'Log In';
    $pageVars['header'] = 'Log In';
    $pageVars['script'] = '';
    $pageVars['css']    = 'style-form';
    
    if ($message == '')
    {
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
                                         'data'  => $userInfo[0]['day'] . ' ' . $userInfo[0]['month'] . ' ' . $userInfo[0]['year'])
                                 );
        
        echo buildLayout('answerlist.html', $pageVars);
    }
    else
    {
        $pageVars['success'] = 'Error: ';
        $pageVars['message'] = $message;

        echo buildLayout('answer.html', $pageVars); 
    }