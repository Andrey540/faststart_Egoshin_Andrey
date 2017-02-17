<?

    class RecursionAwareVarDumper
    {
        const INDENTATION = 4;

        private static $objects;
        private static $output;
        private static $depth;

        /**
         * Converts a variable into a string representation.
         * This method achieves the similar functionality as var_dump and print_r
         * but is more robust when handling complex objects such as PRADO controls.
         *
         * @param $var   Object|array|null to be dumped
         * @param $depth integer that the dumper should go into the variable. Defaults to 10.
         * @return string the string representation of the variable
         */
        public static function dump($var, $depth = 3)
        {
            self::$output  = '';
            self::$objects = array();
            self::$depth   = $depth;
            self::dumpInternal($var, 0);

            return self::$output;
        }

        /**
         * @param $var   Object|array|null
         * @param $level integer
         * @return string the string representation of the variable
         */
        private static function dumpInternal($var, $level)
        {
            switch (gettype($var))
            {
                case 'boolean':
                    self::$output .= $var ? 'true' : 'false';
                    break;
                case 'integer':
                    self::$output .= "$var";
                    break;
                case 'double':
                    self::$output .= "$var";
                    break;
                case 'string':
                    self::$output .= "'$var'";
                    break;
                case 'resource':
                    self::$output .= '{resource}';
                    break;
                case 'NULL':
                    self::$output .= "null";
                    break;
                case 'unknown type':
                    self::$output .= '{unknown}';
                    break;
                case 'array':
                    if (self::$depth <= $level)
                    {
                        self::$output .= 'array(' . self::getDepthLimitedText() . ')';
                    }
                    else if (empty($var))
                    {
                        self::$output .= 'array()';
                    }
                    else
                    {
                        $keys   = array_keys($var);
                        $spaces = str_repeat(' ', $level * self::INDENTATION);
                        $oneIndent = str_repeat(' ', self::INDENTATION);
                        self::$output .= "array\n" . $spaces . '(';
                        foreach ($keys as $key)
                        {
                            self::$output .= "\n" . $spaces . $oneIndent . "[$key] => ";
                            self::$output .= self::dumpInternal($var[$key], $level + 1);
                        }
                        self::$output .= "\n" . $spaces . ')';
                    }
                    break;
                case 'object':
                    if (($id = array_search($var, self::$objects, true)) !== false)
                    {
                        self::$output .= get_class($var) . '#' . ($id + 1) . '(...)';
                    }
                    else if (self::$depth <= $level)
                    {
                        self::$output .= get_class($var) . '(' . self::getDepthLimitedText() . ')';
                    }
                    else
                    {
                        $id        = array_push(self::$objects, $var);
                        $className = get_class($var);
                        $members   = (array) $var;
                        $keys      = array_keys($members);
                        $spaces    = str_repeat(' ', $level * self::INDENTATION);
                        $oneIndent  = str_repeat(' ', self::INDENTATION);
                        self::$output .= "$className#$id\n" . $spaces . '(';
                        foreach ($keys as $key)
                        {
                            $keyDisplay = strtr(trim($key), array("\0" => ':'));
                            self::$output .= "\n" . $spaces . $oneIndent . "[$keyDisplay] => ";
                            self::$output .= self::dumpInternal($members[$key], $level + 1);
                        }
                        self::$output .= "\n" . $spaces . ')';
                    }
                    break;
            }
        }

        private static function getDepthLimitedText()
        {
            return '...DEPTH LIMITED TO ' . self::$depth . '. print stopped. ...';
        }
    }