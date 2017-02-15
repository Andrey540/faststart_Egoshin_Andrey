<?
    require "vendor/predis/predis/autoload.php";
    Predis\Autoloader::register();
    
    try
    {
        $redis = new Predis\Client();
    }
    catch (Exception $e)
    {
        die($e->getMessage());
    }

    const TASK_ID = "id";
    
    $id = isset($_GET[TASK_ID]) ? $_GET[TASK_ID] : null;    
    if (is_null($id))
    {
        die("Incorrect params");
    }
    
    $result = "";
    print("Please, wait...</br>");
    $counter = 0;
    while ((strlen($result) == 0) && ($counter < 5))
    {
        $result = $redis->get($id);
        sleep(1);
        ++$counter;
    }
    echo nl2br($result);
?>