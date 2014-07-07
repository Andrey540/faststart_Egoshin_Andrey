<?php

class defaultActions extends sfActions
{
    public function executeIndex(sfWebRequest $request)
    {
        return $this->renderText("Hello, symfony!");    
    }
    
    public function executeHelloSarah(sfWebRequest $request)
    {
        $this->firstName = "Sarah";    
    } 
    
    public function executeSaveCar(sfWebRequest $request)
    {
        $manufacture = $request->getParameter('manufacture');  
        $model       = $request->getParameter('model');
        $year        = $request->getParameter('year'); 

        $car = new Car();
        $car->setManufacture($manufacture);
        $car->setModel($model);
        $car->setYear($year);
        
        $car->save();
        
        return sfView::NONE;
    } 
    
    public function executeReadCar(sfWebRequest $request)
    {        
        $car = new Car();
        $cars = $car->findByModel("bmw6");
        $this->renderText($cars[0]->getManufacture());
    } 
    
    public function executeUploadForm(sfWebRequest $request)
    {
        $this->header = "Upload File";
        $this->action = "upload_file";    
    }     
    
    public function executeUploadFile(sfWebRequest $request)
    {
        $this->header = "Upload File";
        $this->success = "your file was uploaded successfully!";  

        $data = $request->getFiles('data_file');
        $file = new File();
        
        $file->setName($data['name']);
        
        if (!$file->upload($data['tmp_name']))
        {
            $this->success = "your file can not be uploaded!";            
        }
        else
        {
            $_SESSION['file'] = $data['name'];
        }
    } 
    
    public function executeGetFiles(sfWebRequest $request)
    {
        $this->header = "Show Files";
        $this->files = File::getUploadedFiles();
    }  
    
    public function executeDeleteFile(sfWebRequest $request)
    {
        $this->header = "Delete File";
        $this->success = "file was delete successfully!";  

        $data = $request->getParameter('file');
        $file = new File();
        
        $file->setName($data);
        
        $this->renderText($data);
        
        if (!$file->delete())
        {
            $this->success = "file can not be deleted!";            
        }
        else
        {
            session_unset();
        }
    } 
    
    public function executeDeleteForm(sfWebRequest $request)
    {
        $this->header   = "Delete File";
        $this->action   = "delete_file";         
        $this->fileName = "";
        
        if (!empty($_SESSION['file']))
        {
            $this->fileName = $_SESSION['file'];
        }
    } 
}