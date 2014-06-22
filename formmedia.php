<?php
    require_once('include/common.inc.php');
    
    if (!userAuthorized())
    {
        exit();        
    }
    
    $media = getUserInfoFromRequest(GET_FROM_GET);
  
    $pageVars = array();
    
    $pageVars['title']   = 'Media';
    $pageVars['header']  = 'Media';    
    $pageVars['css']     = 'media';
    $pageVars['script']  = '<script type="text/javascript" src="js/media.js" /></script>';;
    $pageVars['video']   = $media['video'];
    $pageVars['audio']   = $media['audio'];

    if ($pageVars['video'] != '')
    {
        echo buildLayout('video.html', $pageVars);
    }
    else if ($pageVars['audio'] != '')
    {
        echo buildLayout('audio.html', $pageVars);
    } 
     