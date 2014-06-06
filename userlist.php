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
    
    $pages = array();
    
    $countPages = (count($users) / COUNT_SHOW_USERS);
    if ((count($users) % COUNT_SHOW_USERS) != 0)
        $countPages++;   
            
    if ($countPages >= 2)
    {    
        for ($i = 1; $i <= $countPages; $i++)
        {
            $pages[] = $i;    
        }
    }
    
    if ($pageIndex == '')
        $pageIndex = 1;
    else if ($pageIndex > $countPages)
        $pageIndex = $countPages;
    
    $startIndex = ($pageIndex - 1) * COUNT_SHOW_USERS;
    $endIndex   = $pageIndex * COUNT_SHOW_USERS;
    
    if ($endIndex > count($users))
        $endIndex = count($users);         
    
    $usersList = array();
   
    for ($i = $startIndex; $i < $endIndex; $i++)
    {
        $list = array(
                      array('user_id' => $users[$i]['user_id'],
                            'email'   => $users[$i]['email'] . ' - ',
                            'name'    => $users[$i]['first_name'] . ' ' . $users[$i]['last_name'])
                      );
                      
        $usersList = array_merge($usersList, $list);
    }
    
    $pageVars['users'] = $usersList;
    $pageVars['pages'] = $pages;   
     
    echo buildLayout('userlist.html', $pageVars); 
