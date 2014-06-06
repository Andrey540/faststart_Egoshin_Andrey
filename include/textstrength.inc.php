<?php
  
    function calcCountPoints($arr)
    { 
        return 4 * count($arr);
    }
  
    function calcCountDigitPoints($arr)
    {
        $digitsCount = 0;
        for ($i = 0; $i < count($arr); $i++)
        {
            if (is_numeric($arr[$i]))
            {	  
                $digitsCount++; 
            }
        }		  
	  
        return 4 * $digitsCount;
    }
  
    function calcCountSymbolPoints($arr)
    {
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
   
    function calcCountUpperPoints($arr)
    {
        $upperSymbol = 0;
        for ($i = 0; $i < count($arr); $i++)
        {
            if ($arr[$i] >= 'A' && $arr[$i] <= 'Z')
            {	  
                $upperSymbol++;	  
            }
        }  
  
        return (count($arr) - $upperSymbol) * 2;
    }
  
    function calcCountLowerPoints($arr)
    {
        $lowerSymbol = 0;
        for ($i = 0; $i < count($arr); $i++)
        {
            if ($arr[$i] >= 'a' && $arr[$i] <= 'z')
            {	  
                $lowerSymbol++;	  
            }
        }  
  
        return (count($arr) - $lowerSymbol) * 2;
    }  
  
    function calcRepeatSymbols($arr)
    {
        $repeatMass = '';
    
        for ($i = 0; $i < count($arr); $i++)
        { 
            $repeat = 1;
	  
            // Подсчёт повторяющихся символов.
            if (empty($repeatMass[$arr[$i]]))
            {
                $repeatMass[$arr[$i]] = 0;
            }
            $repeatMass[$arr[$i]]++;
        } 
	  
        return calcCountRepeatPoints($repeatMass);
    }  
  
    function calcCountRepeatPoints($arr)
    {
        $repeats = 0;
        if (!empty($arr))
        {
            foreach($arr as $val)
            {
                if ($val != 1)
                    $repeats += $val;
            }
        }
	  
        return $repeats;
    }
	
	function checkWhiteSpaces($arr)
    {
        $result = true;
		foreach($arr as $val)
        {
            if ($val == ' ')
			{
                $result = false;
				break;
			}					
        }
		
        return $result;
    }
  
    function calcTextStrenght($text)
    {
        $arrChar = str_split($text);
   
        // Вычисляем надёжность.
        $strendth = calcCountPoints($arrChar);
        $strendth += calcCountDigitPoints($arrChar);
        $strendth += calcCountUpperPoints($arrChar);
        $strendth += calcCountLowerPoints($arrChar);
      
        if (calcCountDigitPoints($arrChar) == 0)
        {
            $strendth -= calcCountSymbolPoints($arrChar);
        
        }
        else if (calcCountSymbolPoints($arrChar) == 0)
        {
             $strendth -= calcCountDigitPoints($arrChar);        
        }
          
        $strendth -= calcRepeatSymbols($arrChar);
		
		if (!checkWhiteSpaces($arrChar))
			$strendth = 0;
          
        return $strendth;
    }
  
  
