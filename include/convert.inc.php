<?php
    
    function concatDate(&$vars)
    {
        $month = array('January' => 1, 'February' => 2, 'March' => 3, 'April' => 4,
                       'May' => 5, 'June' => 6, 'July' => 7, 'August' => 8, 'September' => 9,
                       'October' => 10, 'November' => 11, 'December' => 12);
                            
        $vars['birthday'] = $vars['year'] . '-' . $month[$vars['month']] .
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
        
        if (count($arrDate) == 3)
        {
            $vars['year']  = $arrDate[0];
            $vars['month'] = $arrDate[1];
            $vars['day']   = $arrDate[2];
        }
    } 
