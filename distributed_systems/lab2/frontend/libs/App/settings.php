<?php

$isDebugMode = (bool)$_ENV['SLIM_MODE'] == \Util\EnvironmentMode::DEV;

return [
    'settings' => [
        // Slim Settings
        'determineRouteBeforeAppMiddleware' => false,
        'displayErrorDetails' => $isDebugMode,

        // View settings
        'view' => [
            'template_path' => WEB_DIR . '/templates',
            'twig' => [
                'debug' => $isDebugMode,
                'auto_reload' => true,
            ],
        ],

        // Logger settings
        'logger' => [
            'name' => 'app',
            'path' => LOG_DIR . '/slim/error.log',
        ],
    ],
];