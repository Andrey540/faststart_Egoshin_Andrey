<?php
    require_once('include/common.inc.php');
    
    const RATE_INCREMENT = 1;
    const RATE_DECREMENT = -1;
    
    $change = getUserInfoFromRequest(GET_FROM_POST);
    
    if ($change['action'] == RATE_INCREMENT)
    {
        if (changeFileRate($change['file_id'], $change['user_id'], RATE_INCREMENT))
            $change['rate']++;
    }
    else if ($change['action'] == RATE_DECREMENT)
    {
        if ($change['rate'] > 0)
        {    
            if (changeFileRate($change['file_id'], $change['user_id'], RATE_DECREMENT))
                $change['rate']--;
        }
    }
    
    $response = array('file_id' => $change['file_id'],
                      'rate'    => $change['rate']);    
    
    echo json_encode($response);