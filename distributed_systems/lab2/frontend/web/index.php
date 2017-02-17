<?php

require_once __DIR__ . '/../libs/autoload.php';

// Prepare app
$settings = require __DIR__ . '/../libs/App/settings.php';
$app = new \Slim\App($settings);
// Register dependencies with the DIC
require __DIR__ . '/../libs/App/dependencies.php';
// Register middleware
require __DIR__ . '/../libs/App/middleware.php';
// Register routes
require __DIR__ . '/../libs/App/routes.php';
// Run app

$app->run();