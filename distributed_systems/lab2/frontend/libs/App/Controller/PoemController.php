<?php

namespace App\Controller;

use Slim\Http\Request;
use \Util\RequestUtil;
use \Request\UrlRequest;
use \Service\TaskIdGenerator;
use \App\Model\Poem;

class PoemController extends BaseController
{
    public function poem(Request $request, $response)
    {
        return $this->view->render($response, "poem.twig", []);
    }
    
    public function processPoem(Request $request, $response)
    {
        $poemText = $request->getParam("poem");
        if (!$poemText)
        {
            return self::returnServerError($response, json_encode(["error" => "empty text"]), RequestUtil::INVALID_REQUEST_STATUS);
        }
        $taskId = TaskIdGenerator::generateTaskId();
        $poem  = new Poem($taskId, $poemText);

        $urlRequest = new UrlRequest(POEM_CALCULATOR_SERVICE_URL);

        $urlRequest->setPostVars($poem->getData());

        RequestUtil::getUrlContents($urlRequest);

        $url = $this->router->pathFor('poemSuccess', [], ['id' => $taskId]);
        return $response->withStatus(RequestUtil::REDIRECTED_STATUS)->withHeader('Location', $url);
    }

    public function poemSuccess(Request $request, $response)
    {
        $taskId = $request->getParam("id");
        if (!$taskId)
        {
            return self::returnServerError($response, json_encode(["error" => "empty task id"]), RequestUtil::INVALID_REQUEST_STATUS);
        }

        $poemRequestUrl = $this->router->pathFor('processedPoemAjaxRequestSuccess', [], ['id' => $taskId]);
        return $this->view->render($response, 'poem_success.twig', ['poemRequestUrl' => $poemRequestUrl]);
    }

    public function processedPoemAjaxRequestSuccess(Request $request, $response)
    {
        $taskId = $request->getParam("id");
        if (!$taskId)
        {
            return self::returnServerError($response, json_encode(["error" => "empty task id"]), RequestUtil::INVALID_REQUEST_STATUS);
        }

        $redisClient = \Redis\Client::getRedisClient();
        $result = $redisClient->get($taskId);

        $result = nl2br($result);
        return self::returnServerSuccess($response, json_encode(["text" => $result]));
    }
}