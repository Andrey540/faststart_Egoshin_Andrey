<?php

function calacPages($users)
{
    $countPages = ($users / COUNT_SHOW_USERS);
    if ((count($users) % COUNT_SHOW_USERS) != 0)
        $countPages++; 
    return $countPages;
}

function generatePages($users, $countPages)
{ 
    $pages = array();
         
    if ($countPages >= 2)
    {    
        for ($i = 1; $i <= $countPages; $i++)
        {
            $pages[] = $i;    
        }
    }
    
    return $pages;
}

function generateUsersList($users, $countPages, $pageIndex)
{ 
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
    
    return $usersList;
}
