<?php
namespace App\Model;

class Poem
{
    public $taskId;
    public $text;

    const POEM_TASK_ID = "TaskId";
    const POEM_TEXT    = "Text";

    public function __construct($taskId, $text)
    {
        $this->taskId = $taskId;
        $this->text   = $text;
    }

    /**
     * @return array
     */
    public function getData()
    {
        return [
            self::POEM_TASK_ID => $this->taskId,
            self::POEM_TEXT => $this->text
        ];
    }
}