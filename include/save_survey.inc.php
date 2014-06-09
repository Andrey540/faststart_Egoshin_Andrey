<?php
    function addNewUser($userInfo)
    {
        $result = ERROR_OK;
        $checkInfo = findSurveyByEmail($userInfo['email']);
        
        if (empty($checkInfo))
        {
            concatDate(&$userInfo); 
                                
            if (!saveSurveyInfo($userInfo))
            {                
                $result = ERROR_ADD_USER;
            }
        }
        else
        {            
            $result = ERROR_EMAIL_EXIST;
        }
        return $result;
    }
    