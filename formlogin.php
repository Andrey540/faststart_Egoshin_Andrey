<?php
	require_once('include/common.inc.php');
    
    $pageVars = array();
    $pageVars['title']   = 'Log In';
    $pageVars['header']  = 'Log In';
    $pageVars['action']  = 'login.php';
    $pageVars['script']  = '';
    $pageVars['css']     = 'login';
    
    echo buildLayout('login.html', $pageVars);
    

