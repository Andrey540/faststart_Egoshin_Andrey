<?
    const ID = "ID";
    const FISRT_NAME = "FirstName";
    const LAST_NAME = "LastName";
    const EMAIL = "Email";
    
    const SELF_HOST_APPLICATION_REQUEST_URL = "http://localhost:8081/api/user/";
    const DISPLAY_RESULT_URL = "http://127.0.0.1:55999/sign_up_success.php";
    
    $fisrtName = isset($_GET[FISRT_NAME]) ? $_GET[FISRT_NAME] : null;
    $lastName = isset($_GET[LAST_NAME]) ? $_GET[LAST_NAME] : null;
    $email = isset($_GET[EMAIL]) ? $_GET[EMAIL] : null;
    
    if (is_null($fisrtName) || is_null($lastName) || is_null($email))
    {
        die("Incorrect params");
    }
    
    $data = [
        ID => "0",
        FISRT_NAME => $fisrtName,
        LAST_NAME => $lastName,
        EMAIL => $email
    ];
    
    $ch = curl_init();
    curl_setopt($ch, CURLOPT_URL, SELF_HOST_APPLICATION_REQUEST_URL);
    curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
    curl_setopt($ch, CURLOPT_HEADER, false);
    curl_setopt($ch, CURLOPT_CUSTOMREQUEST, "PUT");
    curl_setopt($ch, CURLOPT_POSTFIELDS, http_build_query($data)); 
    
    $response = curl_exec($ch); 
    if(!$response)
    {
        die("Could not save data");;
    }
    echo $response;
    header("Location: " . DISPLAY_RESULT_URL . "?id=" . $response);
    die();