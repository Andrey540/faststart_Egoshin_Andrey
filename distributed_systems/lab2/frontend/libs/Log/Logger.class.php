<?php

    class Logger
    {
        /**
         * Writes message to log.
         *
         * @param string $logFile path to log file
         * @param string $msg
         */
        public static function log($logFile, $msg)
        {
            $canOpenExistingFile = file_exists( $logFile ) && is_writable($logFile);
            $shouldCreateNewFile = !file_exists( $logFile );

            if ( $shouldCreateNewFile || $canOpenExistingFile )
            {
                if ($shouldCreateNewFile)
                {
                    $savedMask = umask(0);
                    $f = @fopen($logFile, "a");
                    umask($savedMask);
                }
                else
                {
                    $f = @fopen($logFile, "a");
                }

                if ($f)
                {
                    fprintf($f, "[%s] %s\n", date('Y-m-d H:i:s'), $msg);
                    fclose($f);
                }
            }
        }

        /**
         * Writes exception details to log.
         *
         * @param $logFile
         * @param Exception $e
         */
        public static function logException($logFile, Exception $e)
        {
            self::log($logFile, self::getExceptionDetails($e));
        }

        /**
         * Returns exception details for logging.
         *
         * @param Exception $e
         * @return string
         */
        public static function getExceptionDetails(Exception $e)
        {
            return "Exception details:\n\tmessage: '" . $e->getMessage() .
                   "'\n\tcode: " . $e->getCode() .
                   "\n\tline: " . $e->getLine() .
                   "\n\ttrace: \"" . $e->getTraceAsString() . "\"";
        }

        public static function debug( $message )
        {
            $logFile = LOG_DIR . "/debug.log";
            $message = "(" . microtime(true) . ") " . $message;
            Logger::log( $logFile, $message );
        }

        public static function debugObject($message, $var, $depth = 3)
        {
            self::debug($message . ': '. RecursionAwareVarDumper::dump($var, $depth));
        }
    }