<?php

namespace Redis;

class Client
{
    private static $redisClient = null;
    
    public static function getRedisClient()
    {
        if (!self::$redisClient)
        {
            self::$redisClient = new \Predis\Client();
        }
        return self::$redisClient;
    }
}