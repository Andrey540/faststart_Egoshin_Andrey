<?php
	require_once('include/common.inc.php');
    
    if (!userAuthorized())
    {
        exit();        
    }
    
    $find = getUserInfoFromRequest(GET_FROM_POST);
    
    $files = findFilteredFiles($find['email'], $find['extension']);
    
    $pageVars = array();
    $pageVars['title']      = "File Collection";
    $pageVars['header']     = "File Collection";
    $pageVars['css']        = 'filterfiles';
    $pageVars['action']     = "filterfiles.php"; 
    $pageVars['user_id']    = $_SESSION['user_id'];   
    $pageVars['email']      = $find['email'];
    $pageVars['extension']  = $find['extension'];
    $pageVars['script']     = '<script type="text/javascript" src="js/filterfiles.js" /></script>';

    $file = array();

    foreach($files as $value)
    {
        $result = takeFileRate($value['file_id']);
        $rate = DEFAULT_RATE + $result[0]["SUM(`rate`)"];
        $list = array(
                      array('file'      => $value['email'] . ' - ' . $value['name'] . '.' . $value['extension'],
                            'file_id'   => $value['file_id'],
                            'file_rate' => $rate)                        
                     );
                    
        $file = array_merge($file, $list);        
    }
        
    $pageVars['file'] = $file; 
    
    echo buildLayout('filelist.html', $pageVars); 
