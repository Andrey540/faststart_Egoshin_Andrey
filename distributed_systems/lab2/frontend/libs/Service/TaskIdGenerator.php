<?php
namespace Service;

class TaskIdGenerator
{
    const MAX_TASK_ID_KEY = "max_task_id";
    const TASK_ID_PREFIX  = "task_";

    /**
     * @return string
     */
    public static function generateTaskId()
    {
        $redisClient = \Redis\Client::getRedisClient();
        $maxTaskId = $redisClient->get(self::MAX_TASK_ID_KEY);
        $redisClient->set(self::MAX_TASK_ID_KEY, ++$maxTaskId);
        
        return self::TASK_ID_PREFIX . $maxTaskId;
    }
}