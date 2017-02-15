<?
    require "vendor/predis/predis/autoload.php";
    Predis\Autoloader::register();
    
    const SELF_HOST_APPLICATION_REQUEST_URL = "http://localhost:8081/api/poem/";
    const RESULT_URL = "http://127.0.0.1:55999/best_line_selector.php";
    
    try
    {
        $redis = new Predis\Client();
    }
    catch (Exception $e)
    {
        die($e->getMessage());
    }

    const MAX_TASK_ID_KEY = "max_task_id";
    const TEXT_FIELD = "poem";
    const POEM_TASK_ID = "TaskId";
    const POEM_TEXT = "Text";
    const TASK_ID_PREFIX = "task_";

    $maxTaskId = $redis->get(MAX_TASK_ID_KEY);
    $maxTaskId = intval($maxTaskId);
    
    $taskId = TASK_ID_PREFIX . $maxTaskId;
    
    $text = isset($_GET[TEXT_FIELD]) ? $_GET[TEXT_FIELD] : null;    
    if (is_null($text) || strlen($text) == 0)
    {
        die("Incorrect params");
    }
    
    $redis->set(MAX_TASK_ID_KEY, ++$maxTaskId);

    $data = [
        POEM_TASK_ID => $taskId,
        POEM_TEXT => $text
    ];
   
    $ch = curl_init();
    curl_setopt($ch, CURLOPT_URL, SELF_HOST_APPLICATION_REQUEST_URL);
    curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
    curl_setopt($ch, CURLOPT_HEADER, false);
    curl_setopt($ch, CURLOPT_CUSTOMREQUEST, "POST"); 
    curl_setopt($ch, CURLOPT_POSTFIELDS, http_build_query($data));    
    
    $result = curl_exec($ch);
    
    header("Location: " . RESULT_URL . "?id=" . $taskId);
    die();
?>