<?
    const FISRT_NAME = "first_name";
    const LAST_NAME = "last_name";
    const EMAIL = "email";
    
    $fisrtName = isset($_GET[FISRT_NAME]) ? $_GET[FISRT_NAME] : null;
    $lastName = isset($_GET[LAST_NAME]) ? $_GET[LAST_NAME] : null;
    $email = isset($_GET[EMAIL]) ? $_GET[EMAIL] : null;
    
    if (is_null($fisrtName) || is_null($lastName) || is_null($email))
    {
        die("Incorrect params");
    }
    
    $url = "http://localhost:8081/api/user/?firstName=" . $fisrtName . "&lastName=" . $lastName . "&Email=" . $email;
    $data = [
        $fisrtName,
        $lastName,
        $email
    ];
    
    $ch = curl_init();

    curl_setopt($ch, CURLOPT_URL, $url);
    curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
    curl_setopt($ch, CURLOPT_HEADER, false);
    curl_setopt($ch, CURLOPT_CUSTOMREQUEST, "PUT"); 
    curl_setopt($ch, CURLOPT_POSTFIELDS,http_build_query($data));    
    
    $response = curl_exec($ch); 
    if(!$response)
    {
        die("Could not save data");;
    }
    header("Location: " . "http://127.0.0.1:55999/sign_up_success.php?id=" . $response);
    die();
?>