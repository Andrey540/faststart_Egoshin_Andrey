<?php

$languageInitializer = function($request, $response, $next) use ($app) {
    $container = $app->getContainer();
    $session   = $container['session'];
    $language  = $request->getParam('language');
    if ($language)
    {
        $session->set('language', $language);
    }
    else
    {
        $language = $session->get('language', $language);
    }
    LanguageInitializer::initLanguage($app->getContainer(), $language);
    $response = $next($request, $response);
    return $response;
};
$app->add($languageInitializer);

$app->add(new \Slim\Middleware\SessionMiddleware([
    'name'        => 'service-sid',
    'autorefresh' => true,
    'secure'      => true,
    'lifetime'    => '24 hour'
]));