<?php
    require_once('include/common.inc.php');
    
    $change = getUserInfoFromRequest(GET_FROM_POST);
    
    if ($change['action'] == 1)
    {
        if (changeFileRate($change['file_id'], $change['user_id'], 1))
            $change['rate']++;
    }
    else if ($change['action'] == -1)
    {
        if ($change['rate'] > 0)
        {    
            if (changeFileRate($change['file_id'], $change['user_id'], -1))
                $change['rate']--;
        }
    }
    
    $response = array('file_id' => $change['file_id'],
                      'rate'    => $change['rate']);    
    
    echo json_encode($response);