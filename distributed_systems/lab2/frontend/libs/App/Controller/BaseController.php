<?php

namespace App\Controller;

use Interop\Container\ContainerInterface;
use Slim\Http\Request;
use Slim\Http\Response;

abstract class BaseController
{
    /** @var ContainerInterface  */
    protected $container = null;

    /** @var \Slim\Views\Twig */
    protected $view = null;
    /** @var \SlimSession\Session  */
    protected $session = null;
    /** @var \Slim\Router  */
    protected $router = null;

    public function __construct($container)
    {
        $this->container = $container;
        $this->view      = $container['view'];
        $this->router    = $container['router'];
        $this->session   = $container['session'];
    }

    protected static function returnServerError(Response $response, $message = null, $status = \Util\RequestUtil::INTERNAL_SERVER_ERROR_STATUS)
    {
        $message = $message ? $message : json_encode(["error" => "server error"]);
        return $response->withStatus($status)->write($message);
    }

    protected static function returnServerSuccess(Response $response, $message = null, $status = \Util\RequestUtil::SUCCESS_STATUS)
    {
        $message = $message ? $message : json_encode('OK!');
        return $response->withStatus($status)->write($message);
    }
}