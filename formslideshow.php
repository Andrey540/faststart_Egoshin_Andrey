<?php
	require_once('include/common.inc.php');
    
    if (!userAuthorized())
    {
        exit();        
    }
    
    $pageVars = array();
    $pageVars['title']  = 'Slide Show';
    $pageVars['header'] = 'Slide Show';
    $pageVars['script'] = '<script type="text/javascript" src="js/slideshow.js" /></script>';
    $pageVars['css']    = 'slideshow';
    
    echo buildLayout('slideshow.html', $pageVars);
    

