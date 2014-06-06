<?php
    function addNewUser($userInfo, &$message)
    {
        $checkInfo = findSurveyByEmail($userInfo['email']);
        
        if (empty($checkInfo))
        {
            concatDate(&$userInfo); 
                                
            if (!saveSurveyInfo($userInfo))
            {
                $message = 'can not sign up!';
            }
        }
        else
        {
            $message = 'this e-mail is already exist!';
        }
    }
    