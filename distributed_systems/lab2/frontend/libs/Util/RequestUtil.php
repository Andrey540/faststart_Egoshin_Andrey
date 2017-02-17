<?
namespace Util;

class RequestUtil
{
    const LOAD_TIMEOUT = 20;
    const COUNT_TRIES = 3;

    const SUCCESS_STATUS               = 200;
    const REDIRECTED_STATUS            = 302;
    const INVALID_REQUEST_STATUS       = 400;
    const UNAUTHORIZED_STATUS          = 401;
    const AUTHORIZATION_ERROR_STATUS   = 403;
    const NOT_FOUND_STATUS             = 404;
    const INTERNAL_SERVER_ERROR_STATUS = 500;

    /**
     * Tries to get url contents.
     * Returns content of url on success or null on error.
     *
     * @param \Request\UrlRequest $urlRequest
     * @param null $headers
     * @return string
     */
    public static function getUrlContents(\Request\UrlRequest $urlRequest, &$headers = null)
    {
        $response = $urlRequest->send();
        $errorCode = $urlRequest->getErrorCode();

        if ($errorCode)
        {
            return null;
        }

        $contents = self::getContentByResponse($response, $headers);
        return $contents;
    }

    /**
     * Parses header and returns status as int.
     *
     * @param string $header
     * @return int
     */
    public static function parseHttpStatus($header)
    {
        preg_match('|HTTP/\d\.\d\s+(\d+)\s+.*|',$header,$match);
        return intval( $match[1] );
    }

    private static function getContentByResponse($response, &$headers = null)
    {
        $headerAndContents = preg_split("/(?:\r\n){2}/", $response, 2);
        $headers = explode("\r\n", $headerAndContents[0]);

        while (self::parseHttpStatus( $headers[0] ) == 100)
        {
            $response = str_replace("HTTP/1.1 100 Continue\r\n\r\n", "", $response);
            $headerAndContents = preg_split("/(?:\r\n){2}/", $response, 2);
            $headers = explode("\r\n", $headerAndContents[0]);
        }

        $contents = "";
        if (isset($headerAndContents[1]))
        {
            $contents = $headerAndContents[1];
        }
        return $contents;
    }
}