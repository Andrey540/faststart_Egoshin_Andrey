<?php
   
    function findFilteredFiles($email, $extension = '')
    {
        $query = "SELECT files.`file_id`, users.`email`, files.`name`, files.`extension`  FROM files, users WHERE 
                    files.`extension` LIKE '%" . dbQuote($extension) . "%' AND users.`email` LIKE '%"
                     . dbQuote($email) . "%' AND users.`user_id` =  files.`user_id`";
        return dbQueryGetResult($query);   
    }
    
    function findImages($extension = 'jpg')
    {
        $query = "SELECT files.`file_id`, files.`extension`  FROM files WHERE 
                    files.`extension` LIKE '%" . dbQuote($extension) . "%'";
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
    
    function uploadFile($fileInfo)
    {
        $result = false;    
        
        $arrWords = explode(".", $fileInfo['name']);
      
        if (!empty($arrWords))
        {      
            $fileInfo['user_id']   = $_SESSION['user_id'];
            $fileInfo['name']      = str_replace('.' . $arrWords[count($arrWords) - 1], '', $fileInfo['name']);
            $fileInfo['extension'] = $arrWords[count($arrWords) - 1];
      
            if (saveFileInfo(&$fileInfo))
            {
                $finalPath = 'uploads/' . $fileInfo['file_id'] . '.' . $fileInfo['extension'];
                if (move_uploaded_file($fileInfo['tmp_name'], $finalPath))
                {      
                    $result = true;
                }      
            } 
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
    
    function emptyFile($file)
    {
        return !(($file['data_file'] != '') && ($file['data_file']['error'] == 0));    
    }