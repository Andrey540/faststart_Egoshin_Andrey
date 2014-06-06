<?php

function getParameterFromPost($value, $defaultValue = '')
{
    $param = isset($_POST[$value]) ? $_POST[$value] : $defaultValue;  

    return $param;
}

function getParameterFromGet($value, $defaultValue = '')
{
    $param = isset($_GET[$value]) ? $_GET[$value] : $defaultValue;  

    return $param;
}

function getFileParameter($value, $defaultValue = '')
{
    $param = isset($_FILES[$value]) ? $_FILES[$value] : $defaultValue;  

    return $param;
}