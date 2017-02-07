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
    
    const ID = "id";
    const USERS_KEY_PREFIX = "users_";
    
    $id = isset($_GET[ID]) ? $_GET[ID] : null;    
    if (is_null($id))
    {
        die("Incorrect params");
    }

    $userInfo = $redis->get(USERS_KEY_PREFIX . $id);   
    var_export(json_decode($userInfo, true));    
?>