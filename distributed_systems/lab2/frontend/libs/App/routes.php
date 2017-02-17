<?php

$app->get('/poem', 'App\Controller\PoemController:poem')->setName('poem');
$app->post('/process_poem', 'App\Controller\PoemController:processPoem')->setName('processPoem');
$app->get('/poem_success', 'App\Controller\PoemController:poemSuccess')->setName('poemSuccess');
$app->get('/processed_poem_request', 'App\Controller\PoemController:processedPoemAjaxRequestSuccess')->setName('processedPoemAjaxRequestSuccess');