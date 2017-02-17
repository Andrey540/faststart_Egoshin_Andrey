<?php
require_once __DIR__ . '/config.php';
require_once __DIR__ . '/Autoload/AutoLoader.class.php';

$autoLoader = new AutoLoader(__DIR__);
spl_autoload_register(array($autoLoader, 'load'));

require_once __DIR__ . '/../vendor/autoload.php';