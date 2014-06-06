<?php

function setYearSelect($start, $end)
{ 
	if ($start < 1900)
		$start = 1900;
	if ($end > 2200)
		$end = 2200;
	if ($start > $end)
		$start = $end;
    $option = '';
	for($i = $start; $i <= $end; $i++)
		$option .= '<option>' . $i . '</option>';
    return $option;
}

function setMonthSelect($start, $end)
{ 
	if ($start < 1)
		$start = 1;
	if ($end > 12)
		$end = 12;
	if ($start > $end)
		$start = $end;
	$month = array('', 'January', 'February', 'March', 'April', 'May', 'June',
					'July', 'August', 'September', 'October', 'November',
					'December');
    $option = '';
	for($i = $start; $i <= $end; $i++)
		$option .= '<option>' . $month[$i] . '</option>';
    return $option;
}

function setDaySelect($start, $end)
{ 
	if ($start < 1)
		$start = 1;
	if ($end > 31)
		$end = 31;
	if ($start > $end)
		$start = $end;
    $option = '';
	for($i = $start; $i <= $end; $i++)
		$option .= '<option>' . $i . '</option>';
    return $option;
}

function setSexSelect($start, $end)
{ 
	if ($start < 1)
		$start = 1;
	if ($end > 2)
		$end = 2;
	if ($start > $end)
		$start = $end;
	$sex = array('', 'Man', 'Woman');
    $option = '';
	for($i = $start; $i <= $end; $i++)
		$option .= '<option>' . $sex[$i] . '</option>';
    return $option;
}
