<?php

function setYearSelect($start, $end)
{ 
	if ($start < MIN_YEAR)
		$start = MIN_YEAR;
	if ($end > MAX_YEAR)
		$end = MAX_YEAR;
	if ($start > $end)
		$start = $end;
    $option = '';
	for($i = $start; $i <= $end; $i++)
		$option .= '<option>' . $i . '</option>';
    return $option;
}

function setMonthSelect($start, $end)
{ 
	if ($start < MIN_MONTH)
		$start = MIN_MONTH;
	if ($end > MAX_MONTH)
		$end = MAX_MONTH;
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
	if ($start < MIN_DAY)
		$start = MIN_DAY;
	if ($end > MAX_DAY)
		$end = MAX_DAY;
	if ($start > $end)
		$start = $end;
    $option = '';
	for($i = $start; $i <= $end; $i++)
		$option .= '<option>' . $i . '</option>';
    return $option;
}

function setSexSelect($start, $end)
{ 
	if ($start < MIN_SEX)
		$start = MIN_SEX;
	if ($end > MAX_SEX)
		$end = MAX_SEX;
	if ($start > $end)
		$start = $end;
	$sex = array('', 'Man', 'Woman');
    $option = '';
	for($i = $start; $i <= $end; $i++)
		$option .= '<option>' . $sex[$i] . '</option>';
    return $option;
}
