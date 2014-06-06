<?php
	require_once('include/common.inc.php');
    
    if (!userAuthorized())
    {
        exit();        
    }
   
    $showPage = getUserInfoFromRequest(GET_FROM_GET);
    
    $pageIndex = $showPage['show_page'];
    
    $pageVars = array();
    $pageVars['title']  = "User's Info";
    $pageVars['header'] = "User's Info";
    $pageVars['script'] = '';
    $pageVars['css']    = 'style-form';
    
    $users = findSurveyBySubEmail('');  
    $countPages = calacPages(count($users));
    
    $pageVars['users'] = generateUsersList($users, $countPages, $pageIndex);
    $pageVars['pages'] = generatePages(count($users), $countPages);   
     
    echo buildLayout('userlist.html', $pageVars); 
