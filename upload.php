<?php
    require_once('include/common.inc.php');
    
    if (!userAuthorized())
    {
        exit();        
    }
    
    $fileSave = getUserInfoFromRequest(GET_FROM_FILE);
  
    $pageVars = array();
    $pageVars['title']   = 'Upload file';
    $pageVars['header']  = 'Upload file';
    $pageVars['action']  = 'upload.php';
    $pageVars['success'] = 'Error: ';
    $pageVars['script']  = '';
    $pageVars['css']     = 'style-form';
    
    $message = 'can not upload file!';

    if (($fileSave['data_file']['error'] == 0) && ($_SESSION['user_id'] != ''))
    {        
        if (uploadFile($fileSave['data_file']))
        {      
            $message = 'your file was uploaded!';      
            $pageVars['success'] = 'Success: '; 
        }        
    }
    
    $pageVars['message'] = $message;
    
    echo buildLayout('answer.html', $pageVars); 