<?php
    
    function buildLayout($tplName, $pageVars)
    {
        $html  = getView('header.html', $pageVars);
        $html .= getView($tplName, $pageVars);
        $html .= getView('footer.html', $pageVars);
        
        return $html;
    }  
