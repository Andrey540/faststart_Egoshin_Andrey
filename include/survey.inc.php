<?php
    
    function saveSurveyInfo(&$surveyInfo)
    {
        $result = false;
        
        $query = "INSERT INTO users SET first_name='"    . dbQuote($surveyInfo['first_name']) . 
                                        "', last_name='" . dbQuote($surveyInfo['last_name']) . 
                                        "', password='"  . dbQuote($surveyInfo['password']) . 
                                        "', email='"     . dbQuote($surveyInfo['email']) . 
                                        "', birthday='"  . dbQuote($surveyInfo['birthday']) . 
                                        "', sex='"       . dbQuote($surveyInfo['sex']) . "'";
        if (dbQuery($query))
        {
            $surveyInfo['user_id'] = dbGetLastInsertId(); 
            $result = true;            
        }
        
        return $result;
    }  
    
    function findSurveyByEmail($email)
    {
        $query = "SELECT * FROM users WHERE email LIKE '" . dbQuote($email) . "'";
        return dbQueryGetResult($query);   
    }
    
    function findSurveyByEmailAndPass($email, $pass)
    {
        $query = "SELECT * FROM users WHERE email LIKE '" . dbQuote($email) . 
                                  "' AND password LIKE '" . dbQuote($pass) . "'";
        return dbQueryGetResult($query);   
    }
    
    function findSurveyById($user_id)
    {
        $query = "SELECT * FROM users WHERE user_id LIKE '" . dbQuote($user_id) . "'";
        return dbQueryGetResult($query);   
    }
    
    function findSurveyBySubEmail($email)
    {
        $query = "SELECT * FROM users WHERE email LIKE '%" . dbQuote($email) . "%'";
        return dbQueryGetResult($query);   
    }