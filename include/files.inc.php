<?php
   
    function findFilteredFiles($email, $extension = '')
    {
        $query = "SELECT files.`file_id`, users.`email`, files.`name`, files.`extension`  FROM files, users WHERE 
                    files.`extension` LIKE '%" . dbQuote($extension) . "%' AND users.`email` LIKE '%"
                     . dbQuote($email) . "%' AND users.`user_id` =  files.`user_id`";
        return dbQueryGetResult($query);   
    }
    
    function saveFileInfo(&$fileInfo)
    {
        $result = false;
        
        $query = "INSERT INTO files SET user_id='"       . $fileInfo['user_id'] . 
                                        "', name='"      . $fileInfo['name'] . 
                                        "', extension='" . $fileInfo['extension'] . "'";

        if (dbQuery($query))
        {
            $fileInfo['file_id'] = dbGetLastInsertId(); 
            $result = true;            
        }
        
        return $result;
    }
    
    function saveUserInfoToFile($userInfo, $fileName)
    { 
        $success = false;
    
        if ( !file_exists( $fileName ) )
        {
            $file = fopen($fileName, "w");
            if ($file)
            {        
                $info = '';
                foreach($userInfo as $key => $val)
                {
                    if ($key != 're_email')
                        $info .= trim($val) . ' ';
                }
                fwrite($file, $info);  
                fclose($file);
        
                $success = true;
            }
        }
    
        return $success;
    }

    function readUserInfoFromFile($fileName)
    {   
        $userInfo = array();
        if ( file_exists( $fileName ) )
        {
            $file = fopen($fileName, "r");
            if ($file)
            {
                $line = fgets($file); 
                list($userInfo['first_name'], $userInfo['last_name'], $userInfo['email'], $userInfo['password'],
                                $userInfo['sex'], $userInfo['month'], $userInfo['day'], $userInfo['year']) = preg_split("[ ]", $line, 8);
                fclose($file); 
            }
        }
    
        return $userInfo;
    }