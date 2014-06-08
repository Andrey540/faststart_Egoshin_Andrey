<?php
    function addNewUser($userInfo)
    {
        $result = 0;
        $checkInfo = findSurveyByEmail($userInfo['email']);
        
        if (empty($checkInfo))
        {
            concatDate(&$userInfo); 
                                
            if (!saveSurveyInfo($userInfo))
            {                
                $result = -1;
            }
        }
        else
        {            
            $result = -2;
        }
        return $result;
    }
    