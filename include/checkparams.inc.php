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
        $result = true;
      
        if (calcTextStrenght($param) < MIN_PASSWORD_STRENGTH)
            $result = false;		  
  
        return $result;
    }
    
    function checkSex($param)
    {
        $result = true;
      
        if (($param != 'Man') && ($param != 'Woman'))
            $result = false;		  
  
        return $result;
    }
    
    function checkMonth($param)
    {
        $result = false;
        
        $month = array('January', 'February', 'March', 'April', 'May', 'June',
					'July', 'August', 'September', 'October', 'November',
					'December');
                    
        foreach($month as $val)
        {
            if ($val == $param)
            {
                $result = true;
                break;
            }        
        }		  
  
        return $result;
    }
    
    function checkDay($param)
    {
        $result = false;        
      
        if (($param >= MIN_DAY) && ($param <= MAX_DAY))
            $result = true;		  
  
        return $result;
    }
    
    function checkYear($param)
    {
        $result = false;        
      
        if (($param >= MIN_YEAR) && ($param <= MAX_YEAR))
            $result = true;		  
  
        return $result;
    }
