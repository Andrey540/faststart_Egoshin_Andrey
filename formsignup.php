<?php
	require_once('include/common.inc.php');
    
    $pageVars = array();
    $pageVars['title']  = 'Sign Up';
    $pageVars['header'] = 'Sign Up';
    $pageVars['action'] = 'signup.php';
    $pageVars['sex']    =  array('Select Sex:', 'Man', 'Woman');
                                
    $pageVars['month']  =  array('Month:', 'January', 'February', 'March', 'April', 'May', 'June',
                                'July', 'August', 'September', 'October', 'November',
                                'December');
                                  
    $pageVars['day']    =  array('Day:');
    $pageVars['day']    =  array_merge($pageVars['day'], range(MIN_DAY, MAX_DAY));
    $pageVars['year']   =  array('Yaer:');
    $pageVars['year']   =  array_merge($pageVars['year'], range(MIN_YEAR, MAX_YEAR));
    $pageVars['script'] = '<script type="text/javascript" src="js/signup.js" /></script>';
    $pageVars['css']    = 'style-form';
    
    echo buildLayout('signup.html', $pageVars);
    

