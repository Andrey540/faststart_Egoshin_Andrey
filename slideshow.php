<?php
    require_once('include/common.inc.php');
    
    if (!userAuthorized())
    {
        exit();        
    }
    
    $image = getUserInfoFromRequest(GET_FROM_POST);
    
   // if (empty($image['image']))
   //     die();
        
    $files = array();
    $extensions = array("png", "jpg", "bmp", "gif");

    foreach($extensions as $val)
    {
        $files = array_merge($files, findImages($val));
    } 
    
    if ($image['image'] > count($files))
        $image['image'] = 1;
    else if ($image['image'] == 0)
        $image['image'] = count($files);
    
    $response = array('image'  => $files[$image['image'] - 1],
                      'number' => $image['image']);
        
    echo json_encode($response);