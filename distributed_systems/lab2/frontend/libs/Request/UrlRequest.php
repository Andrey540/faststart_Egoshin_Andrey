<?

namespace Request;

class UrlRequest
{
    private $url;
    private $postVars = [];

    private $response;
    private $errorCode;
    private $timeout = null;
    private $method = null;

    public function __construct($url)
    {
        $this->url = $url;
    }

    public function getResponse()
    {
        return $this->response;
    }

    public function addFile($filePath, $mimeType = "")
    {
        // PHP 5.5 introduced a CurlFile object that deprecates the old @filename syntax
        // See: https://wiki.php.net/rfc/curl-file-upload
        $file = null;
        if (function_exists('curl_file_create'))
        {
            $file = curl_file_create($filePath, $mimeType);
        }

        $this->postVars["name"] = !is_null($file) ? $file : "@$filePath";
    }

    public function getErrorCode()
    {
        return $this->errorCode;
    }

    public function setMethod($method)
    {
        $this->method = $method;
    }

    public function setPostVars($postVars)
    {
        $this->postVars = array_merge($postVars, $this->postVars);
    }

    public function setTimeout($timeout)
    {
        $this->timeout = $timeout;
    }

    public function getPostVars()
    {
        return $this->postVars;
    }

    public function setUrl($url)
    {
        $this->url = $url;
    }

    public function getUrl()
    {
        return $this->url;
    }

    public function send()
    {
        for ($i = 0; $i < \Util\RequestUtil::COUNT_TRIES; ++$i)
        {
            $this->executeSend();

            if (!$this->errorCode)
            {
                break;
            }
            else
            {
                $this->writeErrorLog();
            }
        }

        return $this->response;
    }

    private function writeErrorLog()
    {
        $logFile = LOG_DIR . "/url_request_errors.log";

        $errorMessage = "UrlRequest error!\n
                url: {$this->url}\n
                post vars: " . var_export($this->postVars, true) . "\n
                error code: {$this->errorCode}\n
                response: {$this->response}";

        \Logger::log($logFile, $errorMessage);
    }

    private function executeSend()
    {
        $timeout = ($this->timeout) ? $this->timeout : \Util\RequestUtil::LOAD_TIMEOUT;

        $curl = curl_init();
        curl_setopt($curl, CURLOPT_URL, $this->url);
        curl_setopt($curl, CURLOPT_HEADER, 1);

        curl_setopt($curl, CURLOPT_FOLLOWLOCATION, 0);
        curl_setopt($curl, CURLOPT_RETURNTRANSFER, 1);
        curl_setopt($curl, CURLOPT_TIMEOUT, $timeout);

        $curlCheckSsl = \Util\EnvironmentMode::isProdEnv() ? 2 : 0;
        curl_setopt($curl, CURLOPT_SSL_VERIFYPEER, $curlCheckSsl);
        curl_setopt($curl, CURLOPT_SSL_VERIFYHOST, $curlCheckSsl);

        if (!empty($this->postVars))
        {
            curl_setopt($curl, CURLOPT_POST, 1);
            curl_setopt($curl, CURLOPT_POSTFIELDS, http_build_query($this->postVars));
        }
        if ($this->method == HttpMethods::HEAD)
        {
            curl_setopt($curl, CURLOPT_NOBODY, 1);
        }

        $this->response = curl_exec($curl);
        $this->errorCode = curl_errno($curl);

        curl_close($curl);
    }
}