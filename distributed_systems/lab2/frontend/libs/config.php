<?php

$_ENV['SLIM_MODE'] = "development";

define('WEB_DIR', __DIR__ . '/../web');
define('LOG_DIR', __DIR__ . '/../logs');

define('SERVICE_HOST', 'localhost');
define('SERVICE_PORT', '8081');
define('POEM_CALCULATOR_SERVICE_URL', 'http://' . SERVICE_HOST . ':' . SERVICE_PORT . '/api/poem/');