<?php

    const NORMAL_DATE_LENGTH = 3;
    
    function concatDate(&$vars)
    {
        $year = range(MIN_YEAR, MAX_YEAR);
                            
        $vars['birthday'] = $year[$vars['year'] - 1] . '-' . $vars['month'] .
                                '-' . $vars['day']; 
    }  
    
    function parseDate(&$vars)
    {       
        $vars['year'] = '0000';
        $vars['month'] = '0000';
        $vars['day'] = '0000';
        $month = array('01' => 'January', '02' => 'February', '03' => 'March', '04' => 'April',
                       '05' => 'May', '06' => 'June', '07' => 'July', '08' => 'August', '09' => 'September',
                       '10' => 'October', '11' => 'November', '12' => 'December');
                       
        $arrDate = explode("-", $vars['birthday']);
        
        if (count($arrDate) == NORMAL_DATE_LENGTH)
        {
            $vars['year']  = $arrDate[0];
            $vars['month'] = $arrDate[1];
            $vars['day']   = $arrDate[2];
        }
    } 
