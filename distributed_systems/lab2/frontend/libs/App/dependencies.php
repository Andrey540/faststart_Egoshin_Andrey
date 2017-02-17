<?php

use Symfony\Component\Translation\Loader\YamlFileLoader;
use Symfony\Component\Translation\MessageSelector;
use Symfony\Component\Translation\Translator;

$container = $app->getContainer();

/**
 * @param \Slim\Http\Response $response
 * @return mixed
 */
function redirectToISpringSolutions($response)
{
    $status = \Util\RequestUtil::REDIRECTED_STATUS;
    return $response
        ->withStatus($status)
        ->withHeader('Content-Type', 'text/html')
        ->withRedirect('https://ispringsolutions.com', $status);
};

$container['errorHandler'] = function ($c) {
    return function ($request, $response, $exception) use ($c) {
        $settings = $c->get('settings');

        Logger::logException($settings['logger']['path'], $exception);
    };
};

$container['phpErrorHandler'] = function ($container) {
    return $container['errorHandler'];
};

set_error_handler(function ($severity, $message, $file, $line) {
    if (!(error_reporting() & $severity)) {
        // This error code is not included in error_reporting, so ignore it
        return;
    }
    throw new \ErrorException($message, 0, $severity, $file, $line);
});

$container['session'] = function ($c) {
    return new \SlimSession\Session;
};

$container['view'] = function ($c) {
    $settings = $c->get('settings');

    $translator = new Translator("en_US", new MessageSelector());
    $translator->setFallbackLocales(['en_US']);
    $translator->addLoader('yaml', new YamlFileLoader());

    $translator->addResource('yaml', './../libs/i18n/lang/ru_RU.yml', 'ru_RU');
    $translator->addResource('yaml', './../libs/i18n/lang/en_US.yml', 'en_US');

    $view = new \Slim\Views\Twig($settings['view']['template_path'], $settings['view']['twig']);

    $view->addExtension(new \Slim\Views\TwigExtension(
        $c['router'],
        $c['request']->getUri()
    ));
    $view->addExtension(new Twig_Extension_Debug());
    $view->addExtension(new \Symfony\Bridge\Twig\Extension\TranslationExtension($translator));

    return $view;
};

$container['poemController'] = function ($c) {
    return new \App\Controller\PoemController($c);
};