<?php
class File
{
    private $name;
    private $tmpName;
    
    static function getUploadedFiles()
    {
        $result = "";
        $dir = "uploads/";  
        if(is_dir($dir))
        { 
            $result = scandir($dir); 
            array_shift($result); 
            array_shift($result); 
        }
        return $result;
    }
    
    public function __construct()
    {
        $this->name = "";
        $this->tmpName = "";
    }
    
    public function setName($name)
    {
        $this->name = $name;
    }
    
    public function getName()
    {
        return $this->name;
    }
    
    public function setTmpName($tmpName)
    {
        $this->tmpName = $tmpName;
    }
    
    public function getTmpName()
    {
        return $this->tmpName;
    }
    
    public function upload()
    {
        $result = false;            
        $finalPath = 'uploads/' . $this->name;
        if (move_uploaded_file($this->tmpName, $finalPath))
        {      
                $result = true;
        }      
    
        return $result;
    }
    
    public function delete()
    {           
        $result = false;
        $finalPath = 'uploads/' . $this->name;
        if (file_exists($finalPath))
        {
            $result = unlink($finalPath);
        }
        return $result;
    }
}