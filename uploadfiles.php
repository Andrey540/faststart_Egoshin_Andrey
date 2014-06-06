<?php
	require_once('include/common.inc.php');
    
    if (!userAuthorized())
    {
        exit();        
    }
    
    $pageVars = array();
    $pageVars['title']  = 'Upload file';
    $pageVars['header'] = 'Upload file';
    $pageVars['css']    = 'style-form';
    $pageVars['script'] = '';
    $pageVars['action']  = 'upload.php';
    
    echo buildLayout('uploadsfiles.html', $pageVars); 