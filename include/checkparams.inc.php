<?php
    
    const MIN_PASSWORD_STRENGTH = 60;
    const MIN_YEAR = 1900;
    const MAX_YEAR = 2200;
    const MIN_MONTH = 1;
    const MAX_MONTH = 12;
    const MIN_DAY = 1;
    const MAX_DAY = 31;
    const MIN_SEX = 1;
    const MAX_SEX = 2;
	
    function calcCountNotSymbolChars($param)
    {
        $arr = str_split($param);
        $notSymbolCount = 0;
        for ($i = 0; $i < count($arr); $i++)
        {
            if ((is_numeric($arr[$i])) || (!ctype_alpha($arr[$i])))
            {	  
                $notSymbolCount++; 
            }
        }		  
	  
        return $notSymbolCount;
    }
  
    function calcCountSymbolChars($param)
    {
        $arr = str_split($param);
        $symbolsCount = 0;
        for ($i = 0; $i < count($arr); $i++)
        {
            if (!is_numeric($arr[$i]))
            {	  
                $symbolsCount++; 
            }
        }		  
	  
        return $symbolsCount;
    }
   
    function checkUpperChars($param)
    {
        $result = true;
        $arr = str_split($param);
        if (($arr[0] < 'A') || ($arr[0] > 'Z'))
            $result = false;
	  
        for ($i = 1; $i < count($arr); $i++)
        {
            // Подсчёт символов в врехнем и нижнем регистре.
            if (($arr[$i] < 'a') || ($arr[$i] > 'z'))
                $result = false;	  
        }  
  
        return $result;
    }
  
    function checkName($param, $name = 'first_name')
    {
        $result = true;
        if ((empty($param)) || (!checkUpperChars($param)))
            $result = false; 
	    
        return $result;
    }
  
    function checkAge($param)
    {
        $result = true;
      
        if ((empty($param)) || (calcCountSymbolChars($param) != 0))
            $result = false;		  
  
        return $result;
    }
  
    function checkEmail($param)
    {
        $result = true;
     	  
        $dog = strrpos($param, '@');
        $dot = strrpos($param, '.');	  
  
        if (($dog == 0) || ($dot == 0))
            $result = false;  	  
	  
        $arr = str_split($param);
	  
        for ($i = 0; $i < $dog; $i++)
        {
            if ((!ctype_alpha($arr[$i])) && (!is_numeric($arr[$i])))
            {
                $result = false;
                break;
            }	  
        }
	  
        for ($i = $dog + 1; $i < count($arr); $i++)
        {
            if (($i != $dot) && (!ctype_alpha($arr[$i])))
            {
                $result = false;
                break;
            }	  
        }
	    
        return $result;
    }
    
    function checkPassword($param)
    {
        return (calcTextStrenght($param) >= MIN_PASSWORD_STRENGTH);
    }
    
    function checkSex($param)
    {  
        return ($param != 0);
    }
    
    function checkMonth($param)
    {  
        return $param != 0;
    }
    
    function checkDay($param)
    {		  
        return $param != 0;
    }
    
    function checkYear($param)
    {  
        return $param != 0;
    }
    
    function checkUserParams($userInfo)
    {
        $result = ERROR_OK;
  
        if (!checkName($userInfo['first_name']))
        {
            $result = ERROR_FIRST_NAME;
        }
        else if (!checkName($userInfo['last_name']))
        {
            $result = ERROR_LAST_NAME;
        }
        else if (!checkPassword($userInfo['password']))
        {
            $result = ERROR_PASSWORD;
        }
        else if ($userInfo['email'] != $userInfo['re_email'])
        {
            $result = ERROR_EMAIL;
        }
        else if (!checkEmail($userInfo['email']))
        {
            $result = ERROR_EMAIL;
        }    
        else if (!checkSex($userInfo['sex']))
        {
            $result = ERROR_SEX;
        }    
        else if (!checkMonth($userInfo['month']))
        {
            $result = ERROR_MONTH;
        }    
        else if (!checkDay($userInfo['day']))
        {
            $result = ERROR_DAY;
        }    
        else if (!checkYear($userInfo['year']))
        {
            $result = ERROR_YEAR;
        }  
        return $result;   
    }
