<?php    
   
    function takeFileRate($fileId)
    {
        $query = "SELECT SUM(`rate`)  FROM rate WHERE `file_id` LIKE '" . dbQuote($fileId) . "'";
        return dbQueryGetResult($query);   
    }
    
    function addRate($fileId, $userId, $rate)
    {
        $query = "INSERT INTO rate SET file_id='" . dbQuote($fileId) . 
                                   "', user_id='" . dbQuote($userId) . 
                                   "', rate='"    . dbQuote($rate)   . "'";
        return dbQuery($query);   
    } 
    
    function updateRate($fileId, $userId, $rate)
    {
        $query = "UPDATE rate SET `rate`='" . dbQuote($rate)   . 
                        "' WHERE `user_id`='" . dbQuote($userId) . 
                        "' AND `file_id`='"   . dbQuote($fileId) . "'";
        return dbQuery($query);   
    }
    
    function findExistRate($fileId, $userId)
    {
        $query = "SELECT `rate` FROM rate WHERE file_id LIKE '" . dbQuote($fileId) . "' AND
                                                user_id LIKE '" . dbQuote($userId) . "'";
        return dbQueryGetResult($query);   
    }    
    
    function changeFileRate($fileId, $userId, $action)
    {        
        $result = false;
        $checkInfo = findExistRate($fileId, $userId);  
        if (empty($checkInfo))
        {
            addRate($fileId, $userId, $action);
            $result = true;
        }
        else
        {       
            if ($checkInfo[0]['rate'] == 0)
            {
                updateRate($fileId, $userId, $action);
                $result = true;
            }
            else if (($checkInfo[0]['rate'] == 1) && ($action == -1)) 
            {            
                updateRate($fileId, $userId, 0);
                $result = true;
            }
            else if (($checkInfo[0]['rate'] == -1) && ($action == 1))
            {
                updateRate($fileId, $userId, 0); 
                $result = true;
            }        
        } 
        return $result;
    }