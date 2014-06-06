<?php
	require_once('include/common.inc.php');
    
    if (!userAuthorized())
    {
        exit();        
    }
   
    $userEmail = getUserInfoFromRequest(GET_FROM_POST);
	$message = '';

    if (!checkEmail($userEmail['email']))
	{
		$message = 'incorrect e-mail!';
	}

    $userInfo = array(); 
    $userInfo = findSurveyByEmail($userEmail['email']);    
    
    if (!empty($userInfo))
        parseDate(&$userInfo[0]);
    else if ($message == '')
        $message = 'There is not such e-mail';   
        
    $pageVars = array();
    $pageVars['title']  = 'Sign In';
    $pageVars['header'] = 'Sign In';
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