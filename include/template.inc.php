<?php
    
    function getView1($templateName, $vars = array())
    {
        $templatePath = TEMPLATE_DIR . '/' . $templateName;

        $content = file_get_contents($templatePath);
        if (!empty($vars))
        {
            foreach($vars as $placeholder => $value)
            {
                $key = '{' . $placeholder . '}';
                $content = str_replace($key, $value, $content);            
            }        
        }
        return $content;
    }  
    
    function getView($templateName, $vars = array())
    {
        $smarty = new Smarty();
        $smarty->template_dir = TEMPLATE_DIR;
        $smarty->compile_dir = TEMPLATE_COMPILED_DIR;
        
        $smarty->assign($vars);
        
        return $smarty->fetch($templateName);        
    } 
