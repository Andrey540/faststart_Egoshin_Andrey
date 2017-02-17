<?php

class AutoLoader
{
    private static $fileNameFormats = [
        ["\.class\.php", "%s.class.php"],
        ["\.interface\.php", "%s.interface.php"],
        ["\.php", "%s.php"]
    ];

    private $classes;

    public function __construct($classesDir)
    {
        $this->classes = $this->findClasses($classesDir);
    }

    /**
     * Findes and returns classes in specified directory.
     *
     * @param string $classesDir
     * @return array
     */
    private function findClasses($classesDir)
    {
        $classes = [];
        foreach (new DirectoryIterator($classesDir) as $file)
        {
            if ($file->isDot())
            {
                continue;
            }

            if ($file->isDir())
            {
                $classes = array_merge($classes,
                $this->findClasses($classesDir . "/" . $file));
                continue;
            }

            $file = $file->__toString();
            foreach (self::$fileNameFormats as $fileFormatInfo)
            {
                $fileFormat = $fileFormatInfo[0];
                if (preg_match("/" . $fileFormat . "$/", $file))
                {
                    $classes[] = [
                        $classesDir . "/" . $file,
                        $fileFormatInfo[1]
                    ];
                    break;
                }
            }
        }
        return $classes;
    }

    public function getClasses()
    {
        return $this->classes;
    }

    /**
     * Tries to load class.
     *
     * @param string $className
     */
    public function load($className)
    {
        $wantedClassFileName1 = basename($className);
        $pos = strripos($className, '\\');
        if ($pos)
        {
            $wantedClassFileName1 = substr($className, $pos + 1, strlen($className));
        }
        $wantedClassFileName1 .= ".php";
        foreach ($this->classes as $classInfo)
        {
            $classPath = $classInfo[0];
            $classFileName = pathinfo($classPath, PATHINFO_BASENAME);

            $classFileFormat = $classInfo[1];
            $wantedClassFileName2 = sprintf($classFileFormat, $className);

            if ($classFileName == $wantedClassFileName1 || $classFileName == $wantedClassFileName2)
            {
                require_once $classPath;
                break;
            }
        }
    }
}