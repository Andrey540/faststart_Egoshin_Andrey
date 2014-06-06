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
        $fileInfo =  $fileSave['data_file'];
        $arrWords = explode(".", $fileInfo['name']);
      
        if (!empty($arrWords))
        {      
            $fileInfo['user_id']   = $_SESSION['user_id'];
            $fileInfo['name']      = $arrWords[count($arrWords) - 2];
            $fileInfo['extension'] = $arrWords[count($arrWords) - 1];
      
            if (saveFileInfo(&$fileInfo))
            {
                $finalPath = 'uploads/' . $fileInfo['file_id'] . '.' . $fileInfo['extension'];
                if (move_uploaded_file($fileInfo['tmp_name'], $finalPath))
                {      
                    $message = 'your file was uploaded!';      
                    $pageVars['success'] = 'Success: '; 
                }      
            } 
        }        
    }
    
    $pageVars['message'] = $message;
    
    echo buildLayout('answer.html', $pageVars); 