<?php
class File
{
    const FILE_DIRECTORY = "uploads/";
    private $name;
    
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
    
    public function upload($filePath)
    {
        $result = false;            
        $finalPath = File::FILE_DIRECTORY . $this->name;
        if (move_uploaded_file($filePath, $finalPath))
        {      
                $result = true;
        }      
    
        return $result;
    }
    
    public function delete()
    {           
        $result = false;
        $finalPath = File::FILE_DIRECTORY . $this->name;
        if (file_exists($finalPath))
        {
            $result = unlink($finalPath);
        }
        return $result;
    }
}